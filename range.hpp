#pragma once
/* 
Resources:
http://www.ocoudert.com/blog/2010/07/07/how-to-write-abstract-iterators-in-c/
*/
namespace itertools
{

template <typename T>
class range
{

private:
    T start, fin;

public:
    range(const T s, const T f) : start(s), fin(f) {}

    class const_iterator
    {

    private:
        T curr;

    public:
        const_iterator(T _start) : curr(_start) {}

        // ++i
        const_iterator &operator++()
        {
            ++curr;
            return *this;
        }

        // Dereference
        const T &operator*() const { return curr; }

        // Equal comparison
        bool operator==(const const_iterator &rhs) const { return curr == rhs.curr; }
        // Not-Equal comparison
        bool operator!=(const const_iterator &rhs) const { return !(curr == rhs.curr); }
    };

    auto begin() const
    {
        return const_iterator(start);
    }

    auto end() const
    {
        return const_iterator(fin);
    }
};
} // namespace itertools