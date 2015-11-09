#include "process.h"


/*Конструктор за замовченням.*/
Process::Process(){
    id = 0;
    startTime = 0;
    endTime = 0;
    waitTime = 0;
    requiredTime = 0;
    remainingTime = 0;
    length = 0;
}

/*Конструктор з параметрами.*/
Process::Process(unsigned int newId, unsigned int newStartTime, unsigned int newRequiredTime, unsigned int newLength){
    id = newId;
    startTime = newStartTime;
    endTime = 0;
    waitTime = 0;
    requiredTime = newRequiredTime;
    remainingTime = requiredTime;
    length = newLength;
}

/*Виконується протягом заданої кількості тактів.*/
void Process::Do(unsigned int ticks){
    if(ticks < remainingTime){
        remainingTime -= ticks;
    }else{
        remainingTime = 0;
        endTime = startTime + requiredTime + waitTime - 1;
    }
}

/*Очікує протягом заданої кількості тактів.*/
void Process::Wait(unsigned int ticks){
    waitTime += ticks;
}

/*Чи є процес завершеним?*/
bool Process::IsDone(){
    return remainingTime == 0;
}
