#ifndef PROCESS_H
#define PROCESS_H


class Process
{
public:
    /*Конструктор за замовченням.*/
    Process();

    /*Конструктор з параметрами.*/
    Process(unsigned int newId,
            unsigned int newStartTime,
            unsigned int newRequiredTime,
            unsigned int newLength);

    /*Виконується протягом заданої кількості тактів.*/
    void Do(unsigned int ticks);

    /*Очікує протягом заданої кількості тактів.*/
    void Wait(unsigned int ticks);

    /*Чи є процес завершеним?*/
    bool IsDone();


public:
    unsigned int id;
    unsigned int startTime;
    unsigned int endTime;
    unsigned int waitTime;
    unsigned int requiredTime;
    unsigned int remainingTime;
    unsigned int length;
};

#endif // PROCESS_H
