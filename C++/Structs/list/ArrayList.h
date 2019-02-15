#pragma once

#include "IList.h"

namespace my_structs
{
    template <class T>
    class ArrayList : private IList<T>
    {
    public:

        size_t size() const {return size;}
        ~ArrayList();
    private:
        T* data;
        size_t size;
    };
}
