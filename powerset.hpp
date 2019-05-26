#pragma once
#include <math.h>
#include <string>
#include <vector>
#include <iostream>

/* 
Resources:
http://www.ocoudert.com/blog/2010/07/07/how-to-write-abstract-iterators-in-c/
https://stackoverflow.com/questions/24365954/how-to-generate-a-power-set-of-a-given-set
*/
namespace itertools
{

template <typename T>
class powerset
{

private:
    T iterable;

    // We want to know how many items are in the iterable object.
    int totalnumber() const
    {
        int elements_number = 0;
        for (auto i : iterable)
        {
            elements_number += 1;
        }
        return int(pow(2, elements_number));
    }

public:
    powerset(const T itrbl) : iterable(itrbl) {}

    class const_iterator
    {
    private:
        T curr_iterable; // We pass the iterable object to iterate over it.
        int size;

    public:
        const_iterator(T current_itrbl, int current_size) : curr_iterable(current_itrbl), size(current_size) {}

        // ++i
        const_iterator &operator++()
        {
            // According to the resource above, we use a binary number to generate the set, therefore we increment the size to use it in the AND operation
            ++size;
            return *this;
        }

        // Dereference
        const T operator*() const
        {
            vector<typename remove_const<typename remove_reference<decltype(*(curr_iterable.begin()))>::type>::type> ans;
            int i = 1;
            for (auto piece : curr_iterable)
            {
                if (i & piece)
                    ans.insert(piece);
                i = i << 1;
            }
            return ans;
        }

        // Equal comparison
        bool operator==(const const_iterator &rhs) const { return size == rhs.size; }
        // Not-Equal comparison
        bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }
    };

    auto begin() const
    {
        // We pass 0 to mark the start of the set
        return const_iterator(iterable, 0);
    }
    auto end() const
    {
        int fullsize = totalnumber();
        // We pass the fullsize to mark the end of the set
        return const_iterator(iterable, fullsize);
    }
};
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &ans)
{
    out << "{";
    auto curr = ans.begin();
    if (curr != ans.end())
    {
        out << *curr;
        ++curr;
    }
    while (temp != ans.end())
    {
        out << ',' << *curr;
        ++curr;
    }
    out << "}";
    return out;
}
}; // namespace itertools
