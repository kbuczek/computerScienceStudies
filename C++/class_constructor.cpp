#include<iostream>
#include<string>

class grade_book {
    public:
    void set_name(std::string name) { course_name = name; }
    std::string get_name() { return course_name; }
    void display() const { std::cout << course_name << std::endl; }
    private:
    std::string course_name;
    friend void print_name(const grade_book&);
};

void print_name(const grade_book& b)
{
    //b.display();
    std::cout << b.course_name << std::endl;
}

int main() {
    grade_book b;
    b.set_name ("c++");
    //std::cout << b.get_name() << std:endl;
    print_name(b);
}
