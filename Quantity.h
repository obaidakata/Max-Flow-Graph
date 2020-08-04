#pragma once

#include<iostream>
#include <string>
using namespace std;

class Quantity
{
public:
    enum eQuantityTypes { Value, Inifinity, NegativeInifinity };
private:
    int m_NumValue;
    eQuantityTypes quantityType;
public:
    static Quantity s_Infinite;
    static Quantity s_NegInifinity;

    Quantity(int i_Value);
    Quantity(const Quantity& i_Value);
    Quantity(eQuantityTypes i_Type = Inifinity);

    Quantity operator+(const Quantity& i_ToAdd);
    Quantity& operator+=(const Quantity& i_ToAdd);
    bool operator==(const Quantity& i_ToCompare);
    Quantity& operator=(const Quantity& i_ToAssign);
    bool operator>(const Quantity& i_ToCompare);
    bool operator<(const Quantity& i_ToCompare);
    bool operator<=(const Quantity& i_ToCompare)
    {
        return !(*this > i_ToCompare);
    }
};