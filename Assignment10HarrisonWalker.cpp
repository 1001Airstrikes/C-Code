#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

template<class T>
int seq_search(const T a[], int start, int stop, const T & e)
{
    if(a[start] == e)
        return start;
    else if(start == stop)
        return -1;
    else
        return seq_search(a, start+1, stop, e);
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    cout << seq_search(a, 0, 4, 3) << endl;

    vector<int> v = {11, 27, 28, 30, 36, 42, 58, 65};
    cout << binary_search(v.begin(), v.end(), 27) << endl;
    cout << binary_search(v.begin(), v.end(), 50) << endl;

    vector<int> c = {34, 12, 53, 92, 61, 17, 20};
    sort(c.begin(), c.end());
    for (int i : c)
        cout << i << ' ';

    return 0;
}
