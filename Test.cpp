#include <iostream>
#include <string>
#include "chain.hpp"
#include "powerset.hpp"
#include "product.hpp"
#include "range.hpp"
#include "zip.hpp"
#include "badkan.hpp"
using namespace std;
using namespace itertools;

template <typename Iterable>
string iterable_to_string(const Iterable &iterable)
{
    ostringstream ostr;
    for (decltype(*iterable.begin()) i : iterable)
    {
        ostr << i << ",";
    }
    return ostr.str();
}

int main()
{

    // SOME TESTS WERENT ADDED BECAUSE THE IMPLEMENTATION IS NEEDED
    badkan::TestCase testcase;
    int grade = 0;
    int signal = setjmp(badkan::longjmp_buffer);
    if (signal == 0)
    {

        testcase.setname("Range")
            .CHECK_OUTPUT(iterable_to_string(range(5, 9)), "5,6,7,8,")
            .CHECK_OUTPUT(iterable_to_string(range(5.1, 9.1)), "5.1,6.1,7.1,8.1,")
            .CHECK_OUTPUT(iterable_to_string(range('a', 'e')), "a,b,c,d,")
            .CHECK_OUTPUT(iterable_to_string(range('a', 'z')), "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,");

        testcase.setname("Chain")
            .CHECK_OUTPUT(iterable_to_string(chain(range(1, 4), range(5, 8))), "1,2,3,5,6,7,")
            .CHECK_OUTPUT(iterable_to_string(chain(range(1.5, 4.5), range(5.5, 8.5))), "1.5,2.5,3.5,5.5,6.5,7.5,")
            .CHECK_OUTPUT(iterable_to_string(chain(range('a', 'e'), string("hello"))), "a,b,c,d,h,e,l,l,o,")
            .CHECK_OUTPUT(iterable_to_string(chain(string("az"), range('a', 'z'))), "a,z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,");

        testcase.setname("Zip")
            .CHECK_OUTPUT(iterable_to_string(zip(range(1, 6), string("world"))), "1,w,2,o,3,r,4,l,5,d,")
            .CHECK_OUTPUT(iterable_to_string(zip(zip(range(1, 4), string("xyz")), zip(string("abc"), range(6, 9)))), "1,x,a,6,2,y,b,7,3,z,c,8,")
            .CHECK_OUTPUT(iterable_to_string(zip(range(1, 3), string("ac"))), "1,a,2,c,");

        testcase.setname("Product")
            .CHECK_OUTPUT(iterable_to_string(product(range(1, 4), string("hello"))), "1,h,1,e,1,l,1,l,1,o,2,h,2,e,2,l,2,l,2,o,3,h,3,e,3,l,3,l,3,o,")
            .CHECK_OUTPUT(iterable_to_string(product(range(1, 4), string("ad"))), "1,a,1,d,2,a,2,d,3,a,3,d,")
            .CHECK_OUTPUT(iterable_to_string(product(range(1, 3), range(1, 3))), "1,1,1,2,2,1,2,2,");

        testcase.setname("Powerset")
            .CHECK_OUTPUT(iterable_to_string(powerset(range(1, 4))), "{},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3},")
            .CHECK_OUTPUT(iterable_to_string(powerset(chain(range('a', 'c'), range('x', 'z')))), "{},{a},{b},{a,b},{x},{a,x},{b,x},{a,b,x},{y},{a,y},{b,y},{a,b,y},{x,y},{a,x,y},{b,x,y},{a,b,x,y},");

        grade = testcase.grade();
    }
    else
    {
        testcase.print_signal(signal);
        grade = 0;
    }
    cout << "Your grade is: " << grade << endl;
    return 0;
}