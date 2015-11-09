#ifndef SECTIONID_H
#define SECTIONID_H

#include "vector"


/*Ідентифікатор для розділу пам'яті.*/
class SectionId
{
public:
    /*Конструктор за замовченням.*/
    SectionId();

    /*Конструктор копіювання.*/
    SectionId(const SectionId& other);

    /*Деструктор.*/
    ~SectionId();

    /*Оператор "дорівнює".*/
    bool operator == (const SectionId& other);

    /*Оператор "не дорівнює".*/
    bool operator != (const SectionId& other);

    /*Оператор присвоєння.*/
    SectionId& operator = (const SectionId& other);

    unsigned int GetValue(){
        return value;
    }

private:
    /*Виділяє перший вільний ідентифікатор для нового екземпляру.*/
    unsigned int GetNewId();

    /*Значення ідентифікатора.*/
    unsigned int value;

    /*Таблиця використання ідентифікаторів..*/
    static std::vector<unsigned int> ids;
};

#endif // SECTIONID_H
