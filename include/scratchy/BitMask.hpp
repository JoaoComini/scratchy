#pragma once

template <class T>
struct BitMask
{
    static const unsigned int type_size = sizeof(T) * 8;
    static unsigned long const value = (static_cast<unsigned long>(1) << type_size) - 1;
};