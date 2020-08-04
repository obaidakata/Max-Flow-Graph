#include "Quantity.h"

Quantity Quantity::s_Infinite(eQuantityTypes::Inifinity);
Quantity Quantity::s_NegInifinity(eQuantityTypes::NegativeInifinity);

Quantity::Quantity(int i_Value)
{
    m_NumValue = i_Value;
    quantityType = eQuantityTypes::Value;
}

Quantity::Quantity(const Quantity& i_Value)
{
    m_NumValue = i_Value.m_NumValue;
    quantityType = i_Value.quantityType;
}

Quantity::Quantity(eQuantityTypes i_Type)
{ 
    quantityType = i_Type;
    m_NumValue = 0;
}

Quantity Quantity::operator+(const Quantity& i_ToAdd)
{
    Quantity toReturn(*this);
    if (quantityType == Value)
    {
        toReturn.m_NumValue += i_ToAdd.m_NumValue;
        return toReturn;
    }
    throw new exception("Cant add to Inifinity or NegativeInifinity");
}

Quantity& Quantity::operator+=(const Quantity& i_ToAdd)
{
    *this = *this + i_ToAdd;
    return *this;
}

bool Quantity::operator==(const Quantity& i_ToCompare)
{
    // true if two is infinite
    // or two is not infinity and both have the same value
    bool isEqual;

    if (i_ToCompare.quantityType == Value && quantityType == Value)
    {
        isEqual = i_ToCompare.m_NumValue == m_NumValue;
    }
    else
    {
        isEqual = i_ToCompare.quantityType == quantityType;
    }
    return isEqual;
}

Quantity& Quantity::operator=(const Quantity& i_ToAssign)
{
    quantityType = i_ToAssign.quantityType;
    if (quantityType == Value)
    {
        m_NumValue = i_ToAssign.m_NumValue;
    }
    return *this;
}

bool Quantity::operator>(const Quantity& i_ToCompare)
{
    bool compareResult;
    if (quantityType == Inifinity)
    {
        compareResult = i_ToCompare.quantityType != Inifinity;
    }
    else if (quantityType == NegativeInifinity)
    {
        compareResult = false;
    }
    else
    {
        if (i_ToCompare.quantityType == Inifinity)
        {
            compareResult = false;
        }
        else if (i_ToCompare.quantityType == NegativeInifinity)
        {
            compareResult = true;
        }
        else
        {
            compareResult = m_NumValue > i_ToCompare.m_NumValue;
        }
    }

    return compareResult;
}

bool Quantity::operator<(const Quantity& i_ToCompare)
{
    return !(*this > i_ToCompare);
}