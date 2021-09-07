#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace Scramble::Utils
{
    template<typename T>
    void Swap(T* a, T* b)
    {
        T temp = *a;
        *a = *b;
        *b = temp;
    }
}

#endif