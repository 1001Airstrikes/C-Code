#ifndef _Viewer_h_
#define _Viewer_h_

#include<iostream>
#include<map>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<vector>
#include "Person.h"
const char clear_command[] = "cls";

class Viewer
{
public:
    void run();

    void execute_r(const char & c);
    void execute_s(const char & c, int & n, const int & t, std::map<std::string, Person>::iterator & i);
    void execute_e(const char & c, int & n, std::map<std::string, Person>::iterator & i, std::map<std::string, Person>::iterator & x);

    void add_player();

    void get_stats(int category);

    void search_p();

    void search_ln(const std::string & s);
    void search_fn(const std::string & s);
    void search_k(const std::string & s);
    void search_y(const std::string & s);
    void search_s(const std::string & s);
    void search_c(const std::string & s);

    void print_to_file(std::ofstream & file);

    void print_s(std::ofstream & file);

    void display();

    void next(int & n, const int & t, std::map<std::string, Person>::iterator & i);
    void previous(int & n, const int & t, std::map<std::string, Person>::iterator & i);

    void edit(int & n, std::map<std::string, Person>::iterator & i);

    void edit_f(const std::map<std::string, Person>::iterator & i, const std::map<std::string, Person>::iterator & x);
    void edit_l(std::map<std::string, Person>::iterator & i, std::map<std::string, Person>::iterator & x);
    void edit_y(const std::map<std::string, Person>::iterator & i, const std::map<std::string, Person>::iterator & x);
    void edit_s(const std::map<std::string, Person>::iterator & i, const std::map<std::string, Person>::iterator & x);

private:
    std::map<std::string, Person> players_;
    std::map<std::string, Person> search_results_;
    bool done_r_ = false;
    bool done_s_ = false;
    bool done_e_ = false;
    int year_=0;
    int paid_=0;
    int unpaid_=0;
    std::string error_message_;
};

#endif
