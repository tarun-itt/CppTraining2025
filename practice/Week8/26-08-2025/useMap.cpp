#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> students;

    students[101] = "Alice";
    students[102] = "Bob";
    students[103] = "Charlie";

    students[102] = "Bobby";

    for (auto &p : students) {
        cout << p.first << " -> " << p.second << "\n";
    }

    auto it = students.find(101);
    if (it != students.end()) {
        cout << "Found: " << it->first << " = " << it->second << "\n";
    }
}
