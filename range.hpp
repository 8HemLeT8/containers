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
        T _start;

    public:
        const_iterator(T _s) : _start(_s) {}

        // ++i
        const_iterator &operator++()
        {
            ++_start;
            return *this;
        }

        // Dereference
        const T &operator*() const { return _start; }

        // Equal comparison
        bool operator==(const const_iterator &rhs) const { return _start == rhs._start; }
        // Not-Equal comparison
        bool operator!=(const const_iterator &rhs) const { return !(_start == rhs._start); }
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