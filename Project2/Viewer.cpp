#include "Viewer.h"

using namespace std;

bool is_number(const std::string & s)
{
    bool T_F = true;
    for(char x:s)
    {
        if(!isdigit(x))
           {
               T_F = false;
               break;
           }
    }
    return T_F;
}

void Viewer::run()
{
    ifstream in;
    string lname;
    Person player;
    string yr;
    auto i = players_.begin();
    in.open("save.txt");
    if(!in)
    {
        in.close();
        ofstream o;
        o.open("save.txt");
        o.close();
        in.open("save.txt");
    }
    in >> year_;
    if(!year_ > 0)
    {
        cout << "Please Input a Year: ";
        cin >> yr;
        while (is_number(yr)==false)
        {
            cout << "please input valid year: ";
            cin >> yr;
        }
        year_=stoi(yr);
    }

    while(in >> lname >> player.fname_ >> player.category_ >> player.year_ >> player.status_)
    {
        players_.insert(i, {lname, player});
        ++i;
    }
    in.close();

    done_r_ = false;
    char command;
    while(!done_r_)
    {
        system(clear_command);
        cout << error_message_ <<"\n";
        error_message_.clear();
        cout << "Commands:\n\n1) Start a new season\n2) Add a player\n3) Search for players\n4) Print a list of players\n5) Display statistics\n6) Stop the program\n\nCommand: ";
        cin >> command;

        execute_r(command);
    }
}

void Viewer::execute_r(const char & c)
{
    switch (c)
    {
        case '1' : {
            char choice;
            string year;
            cout << "All players will be deleted, are you sure? Y/N \n";
            cin >> choice;
            if(choice == 'Y'||choice == 'y')
            {
                cout << "Input the year: ";
                cin >> year;
                while(!is_number(year))
                {
                    cout << "Please enter a number: ";
                    cin >> year;
                }
                year_=stoi(year);
                players_.clear();
            }
            break;
        }

        case '2' : {
            add_player();
            break;
        }

        case '3' : {
            search_p();
            break;
        }

        case '4' : {
            std::string filename;
            cout << "Input Filename: ";
            cin >> filename;

            ofstream new_file(filename);
            print_to_file(new_file);
            new_file.close();

            break;
        }

        case '5' :{
            system(clear_command);
            string input;
            while(input.empty())
            {
                int category = 6;
                cout << "Total Players: " << players_.size() << "\n";
                cout << "\n";
                while (category <= 18)
                {
                    get_stats(category);
                    if(paid_!=0 || unpaid_!=0)
                    {
                        if(category == 18)
                        {
                            cout << "U17:\n";
                        }
                        else
                        {
                            cout << "U"<<category<<":\n";
                        }
                        cout << "paid: " << paid_ << "\n";
                        cout << "unpaid: " << unpaid_ << "\n";
                        cout << "\n";
                    }
                    paid_=unpaid_=0;
                    category = category + 2;
                }
                cout << "Enter any Character to Continue\n";
                cin >> input;
            }
            break;
        }

        case '6' : {
            ofstream save_file("save.txt");
            save_file << year_ << "\n";
            search_results_ = players_;
            print_s(save_file);
            save_file.close();
            done_r_ = true;
            break;
        }

        default:{error_message_ = "command does not exist\n"; break;}
    }
}

void Viewer::add_player()
{
    Person new_person;
    string yob;
    string category;
    string lastN;
    int category_num;
    cout << "Last Name: ";
    cin >> lastN;
    cout << "First Name: ";
    cin >> new_person.fname_;
    cout << "Year of birth: "; //add check
    cin >> yob;
    bool validating = true;
    while (validating)
    {
        if(!is_number(yob))
        {
            cout << "Please input a number: ";
            cin >> yob;
        }
        else if(year_ - stoi(yob) < 4 || year_ - stoi(yob) > 16)
        {
            cout << "Year would disqualify player from season, please try again: ";
            cin >> yob;
        }
        else
        {
            new_person.year_=stoi(yob);
            category_num = year_-new_person.year_;

            if(category_num < 6){category_num=6;}
            else if(category_num < 8){category_num=8;}
            else if(category_num < 10){category_num=10;}
            else if(category_num < 12){category_num=12;}
            else if(category_num < 14){category_num=14;}
            else if(category_num < 17){category_num=17;}
            else{
                validating = true;
                cout << "Player does not fit in any category in the current year " << year_ << "\n";
                cout << "Input valid year: ";
                cin >> yob;
            }
            validating = false;
        }
    }

    ostringstream os(category);
    os << "U" << (category_num);
    new_person.category_ = os.str();

    cout << "Registration Status(paid or unpaid): ";
    cin >> new_person.status_;

    while (new_person.status_!="paid" && new_person.status_!= "unpaid")
    {
        cout << "Invalid status entered, please enter paid or unpaid: ";
        cin >> new_person.status_;
    }

    players_.insert({lastN,new_person});
}

