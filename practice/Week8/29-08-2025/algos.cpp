#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Student {
  int id;
  std::string name;
};

int main() {
  std::vector<Student> students = {
      {1, "tarun"}, {2, "vikash"}, {3, "ravu"}, {4, "aryan"}, {5, "eve"}};

  auto it1 = std::find_if(students.begin(), students.end(),
                          [](const Student &s) { return s.id == 3; });
  if (it1 != students.end())
    std::cout << "Found by id: " << it1->name << "\n";

  auto it2 = std::find_if_not(students.begin(), students.end(),
                              [](const Student &s) { return s.id < 4; });
  if (it2 != students.end())
    std::cout << "First student with id >= 4: " << it2->name << "\n";

  auto it3 =
      std::find_if(students.begin(), students.end(), [](const Student &s) {
        return !s.name.empty() && s.name[0] == 'D';
      });
  if (it3 != students.end())
    std::cout << "Found by name starting with 'D': " << it3->name << "\n";

  auto it4 = std::find_if(students.begin() + 1, students.begin() + 4,
                          [](const Student &s) { return s.id == 5; });
  if (it4 != students.begin() + 4)
    std::cout << "Found in subrange: " << it4->name << "\n";
  else
    std::cout << "Not found in subrange\n";
}
