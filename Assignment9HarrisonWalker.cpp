#include<iostream>
#include "Assignment8.h"
#include "Assignment8.cpp"


int main()
{
    Queue<int> qu;
    qu.push(12);
    qu.push(24);
    qu.push(36);
    qu.pop();
    qu.print();
    std::cout << qu.front() << ' ' << qu.size() << std::endl;

    auto a = qu;
    a.print();
    a.clear();
    std::cout << a.empty() << std::endl;

    return 0;
}

