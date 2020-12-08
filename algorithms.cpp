#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void print(auto v)
{
    for(auto i : v)
        cout << i << ' ';

    cout << endl;
};

int main()
{
    vector<int> v1 = {1, 2, 3, 1, 5};
    vector<string> v2 = {"alice", "bob", "joe", "moe", "joe" };

    cout << "Before Changes\n";
    print(v1);
    print(v2);

    replace(v1.begin(), v1.end(), 1, 99);
    replace(v2.begin(), v2.end(), string("joe"), string("pickle"));

    cout << "\nAfter Replace\n";
    print(v1);
    print(v2);

    auto i1 = max_element(v1.begin(), v1.end());
    auto i2 = max_element(v2.begin(), v2.end());

    cout << "\nMax v1: " << *i1 << "\nMax v2: " << *i2 << endl;

    return 0;
}
