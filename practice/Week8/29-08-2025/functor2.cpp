#include <iostream>
#include <algorithm>
#include <vector>

class Student {
    public:
    std::string name;
    int age;
    int avgScore;
    char grade;

    public:
    Student() = default;
    Student(std::string name, int age, int score, char grade):name(name), age(age),avgScore(score),grade(grade) {std::cout<<"Constructor Initialidzed "<<name<<std::endl;}
    Student(const Student& obj):name(obj.name),age(obj.age),avgScore(obj.avgScore),grade(obj.grade){std::cout<<"Copy Constructor Called: "<<obj.name<<std::endl;}
//     Student(Student&& obj) noexcept:name(std::move(obj.name)),age(obj.age),avgScore(obj.avgScore),grade(obj.grade){std::cout<<"Move Construcotr called: "<<obj.name<<std::endl;obj.age = 0;
// obj.avgScore = 0;
// obj.grade = '\0';
//  }
    ~Student(){std::cout<<"Destructor Called: "<<name<<std::endl;}
};



enum class SortField { Name, Age, Score };

struct StudentComparator {
    SortField defaultSortField;
    bool ascending;

    StudentComparator(SortField f= SortField::Age, bool isAscending = true)
      : defaultSortField(f), ascending(isAscending) {}

    bool operator()(const Student& a, const Student& b) const {
        bool result;
        switch (defaultSortField) {
            case SortField::Age: result = a.age < b.age;
            break;
            case SortField::Name: result = a.name < b.name;
            break;
            case SortField::Score: result = a.avgScore < b.avgScore;
            break;

        }
        return ascending ? result : !result;
    }

    void changeDefaultSorting(SortField f){
        this->defaultSortField = f;
    }
};

int main(){
    StudentComparator comp(SortField::Age,true);
    std::vector<Student> students{Student("tarun",19,50,'D'), Student("nikhil",18,90,'A'),Student("sumit",13,70,'B'),Student("varman",17,79,'B')};

    std::cout<<"Before Sorting By Age: \n";
    for(auto& v:students){
        std::cout<<v.name<<" "<<v.age<<" "<<v.avgScore<<" "<<v.grade<<" \n"; 
    }

    std::sort(students.begin(), students.end(),comp);

        std::cout<<"After Sorting By Age: \n";
    for(auto& v:students){
        std::cout<<v.name<<" "<<v.age<<" "<<v.avgScore<<" "<<v.grade<<" \n"; 
    }

    return 0;
}
