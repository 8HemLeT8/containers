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
class zip_class
{

private:
    T start_1;
    P start_2;

public:
    zip_class(T s1, P s2) : start_1(s1), start_2(s2)
    {
    }

    template <typename A, typename B>
    class Itr
    {
    private:
        A s1;
        B s2;

        bool is_A_fin() const
        {
            if (s1 == s1.end())
            {
                return false;
            }
            return true;
        }

    public:
        Itr(A _s1, B _s2) : s1(_s1), s2(_s2)
        {
        }
        // ++i
        Itr<A, B> &operator++()
        {
            if (is_A_fin())
            {
                s2++;
            }
            else
            {
                s1++;
            }

            return *this;
        }
        // Dereference
        auto &operator*() const
        {
            if (is_A_fin())
            {
                return *s2;
            }
            return *s1;
        }
        // Not-Equal comparison
        bool operator!=(const Itr<A, B> &rhs) const
        {
            if (is_A_fin())
            {
                return s1 != rhs.s1;
            }
            return s2 != rhs.s2;
        }
    };

    auto begin() const
    {
        return (start_1.begin(), start_2.begin());
    }

    auto end() const
    {
        return (start_1.end(), start_2.end());
    }
};
template <typename T, typename P>
zip_class<T, P> zip(T start1, P start2)
{
    return zip_class<T, P>(start1, start2);
}
} // namespace itertools
