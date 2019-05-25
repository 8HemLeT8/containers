#pragma once
/* 
Resources:
http://www.ocoudert.com/blog/2010/07/07/how-to-write-abstract-iterators-in-c/
https://stackoverflow.com/questions/19923353/multiple-typename-arguments-in-c-template
https://en.cppreference.com/w/cpp/language/decltype
*/
namespace itertools
{

template <typename T>
class powerset_class
{

private:
    T start_1;

public:
    powerset_class(T s1) : start_1(s1)
    {
    }

    class iterator
    {
    private:
        T s1;

    public:
        iterator(T _s1) : s1(_s1)
        {
        }
        // ++i
        iterator &operator++()
        {
            s1++;
            return *this;
        }
        // Dereference
        auto &operator*() const
        {
            return *s1;
        }
        // Not-Equal comparison
        bool operator!=(const iterator &rhs) const
        {
            return s1 != rhs.s1;
        }
    };

    auto begin() const
    {
        return (start_1.begin());
    }

    auto end() const
    {
        return (start_1.end());
    }
};
template <typename T>
powerset_class<T> powerset(T start1)
{
    return powerset_class<T>(start1);
}
} // namespace itertools