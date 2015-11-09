#include "sectionedmemoryallocator.h"
#include "malloc.h"
#include "stdio.h"

#include "algorithm"

using namespace std;

/*Конструктор за замовченням.*/
SectionedMemoryAllocator::SectionedMemoryAllocator()
{
    InitializeSizes(DEFAULT_MEMORY_SIZE);

    InitializeMemory();

    InitializeSections();
}

/*Конструктор з параметрами.*/
SectionedMemoryAllocator::SectionedMemoryAllocator(const unsigned int newMemorySize)
{
    InitializeSizes(newMemorySize);

    InitializeMemory();

    InitializeSections();
}

/*Конструктор копіювання.*/
SectionedMemoryAllocator::SectionedMemoryAllocator(const SectionedMemoryAllocator &other)
{
    InitializeSizes(other.memorySize);

    InitializeMemory();

    InitializeSections();
}

/*Деструктор.*/
SectionedMemoryAllocator::~SectionedMemoryAllocator()
{
    free(memory);
}

/*
 * Виконує спробу виділення пам'яті заданого розміру.
 * В разі успіху повертає вказівник на ідентифікатор виділеного розділу пам'яті.
 * Інакше повертає NULL.
 * */
SectionId* SectionedMemoryAllocator::mem_alloc(const unsigned int size)
{
    /*Якщо запитано занадто великий розділ або вільних розділів немає взагалі, то продовжувати сенсу немає.*/
    if(freeSections.empty() || size > memorySize){
        return NULL;
    }

    SectionId* firstFreeSection = FindFirstPossibleSection(size);

    /*Якщо з першої спроби знайти розділ необхідного розміру не вдалося, потрібно виконати стиск.*/
    if(NULL == firstFreeSection){
        Compress();
        firstFreeSection = FindFirstPossibleSection(size);

        /*Якщо і з другої спроби знайти розділ потрібного розміру не вдалося, то продовжувати сенсу немає.*/
        if(NULL == firstFreeSection){
            return NULL;
        }
    }

    return AllocateSectionFromFree(*firstFreeSection, size);
}

/*
 * Виконує спробу звільнити блок, заданий ідентифікатором.
 * */
void SectionedMemoryAllocator::mem_free(const SectionId &id)
{

    for(unsigned int i =0; i < allocatedSections.size(); i++){
        if(allocatedSections[i].GetId() == id){
            MemorySection sectionToFree = allocatedSections[i];
            allocatedSections.erase(allocatedSections.begin() + i);
            freeSections.push_back(sectionToFree);
            return;
        }
    }
}

/*Початкова ініціалізація розмірів пам'яті та розділу.*/
void SectionedMemoryAllocator::InitializeSizes(const unsigned int newMemorySize)
{
    memorySize = newMemorySize;
}

/*Початкове виділення буферної пам'яті у розмірі "memorySize".*/
void SectionedMemoryAllocator::InitializeMemory()
{
    memory = (void*)malloc(memorySize);
}

/*Початкова ініціалізація розділів.*/
void SectionedMemoryAllocator::InitializeSections()
{
    freeSections = vector<MemorySection>();

    freeSections.push_back(MemorySection(SectionId(), memory, memorySize));

    allocatedSections = vector<MemorySection>();
}

/*
 * Виконує пошук першого вільного розділу.
 * Повертає вказівник на його ідентифікатор в разі успіху.
 * Інакше повертає NULL.
 * */
SectionId *SectionedMemoryAllocator::FindFirstPossibleSection(const unsigned int size)
{
    for(unsigned int i = 0; i < freeSections.size(); i++){
        if(freeSections[i].GetLength() >= size){
            return new SectionId(freeSections[i].GetId());
        }
    }

    return NULL;
}

/*
 * Виділяє з вільного розділу, заданого ідентифікатором, розділ пам'яті необхідного розміру.
 * Повертає вказівник на ідентифікатор новоствореного блоку в разі успіху.
 * Інакше повертає NULL.
 * */
SectionId *SectionedMemoryAllocator::AllocateSectionFromFree(const SectionId &freeId,
                                                             const unsigned int size)
{
    for(unsigned int i = 0; i < freeSections.size(); i++){
        if(freeSections[i].GetId() == freeId){

            if(freeSections[i].GetLength() == size){

                allocatedSections.push_back(freeSections[i]);

                freeSections.erase(freeSections.begin() + i);
            }else{

                freeSections[i].SetLength(freeSections[i].GetLength() - size);

                allocatedSections.push_back(MemorySection(SectionId(),
                                                        freeSections[i].GetAddress() + freeSections[i].GetLength(),
                                                        size)
                                            );
            }
            return new SectionId(allocatedSections.back().GetId());
        }
    }

    return NULL;
}

/*
 * Отримує інформіцію про стан пам'яті у текстовому вигляді.
 * */
string SectionedMemoryAllocator::ToString()
{
    string ret = "";

    ret.append("Зайняті розділи:\n");
    ret.append("Id\tAddress\t\t\tLength\n");

    for(unsigned int i = 0; i < allocatedSections.size(); i++){
        ret.append(to_string(allocatedSections[i].GetId().GetValue()));
        ret.append("\t");

        ret.append(to_string((int)(allocatedSections[i].GetAddress())));
        ret.append("\t\t");

        ret.append(to_string(allocatedSections[i].GetLength()));
        ret.append("\n");
    }

    ret.append("\nВільні розділи:\n");
    ret.append("Id\tAddress\t\t\tLength\n");

    for(unsigned int i = 0; i < freeSections.size(); i++){
        ret.append(to_string(freeSections[i].GetId().GetValue()));
        ret.append("\t");

        ret.append(to_string((int)(freeSections[i].GetAddress())));
        ret.append("\t\t");

        ret.append(to_string(freeSections[i].GetLength()));
        ret.append("\n");
    }

    return ret;
}

/*
 * Виконує порівняння розділів пам'яті за їх початковими адресами.
 * Повертає "true", якщо адреса лівого розділу менша за адресу правого.
 * */
bool CompareSectionsByAddresses(MemorySection& left, MemorySection& right){
    return  ((int)(left.GetAddress()) < (int)(right.GetAddress()));
}

/*Виконує "стискання" розділів у бік молодших розрядів.*/
void SectionedMemoryAllocator::Compress()
{
    /*Для початку масив зайнятих розділів потрібно впорядкувати за зростанням початкових адрес.*/
    sort(allocatedSections.begin(),
         allocatedSections.end(),
         CompareSectionsByAddresses);

    /*Далі вміст зайнятих розділів зсувається до молодших розрядів буферної пам'яті.*/
    allocatedSections[0].SetAddress(memory);
    for(unsigned int i = 1; i < allocatedSections.size(); i++){
        allocatedSections[i].SetAddress(allocatedSections[i - 1].GetAddress() + allocatedSections[i - 1].GetLength());
    }

    /*Після цього всі вільні розділи об'єднуються.*/
    freeSections.clear();
    freeSections.push_back(MemorySection(SectionId(),
                                         allocatedSections.back().GetAddress() + allocatedSections.back().GetLength(),
                                         (int)memory + memorySize - (int)allocatedSections.back().GetAddress() - allocatedSections.back().GetLength())
                           );
}

