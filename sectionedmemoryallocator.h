#ifndef SECTIONEDMEMORYALLOCATOR_H
#define SECTIONEDMEMORYALLOCATOR_H

#include "vector"

#include "string"

#include "sectionid.h"

#include "memorysection.h"



/*Виконує розподіл пам'яті фіксованими розділами з сегментною організацією.*/
class SectionedMemoryAllocator
{
public:
    /*Конструктор за замовченням.*/
    SectionedMemoryAllocator();

    /*Конструктор з параметрами.*/
    SectionedMemoryAllocator(const unsigned int newMemorySize);

    /*Конструктор копіювання.*/
    SectionedMemoryAllocator(const SectionedMemoryAllocator& other);

    /*Деструктор.*/
    ~SectionedMemoryAllocator();

    /*
     * Виконує спробу виділення пам'яті заданого розміру.
     * В разі успіху повертає вказівник на ідентифікатор виділеного розділу пам'яті.
     * Інакше повертає NULL.
     * */
    SectionId* mem_alloc(const unsigned int size);

    /*
     * Виконує спробу звільнити блок, заданий ідентифікатором.
     * */
    void mem_free(const SectionId& id);

    /*
     * Отримує інформіцію про стан пам'яті у текстовому вигляді.
     * */
    std::string ToString();

private:

    /*Початкова ініціалізація розмірів пам'яті та розділу.*/
    void InitializeSizes(const unsigned int newMemorySize);

    /*Початкове виділення буферної пам'яті у розмірі "memorySize".*/
    void InitializeMemory();

    /*Початкова ініціалізація розділів.*/
    void InitializeSections();

    /*
     * Виконує пошук першого вільного розділу.
     * Повертає вказівник на його ідентифікатор в разі успіху.
     * Інакше повертає NULL.
     * */
    SectionId* FindFirstPossibleSection(const unsigned int size);

    /*
     * Виділяє з вільного розділу, заданого ідентифікатором, розділ пам'яті необхідного розміру.
     * Повертає вказівник на ідентифікатор новоствореного блоку в разі успіху.
     * Інакше повертає NULL.
     * */
    SectionId* AllocateSectionFromFree(const SectionId& freeId,
                                       const unsigned int size);



    /*Виконує "стискання" розділів у бік молодших розрядів.*/
    void Compress();

    /*Буферна пам'ять.*/
    void* memory;

    /*Розмір буферної пам'яті.*/
    unsigned int memorySize;

    /*Розмір розділу.*/
    unsigned int sectionSize;

    /*Масив вільних розділів.*/
    std::vector<MemorySection> freeSections;

    /*Масив зайнятих розділів.*/
    std::vector<MemorySection> allocatedSections;

    /*Розмір буферної пам'яті за замовченням.*/
    static const unsigned int DEFAULT_MEMORY_SIZE = 1024;
};

#endif // SECTIONEDMEMORYALLOCATOR_H
