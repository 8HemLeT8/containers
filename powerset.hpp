#pragma once
#include <math.h>

/* 
Resources:
    http://www.ocoudert.com/blog/2010/07/07/how-to-write-abstract-iterators-in-c/
https://stackoverflow.com/questions/19923353/multiple-typename-arguments-in-c-template
https://en.cppreference.com/w/cpp/language/decltype
*/
using namespace std;
namespace itertools
{

template <typename T>
class powerset_class
{

private:
    T _set;

public:
    powerset_class(T s) : _set(s) {}

    class iterator
    {
    private:
        T from;
        T to;
        uint currIdx = 0; //      0 <= currIdx <= 2^set.size

    public:
        Itr(const T theSet, uint position)
        {
            currIdx = position;
            mySet = theSet;
        }
        // ++i
        iterator &operator++()
        {
            currIdx++;
            return *this;
        }
        // Dereference
        auto operator*() const {
				T element_iterator = from;
				vector<typename remove_const<typename remove_reference<decltype(*from)>::type>::type> ans;
				unsigned int i = currIdx;
				while (i != 0 && element_iterator != to){ 
					unsigned int r = i % 2;
					i = i >> 1; 
					if (r == 1)
						ans.emplace_back(*element_iterator);
					++element_iterator;
				}
				return ans;
			}
        /*
        auto &operator*() const
        {
            string ans = "{";
            bool last = true;

            int i = 0;
            for (auto piece : mySet)
            {
                if (currIdx & (1 << i))
                {
                    last = false;
                    ans += (piece + ",");
                    i++;
                }
            }
            if (last == false)
                ans = ans.substr(0, ans.length() - 1);
            ans += "}";

            return ans;
        }
*/
        // Not-Equal comparison
        bool operator!=(const Itr &rhs)
        {
            return mySet.end() != rhs.mySet.end();
        }
    };
    int setLen() const
    {
        int len = 0;
        for (auto sub : _set)
        {
            len++;
        }
        return len;
    }
    const auto begin() const
    {
        return Itr(_set, 0);
    }

    auto end() const
    {
        return Itr(_set, pow(2, setLen()));
    }
}; // namespace itertools

template <typename T>
powerset_class<T> powerset(T vset)
{
    return powerset_class<T>(vset);
}
} // namespace itertools