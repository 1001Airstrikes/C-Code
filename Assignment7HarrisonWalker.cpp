#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<map>

using namespace std;
using BookMap = map<string,int>;

class StartsWith
{
public:
    StartsWith(char c0) : c(c0) {}
    bool operator() (string s) { return s[0] == c;}

private:
    char c;
};

template <class List>
void print(const List & ls, const int & n)
{
    for (int i = 0; i < n && i < ls.size(); i++)
        cout << ls[i] << endl;
};

void read_books(BookMap & m, const string & file_name)
{
    ifstream in;
    in.open(file_name);
    string line1;
    string line2;
    for(getline(in, line1); getline(in, line2); getline(in, line1))
    {
        m.insert({line1, stoi(line2)});
    }
};

void print_recent(const BookMap & m, const int & year)
{
    for (auto i = m.begin(); i != m.end(); i++)
        if ((*i).second > year)
            cout << (*i).first << endl;
};

int main()
{
    vector<string> v = {"alice", "bob", "archie", ""};
    int x = count_if(v.begin(), v.end(), StartsWith('a'));
    cout << x << "\n\n";

    print(v, 5);

    BookMap m;
    read_books(m, "test.txt");
    print_recent(m, 2000);

    return 0;
}