void Viewer::get_stats(int category)
{
    for (auto index = players_.begin(); index != players_.end(); index++)
    {
        if((year_-((index->second).year_))<category && (year_-((index->second).year_)) >= category-2 && (year_-((index->second).year_)) != category)
        {
            if(index->second.status_ == "paid")
            {
                paid_++;
            }
            else
            {
                unpaid_++;
            }
        }
    }
}

void Viewer::print_to_file(ofstream & file)
{
    auto dummy = players_;
    vector<string> v = {"U6", "U8", "U10", "U12", "U14", "U17"};
    for(string cat : v)
    {
        search_results_ = dummy;
        auto d = dummy.begin();
        for (auto i = search_results_.begin(); i != search_results_.end(); ++i)
        {
            if (i->second.category_ == cat)
            {
                file << i->first << " " << i->second.fname_ << " " << i->second.category_ << " " << i->second.year_ << " " << i->second.status_ << "\n";
                dummy.erase(d);
            }
            ++d;
        }
    }
}

void Viewer::search_p()
{
    vector<string> v(6);
    search_results_.clear();

    system("cls");
    cout << "Items: First Name, Last Name, Keyword, Year of Birth, Registration Status, Category\n\n";
    cout << "Names must be exact, Keyword is any sequence of characters in a name\n\n";
    cout << "Year of Birth should be a four digit number, Registration Status must be exact\n\n";
    cout << "Category should be a 'U' followed by a number\n\n";
    cout << "Each item should be entered in order. If you do not want to enter an item, use a '-'\n\n";
    cout << "Search: ";
    cin >> v[0] >> v[1] >> v[2] >> v[3] >> v[4] >> v[5];

    search_ln(v[1]);
    search_fn(v[0]);
    search_k(v[2]);
    search_y(v[3]);
    search_s(v[4]);
    search_c(v[5]);

    display();
}

void Viewer::display()
{
    if(!search_results_.empty())
    {
        int current = 1;
        int total = search_results_.size();
        auto i = search_results_.begin();
        char command;
        done_s_ = false;
        while(!done_s_)
        {
            system("cls");
            cout << "Player " << current << " out of " << total << "\n\n";
            cout << "Name: " << i->first << ", " << i->second.fname_ << endl;
            cout << "Year of Birth: " << i->second.year_ << endl;
            cout << "Registration Status: " << i->second.status_ << endl;
            cout << "Category: " << i->second.category_ << "\n\n";
            cout << "Commands: \n";
            cout << "1) Search for players\n2) Move to next player\n3) Move to previous player\n4) Edit a player's information\n5) Print a list of players\n6) Exit the search results view\n7) Stop the program\n\n";
            cin >> command;
            execute_s(command, current, total, i);
        }
    }
    else
    {
        string c;
        cout << "No results found. Please enter a character to acknowledge: ";
        cin >> c;
    }
}

void Viewer::execute_s(const char & c, int & n, const int & t, std::map<std::string, Person>::iterator & i)
{
    switch (c)
    {
        case '1' : {
            search_p();
            break;
        }

        case '2' : {
            next(n, t, i);
            break;
        }

        case '3' : {
            previous(n, t, i);
            break;
        }

        case '4' : {
            edit(n, i);
            break;
        }

        case '5' : {
            std::string filename;
            cout << "Input Filename: ";
            cin >> filename;

            ofstream new_file(filename);
            print_s(new_file);
            new_file.close();
            break;
        }

        case '6' : {
            done_s_ = true;
            break;
        }

        case '7' : {
            ofstream save_file("save.txt");
            save_file << year_ << "\n";
            print_to_file(save_file);
            save_file.close();
            done_r_ = true;
            done_s_ = true;
            break;
        }
    }
}

void Viewer::next(int & n, const int & t, std::map<std::string, Person>::iterator & i)
{
    ++n;
    if(n > t)
    {
        n = 1;
        i = search_results_.begin();
    }
    else
        ++i;
}

void Viewer::previous(int & n, const int & t, std::map<std::string, Person>::iterator & i)
{
    --n;
    if(n < 1)
    {
        n = t;
        i = --search_results_.end();
    }
    else
        --i;
}

void Viewer::edit(int & n, std::map<std::string, Person>::iterator & i)
{
    done_e_ = false;
    char command;
    while(!done_e_)
    {
        system("cls");
        cout << i->second.fname_ << " " << i->first << " " << i->second.year_ << " " << i->second.status_ << "\n\n";
        cout << "1) Change first name\n2) Change last name\n3) Change birth year\n4) Change status\n5) Done\n\n";
        cout << "Change: ";
        cin >> command;
        auto x = players_.begin();
        for(x = players_.begin(); x->first != i->first || x->second.fname_ != i->second.fname_ ; ++x) {}
        execute_e(command, n, i, x);
    }
}

