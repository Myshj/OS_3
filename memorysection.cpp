#include "memorysection.h"

#include "stdio.h"

/*Конструктор за замовченням.*/
MemorySection::MemorySection()
{
    id = SectionId();

    address = NULL;

    length = 0;
}

/*Конструктор з параметрами.*/
MemorySection::MemorySection(const SectionId &newId, void *newAddress, const unsigned int newLength)
{
    id = newId;

    address = newAddress;

    length = newLength;
}

/*Конструктор копіювання.*/
MemorySection::MemorySection(const MemorySection &other)
{
    id = other.id;

    address = other.address;

    length = other.length;
}

/*Деструктор.*/
MemorySection::~MemorySection()
{
    address = NULL;
}

SectionId MemorySection::GetId()
{
    return id;
}

void MemorySection::SetId(const SectionId &newId)
{
    id = newId;
}

void *MemorySection::GetAddress()
{
    return address;
}

void MemorySection::SetAddress(void *newAddress)
{
    address = newAddress;
}

unsigned int MemorySection::GetLength()
{
    return length;
}

void MemorySection::SetLength(const unsigned int newLength)
{
    length = newLength;
}
