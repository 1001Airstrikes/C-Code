#include<iostream>
#include<string>

class String
{
public:
    String() : buffer_(nullptr), size_(0) {}
    String(const char* c_str);
    String(const String & s);
    ~String() {delete [] buffer_;}

    int length() const {return size_;}
    char & operator[](int i) {return buffer_[i];}
    const char & operator[](int i) const {return buffer_[i];}
    void clear();
    String operator+(String s);
    String & operator=(String s);
    const char * c_str();
    void print();

private:
    char * get_new_buffer(int n) const;

    char * buffer_;
    int size_;
};

String::String(const char * c_str)
{
    int i;
    for(i = 0; c_str[i] != '\0'; i++) {}
    buffer_ = get_new_buffer(i);
    std::copy(c_str, c_str+i, buffer_);
    size_ = i;
}

String::String(const String & s)
{
    buffer_ = get_new_buffer(s.length());
    for(int i = 0; i < s.length(); i++)
        buffer_[i] = s[i];
    size_ = s.length();
}

inline char * String::get_new_buffer(int n) const
{
    return (n == 0 ? nullptr : new char[n]{});
}

inline void String::clear()
{
    delete [] buffer_;
    buffer_ = nullptr;
    size_ = 0;
}

String String::operator+(String s)
{
    String new_string;
    new_string.buffer_ = get_new_buffer(size_+s.length());
    for(int i = 0; i < size_; i++)
    {
        new_string[i] = buffer_[i];
    }
    for(int i = 0; i < s.length(); i++)
    {
        new_string[size_+i] = s[i];
    }
    new_string.size_ = size_+s.length();

    return new_string;
}

String & String::operator=(String s)
{
    char * new_buffer = get_new_buffer(s.length());
    for(int i = 0; i < size_; i++)
        new_buffer[i] = s[i];
    delete [] buffer_;
    buffer_ = new_buffer;
    size_ = s.length();

    return *this;
}

const char * String::c_str()
{
    std::string s = "";
    for(int i = 0; i < size_; i++)
        s += buffer_[i];
    return s.c_str();
}

inline void String::print()
{
    for(int i = 0; i < size_; i++)
        std::cout << buffer_[i];
    std::cout << std::endl;
}

int main()
{
    std::string x = "Hello";
    const char* cs = x.c_str();
    String s(cs);
    s.print();
    String s2(s);
    s2.print();
    s.clear();
    s.print();
    String s3 = s2 + s2;
    s3.print();
    cs = s3.c_str();
    std::cout << cs[0] << std::endl;

    return 0;
}

