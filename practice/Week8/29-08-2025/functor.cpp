#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Student {
    std::string name;
    int avgScore;
    char grade;

    public:
    Student() = default;
    Student(std::string name, int score, char grade):name(name), avgScore(score),grade(grade) {std::cout<<"Constructor Initialidzed "<<name<<std::endl;}
    Student(const Student& obj):name(obj.name),avgScore(obj.avgScore),grade(obj.grade){std::cout<<"Copy Constructor Called: "<<obj.name<<std::endl;}
    Student(const Student&& obj):name(obj.name),avgScore(obj.avgScore),grade(obj.grade){std::cout<<"Move Construcotr called: "<<obj.name<<std::endl;}
    ~Student(){std::cout<<"Destructor Called: "<<name<<std::endl;}
};

int main(){
    //std::vector<Student> students{Student("tarun",50,'D'), Student("nikhil",90,'A'),Student("sumit",70,'B'),Student("varman",79,'B')};
    std::vector<Student> students;
    students.reserve(10);
    students.push_back(Student("tarun",76,'A'));
 //   students.push_back(Student("varun",87,'B'));    getchar();
    return 0;
}