#ifndef MEMORYSECTION_H
#define MEMORYSECTION_H

#include "sectionid.h"

/*Розділ пам'яті.*/
class MemorySection
{
public:
    /*Конструктор за замовченням.*/
    MemorySection();

    /*Конструктор з параметрами.*/
    MemorySection(const SectionId& newId,
                  void* newAddress,
                  const unsigned int newLength);

    /*Конструктор копіювання.*/
    MemorySection(const MemorySection& other);

    /*Деструктор.*/
    ~MemorySection();

    SectionId GetId();
    void SetId(const SectionId& newId);

    void* GetAddress();
    void SetAddress(void* newAddress);

    unsigned int GetLength();
    void SetLength(const unsigned int newLength);

private:

    /*Ідентифікатор розділу.*/
    SectionId id;

    /*Адреса початку.*/
    void* address;

    /*Довжина в байтах.*/
    unsigned int length;
};

#endif // MEMORYSECTION_H
