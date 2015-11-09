#ifndef QUEUETOMEMORY_H
#define QUEUETOMEMORY_H

#include "process.h"
#include "vector"

#include "sectionedmemoryallocator.h"

#include "string"

#include "unordered_map"

/*Черга процесів до розділів пам'яті.*/
class QueueToMemory
{
public:
    /*Конструктор за замовченням.*/
    QueueToMemory();

    /*Конструктор з параметрами.*/
    QueueToMemory(SectionedMemoryAllocator& newAllocator);

    /*Додає наступний процес до черги.*/
    void AddNew(const Process& process);

    /*Основний цикл роботи черги. Виконується на кожному такті.*/
    void MainCycle();

    /*Отримує текстову інформацію про стан черги.*/
    std::string ToString();

private:
    /*Ініціалізує масиви.*/
    void InitializeArrays();

    /*Видалення виконаних процесів зі списку працюючих.*/
    void RemoveDone();

    /*Переводить (по можливості) процеси із очікування на виконання.*/
    void ShareMemory();

    /*Усі процеси на виконанні виконуються протягом поточного такту.*/
    void DoAll();

    /*Усі процеси у черзі очікують протягом поточного такту.*/
    void WaitAll();

    /*Очікуючі процеси.*/
    std::vector<Process> queue;

    /*Працюючі процеси.*/
    std::vector<Process> working;

    /*Завершені процеси.*/
    std::vector<Process> done;

    /*Аллокатор, який виділяє процесам пам'ять.*/
    SectionedMemoryAllocator* allocator;

    /*Таблиця відповідності ідентифікаторів процесів та їх віртуальних просторів.*/
    std::unordered_map<unsigned int, SectionId> processTable;
};

#endif // QUEUETOMEMORY_H
