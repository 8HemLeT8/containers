#pragma once
/* 
Resources:
http://www.ocoudert.com/blog/2010/07/07/how-to-write-abstract-iterators-in-c/
*/
namespace itertools
{
template <typename T>
class range_class
{

private:
    T start;
    T fin;

public:
    range_class(T s, T f)
    {
        start = s;
        fin = f;
    }
    class Itr
    {
    private:
        T _start;

    public:
        Itr(T _s)
        {
            _start = _s;
        }
        // ++i
        Itr &operator++()
        {
            ++_start;
            return *this;
        }
        // i++
        const Itr operator++(int)
        {
            Itr tmp = *this;
            _start++;
            return tmp;
        }
        // Dereference
        T &operator*() { return _start; }
        // Equal comparison
        bool operator==(const Itr &rhs) const { return _start == rhs._start; }
        // Not-Equal comparison
        bool operator!=(const Itr &rhs) const { return !(_start == rhs._start); }
    };

    Itr begin() const
    {
        return Itr(start);
    }

    Itr end() const
    {
        return Itr(fin);
    }
};

template <typename T>
range_class<T> range(T start, T fin)
{
    return range_class<T>(start, fin);
}

} // namespace itertools