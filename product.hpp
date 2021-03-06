#pragma once
#include <utility>
#include <tuple>
/* 
Resources:
http://www.ocoudert.com/blog/2010/07/07/how-to-write-abstract-iterators-in-c/
https://stackoverflow.com/questions/19923353/multiple-typename-arguments-in-c-template
https://en.cppreference.com/w/cpp/language/decltype
https://stackoverflow.com/questions/15365860/returning-two-variables-in-a-c-function
*/
namespace itertools
{

template <typename T, typename P>
class product
{

private:
    T iterable1;
    P iterable2;

public:
    product(const T itrbl1, const P itrbl2)
        : iterable1(itrbl1), iterable2(itrbl2) {}

    class const_iterator
    {
        typedef typename T::const_iterator T_c_itr;
        typedef typename P::const_iterator P_c_itr;

    private:
        T_c_itr iterator1_curr;
        T_c_itr iterator1_end;
        P_c_itr iterator2_current_elem;
        P_c_itr iterator2_begin;
        P_c_itr iterator2_end;

    public:
        const_iterator(const T_c_itr &itr1_b, const T_c_itr &itr1_e,
                       const P_c_itr &itr2_b, const P_c_itr &itr2_e)
            : iterator1_curr(itr1_b), iterator1_end(itr1_e),
              iterator2_current_elem(itr2_b),
              iterator2_begin(itr2_b), iterator2_end(itr2_e) {}

        // ++i
        const_iterator &operator++()
        {
            ++iterator2_current_elem;
            if (iterator2_current_elem == iterator2_end)
            {
                ++iterator1_curr;
                iterator2_current_elem = iterator2_begin;
            }
            return *this;
        }
        // Dereference
        const auto operator*() const
        {
            return std::make_pair(*iterator1_curr, *iterator2_current_elem);
        }
        // Equal
        bool operator==(const const_iterator &rhs) const
        {
            // Check if both are done, if not then check each element
            if ((iterator1_curr == iterator1_end || iterator2_current_elem == iterator2_end) ||
                (iterator1_curr == rhs.iterator1_curr && iterator1_end == rhs.iterator1_end &&
                 iterator2_current_elem == rhs.iterator2_current_elem && iterator2_end == rhs.iterator2_end))
            {
                return true;
            }
            return false;
        }
        // Not-Equal
        bool operator!=(const const_iterator &rhs) const
        {
            return !(*this == rhs);
        }
    };

    auto begin() const
    {
        return const_iterator(iterable1.begin(), iterable1.end(), iterable2.begin(), iterable2.end());
    }

    auto end() const
    {
        return const_iterator(iterable1.end(), iterable1.end(), iterable2.end(), iterable2.end());
    }
};
} // namespace itertools