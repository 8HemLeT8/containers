#pragma once

#include <math.h>
#include <vector>

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
        const T &curr_iterable; // We pass the iterable object to iterate over it.
        int size;

    public:
        const_iterator(const T &current_itrbl, int current_size) : curr_iterable(current_itrbl), size(current_size) {}

        // ++i
        const_iterator &operator++()
        {
            // According to the resource above, we use a binary number to generate the set, therefore we increment the size to use it in the AND operation
            ++size;
            return *this;
        }

        // Dereference
        auto operator*() const
        {
            // Using a vector to simulate a set (we had compilation errors using sets), the type is set to be the of the iterator first current.
            std::vector<typename std::remove_const<typename std::remove_reference<decltype(*(curr_iterable.begin()))>::type>::type> ans;
            int i = 1;
            for (auto piece : curr_iterable)
            {
                if (i & size)
                    ans.push_back(piece);
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
std::ostream &operator<<(ostream &os, const vector<T> power_set)
{
    os << "{";
    int counter = 0;
    for (auto current : power_set)
    {
        os << current;
        counter++;
        if (counter < power_set.size())
            os << ",";
    }
    os << "}";
    return os;
}
}; // namespace itertools