inline void Viewer::print_s(ofstream & file)
{
    for (auto p : search_results_)
        file << p.first << " " << p.second.fname_ << " " << p.second.category_ << " " << p.second.year_ << " " << p.second.status_ << "\n";
}

void Viewer::execute_e(const char & c, int & n, std::map<std::string, Person>::iterator & i, std::map<std::string, Person>::iterator & x)
{
    switch (c)
    {
        case '1' : {
            edit_f(i, x);
            break;
        }

        case '2' : {
            edit_l(i, x);
            n = 1;
            for(auto x = search_results_.begin(); x != i; ++x)
                ++n;
            break;
        }

        case '3' : {
            edit_y(i, x);
            break;
        }

        case '4' : {
            edit_s(i, x);
            break;
        }

        case '5' : {
            done_e_ = true;
            break;
        }
    }
}

void Viewer::search_ln(const string & s)
{
    if(s != "-")
    {
        auto p = players_.equal_range(s);
        for(auto i = p.first; i != p.second; ++i)
            search_results_.insert(*i);
    }
    else
        search_results_ = players_;
}

void Viewer::search_fn(const string & s)
{
    map<string, Person> dummy;
    if(s != "-")
    {
        for(auto p : search_results_)
        {
            if(p.second.fname_ == s)
                dummy.insert(p);
        }
        search_results_ = dummy;
    }
}

void Viewer::search_k(const string & s)
{
    map<string, Person> dummy;
    if(s != "-")
    {
        for(auto p : search_results_)
        {
            if(p.second.fname_.find(s) != -1 || p.first.find(s) != -1)
                dummy.insert(p);
        }
        search_results_ = dummy;
    }
}

void Viewer::search_y(const string & s)
{
    map<string, Person> dummy;
    if(s != "-")
    {
        for(auto p : search_results_)
        {
            if(p.second.year_ == stoi(s))
                dummy.insert(p);
        }
        search_results_ = dummy;
    }
}

void Viewer::search_s(const string & s)
{
    map<string, Person> dummy;
    if(s != "-")
    {
        for(auto p : search_results_)
        {
            if(p.second.status_ == s)
                dummy.insert(p);
        }
        search_results_ = dummy;
    }
}

void Viewer::search_c(const string & s)
{
    map<string, Person> dummy;
    if(s != "-")
    {
        for(auto p : search_results_)
        {
            if(p.second.category_ == s)
                dummy.insert(p);
        }
        search_results_ = dummy;
    }
}

void Viewer::edit_f(const std::map<std::string, Person>::iterator & i, const std::map<std::string, Person>::iterator & x)
{
    string name;
    cout << "Enter a new first name: ";
    cin >> name;
    x->second.fname_ = name;
    i->second.fname_ = name;
}

void Viewer::edit_l(std::map<std::string, Person>::iterator & i, std::map<std::string, Person>::iterator & x)
{
    pair<string, Person> holder = *i;
    cout << "Enter a new last name: ";
    cin >> holder.first;
    players_.erase(x);
    players_.insert(holder);
    search_results_.erase(i);
    search_results_.insert(holder);
}

void Viewer::edit_y(const std::map<std::string, Person>::iterator & i, const std::map<std::string, Person>::iterator & x)
{
    bool checking = true;
    string year;
    while(checking)
    {
        cout << "Enter a new birth year: ";
        checking = false;
        cin >> year;
        for(int x = 0; x < year.length(); ++x)
        {
            if(!isdigit(year[x]))
            {
                checking = true;
                cout << "Not a number, try again\n";
            }
        }
        i->second.year_ = stoi(year);
        if(year_ - i->second.year_ < 4 || year_ - i->second.year_ > 16)
        {
            checking = true;
            cout << "Year would disqualify player from current season, try again\n";
        }
    }

    if(year_ - i->second.year_ < 6)
    {
        i->second.category_ = "U6";
        x->second.category_ = "U6";
    }
    else if(year_ - i->second.year_ < 8)
    {
        i->second.category_ = "U8";
        x->second.category_ = "U8";
    }
    else if(year_ - i->second.year_ < 10)
    {
        i->second.category_ = "U10";
        x->second.category_ = "U10";
    }
    else if(year_ - i->second.year_ < 12)
    {
        i->second.category_ = "U12";
        x->second.category_ = "U12";
    }
    else if(year_ - i->second.year_ < 14)
    {
        i->second.category_ = "U14";
        x->second.category_ = "U14";
    }
    else if(year_ - i->second.year_ < 17)
    {
        i->second.category_ = "U17";
        x->second.category_ = "U17";
    }
}

void Viewer::edit_s(const std::map<std::string, Person>::iterator & i, const std::map<std::string, Person>::iterator & x)
{
    string status;
    cout << "Enter a new status: ";
    cin >> status;
    while (status!="paid" && status!= "unpaid")
    {
        cout << "Invalid status entered, please enter paid or unpaid: ";
        cin >> status;
    }
    i->second.status_ = status;
    x->second.status_ = status;
}
