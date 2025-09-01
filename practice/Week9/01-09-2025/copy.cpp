#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

class Student {
public:
    int id;
    std::string name;

    Student(int i, const std::string& n) : id(i), name(n) {}
};

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "ID: " << s.id << ", Name: " << s.name;
    return os;
}

int main() {
  std::vector<Student> students = {
      {1, "tarun"}, {2, "vikash"}, {3, "ravu"}, {4, "aryan"}, {5, "eve"}};

    std::copy(students.begin(), students.end(),
              std::ostream_iterator<Student>(std::cout, "\n")); //can write complete vector to screen using copy

    try{
        std::ofstream writer("sampleFile.txt");
        if(writer.is_open()){
            std::copy(students.begin(), students.end(),
              std::ostream_iterator<Student>(writer, "\n")); // i can even write to a file directly using copy algo

        }else{
            std::cout<<"File not opened\n";
        }
    }catch(...){

    }
    
    return 0;
}
