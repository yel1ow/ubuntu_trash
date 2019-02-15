#pragma once

namespace my_structs
{
    template <class T>
    class IList
    {
    public:
        virtual T at(size_t index) const = 0;
        virtual T& at(size_t index) = 0;
        virtual void add(T x) = 0;
        virtual void addAfter(size_t index) = 0;
        virtual bool has(T x) = 0;
        virtual void remove(T x) = 0;
        virtual void removeAt(size_t index) = 0;
        virtual ~IList() {}
        virtual size_t size() const = 0;
    };
}
