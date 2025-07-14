#include <iostream>
#include <cstring>

int main() {
    char names[3][10] = { "Bob", "Alice", "Eve" };

    for (int i = 0; i < 3; ++i) {
        std::cout << names[i] << " has length " << strlen(names[i]) << "\n";
    }

    strcpy(names[0], "Tom");  

    std::cout << "changed: " << names[0] << "\n";

    char str1[] = "hello";
    char str2[] = "world";
    char str3[] = "there";
      char *ptr[3];
      

    ptr[0] = str1;
    ptr[1] = str2;
    ptr[2] = str3;

  

    std::cout<<*ptr<<std::endl;
    return 0;
}
