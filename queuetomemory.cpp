#include "queuetomemory.h"


/*Конструктор за замовченням.*/
QueueToMemory::QueueToMemory(){
    InitializeArrays();
    allocator = NULL;
}

/*Конструктор з параметрами.*/
QueueToMemory::QueueToMemory(SectionedMemoryAllocator &newAllocator){
    InitializeArrays();
    allocator = &newAllocator;
}

/*Додає наступний процес до черги.*/
void QueueToMemory::AddNew(const Process &process){
    queue.push_back(process);
}

/*Основний цикл роботи черги. Виконується на кожному такті.*/
void QueueToMemory::MainCycle(){
    /*Спочатку необхідно видалити ті процеси, які виконалися на попередньому такті.*/
    RemoveDone();

    /*Далі необхідно розподілити наявну пам'ять між очікуючими процесами.*/
    ShareMemory();

    /*Після цього процеси, що виконуються, можуть виконуватися.*/
    DoAll();

    /*А процеси, що чекають, можуть чекати.*/
    WaitAll();
}

/*Отримує текстову інформацію про стан черги.*/
std::string QueueToMemory::ToString(){
    std::string ret = "";

    ret.append("Черга:\n");
    ret.append("Id\tStarted\tEnded\tWaited\tRequired\tRemaining\tLength\n");

    for(unsigned int i = 0; i < queue.size(); i++){
        ret.append(std::to_string(queue[i].id));
        ret.append("\t");

        ret.append(std::to_string(queue[i].startTime));
        ret.append("\t");

        ret.append(std::to_string(queue[i].endTime));
        ret.append("\t");

        ret.append(std::to_string(queue[i].waitTime));
        ret.append("\t");

        ret.append(std::to_string(queue[i].requiredTime));
        ret.append("\t");

        ret.append(std::to_string(queue[i].remainingTime));
        ret.append("\t");

        ret.append(std::to_string(queue[i].length));
        ret.append("\n");
    }
    ret.append("\n\n");

    ret.append("На виконанні:\n");
    ret.append("Id\tStarted\tEnded\tWaited\tRequired\tRemaining\tLength\n");

    for(unsigned int i = 0; i < working.size(); i++){
        ret.append(std::to_string(working[i].id));
        ret.append("\t");

        ret.append(std::to_string(working[i].startTime));
        ret.append("\t");

        ret.append(std::to_string(working[i].endTime));
        ret.append("\t");

        ret.append(std::to_string(working[i].waitTime));
        ret.append("\t");

        ret.append(std::to_string(working[i].requiredTime));
        ret.append("\t");

        ret.append(std::to_string(working[i].remainingTime));
        ret.append("\t");

        ret.append(std::to_string(working[i].length));
        ret.append("\n");

    }
    ret.append("\n\n");

    ret.append("Завершені:\n");
    ret.append("Id\tStarted\tEnded\tWaited\tRequired\tRemaining\tLength\n");

    for(unsigned int i = 0; i < done.size(); i++){
        ret.append(std::to_string(done[i].id));
        ret.append("\t");

        ret.append(std::to_string(done[i].startTime));
        ret.append("\t");

        ret.append(std::to_string(done[i].endTime));
        ret.append("\t");

        ret.append(std::to_string(done[i].waitTime));
        ret.append("\t");

        ret.append(std::to_string(done[i].requiredTime));
        ret.append("\t");

        ret.append(std::to_string(done[i].remainingTime));
        ret.append("\t");

        ret.append(std::to_string(done[i].length));
        ret.append("\n");
    }
    ret.append("\n\n");

    return ret;

}

/*Ініціалізує масиви.*/
void QueueToMemory::InitializeArrays(){
    queue = std::vector<Process>();
    working = std::vector<Process>();
    done = std::vector<Process>();
    processTable = std::unordered_map<unsigned int, SectionId>();
}

/*Видалення виконаних процесів зі списку працюючих.*/
void QueueToMemory::RemoveDone(){
    unsigned int i = 0;
    while(i < working.size()){
        if(true == working[i].IsDone()){
            std::unordered_map<unsigned int, SectionId >::const_iterator gotInfo = processTable.find(working[i].id);
            done.push_back(working[i]);
            allocator->mem_free(gotInfo->second);
            working.erase(working.begin() + i);
            processTable.erase(gotInfo);
            i = 0;
            continue;
        }
        i++;
    }
}

/*Переводить (по можливості) процеси із очікування на виконання.*/
void QueueToMemory::ShareMemory(){
    unsigned int i = 0;
    while(i < queue.size()){
        SectionId* newId = allocator->mem_alloc(queue[i].length);

        if(NULL == newId){
            i++;
            continue;
        }

        working.push_back(queue[i]);
        processTable.emplace(queue[i].id, *newId);
        queue.erase(queue.begin() + i);
        delete newId;
        i = 0;
    }
}

/*Усі процеси на виконанні виконуються протягом поточного такту.*/
void QueueToMemory::DoAll(){
    for(unsigned int i = 0; i < working.size(); i++){
        working[i].Do(1);
    }
}

/*Усі процеси у черзі очікують протягом поточного такту.*/
void QueueToMemory::WaitAll(){
    for(unsigned int i = 0; i < queue.size(); i++){
        queue[i].Wait(1);
    }
}
