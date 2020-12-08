#include<iostream>
#include<vector>
#include<string>

using namespace std;

template <class Iterator, class T>
void increment(Iterator start, Iterator stop, const T & x)
{
    for (Iterator i = start; i < stop; i++)
        *i += x;
};

template <typename T>
T total(initializer_list<T> ilist)
{
    auto b = ilist.begin();
    auto e = ilist.end();
    T total = *b;
    for (auto i = b+1; i < e; i++)
        total += *i;

    return total;
};

template <class I, class UP, class O>
void print_if(I start, I stop, UP condition, O & out)
{
    for (I i = start; i < stop; i++)
        if (condition(*i))
            out << *i;
};

bool big(const string & s)
{
    return s.length() > 3;
};

void print(auto v)
{
    for(auto i : v)
        cout << i << ' ';

    cout << endl;
};

int main()
{
    vector<int> v1 = {1, 2, 3, 1, 5};

    increment(v1.begin(), v1.end(), 1);
    print(v1);

    int x = total({1,2,3,4,5});
    cout << x << endl;
    string y = total({string("hello"), string("hi")});
    cout << y << endl;

    vector<string> v2 = {"alice", "bob", "joe", "moe", "billy" };
    print_if(v2.begin(), v2.end(), big, cout);

    return 0;
}
