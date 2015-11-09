#include "sectionid.h"

/*Конструктор за замовченням.*/
SectionId::SectionId()
{
    value = GetNewId();
}

/*Конструктор копіювання.*/
SectionId::SectionId(const SectionId &other)
{
    value = other.value;
    ids[value]++;
}

/*Деструктор.*/
SectionId::~SectionId()
{
    ids[value]--;
}

/*Оператор "дорівнює".*/
bool SectionId::operator ==(const SectionId &other)
{
    return value == other.value;
}

/*Оператор "не дорівнює".*/
bool SectionId::operator !=(const SectionId &other)
{
    return value != other.value;
}

/*Оператор присвоєння.*/
SectionId &SectionId::operator =(const SectionId &other)
{
    if(this == &other){
        return *this;
    }

    ids[value]--;

    value = other.value;

    ids[value]++;

    return *this;
}

/*Виділяє перший вільний ідентифікатор для нового екземпляру.*/
unsigned int SectionId::GetNewId()
{
    for(unsigned int i = 0; i < ids.size(); i++){
        if(ids[i] == 0){
            ids[i]++;
            return i;
        }
    }

    ids.push_back(1);

    return ids.size() - 1;
}

std::vector<unsigned int> SectionId::ids = std::vector<unsigned int>();

