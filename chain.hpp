#pragma once
/* 
Resources:
http://www.ocoudert.com/blog/2010/07/07/how-to-write-abstract-iterators-in-c/
https://stackoverflow.com/questions/19923353/multiple-typename-arguments-in-c-template
https://en.cppreference.com/w/cpp/language/decltype
*/
namespace itertools
{

template <typename T, typename P>
class chain
{

private:
    T iterable1;
    P iterable2;

public:
    chain(const T itrbl1, const P itrbl2)
        : iterable1(itrbl1), iterable2(itrbl2) {}

    class const_iterator
    {

    private:
        typename T::const_iterator iterator1_begin;
        typename T::const_iterator iterator1_end;
        typename P::const_iterator iterator2_begin;
        typename P::const_iterator iterator2_end;

        bool is_A_fin() const { return iterator1_begin == iterator1_end; }

    public:
        const_iterator(const typename T::const_iterator &itr1_b, const typename T::const_iterator &itr1_e,
                       const typename P::const_iterator &itr2_b, const typename P::const_iterator &itr2_e)
            : iterator1_begin(itr1_b), iterator1_end(itr1_e),
              iterator2_begin(itr2_b), iterator2_end(itr2_e) {}

        // ++i
        const_iterator &operator++()
        {
            if (is_A_fin())
                ++iterator2_begin;
            else
                ++iterator1_begin;
            return *this;
        }
        // Dereference
        const auto operator*() const
        {
            if (is_A_fin())
                return *iterator2_begin;
            return *iterator1_begin;
        }

        bool operator==(const const_iterator &rhs) const
        {
            if (iterator1_begin == rhs.iterator1_begin && iterator1_end == rhs.iterator1_end &&
                iterator2_begin == rhs.iterator2_begin && iterator2_end == rhs.iterator2_end)
            {
                return true;
            }
            return false;
        }

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