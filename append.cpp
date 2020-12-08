#include<iostream>
#include<vector>

using namespace std;

auto append(auto & v1, auto & v2)
{
    for(auto i : v1)
        v2.push_back(i);

    return v2;
};

int main()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {6, 7, 8, 9, 10};

    auto v3 = append(v1,v2);

    for(int i : v2)
        cout << i << ' ';

    return 0;
}
