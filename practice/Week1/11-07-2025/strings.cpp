#include <iostream>
#include <string>
#include <cstring>

// operator overloading of string for this global space
std::string operator+(const std::string &lhs, const std::string &rhs)
{
    std::cout << lhs << " " << rhs << "\n";
    return std::string(rhs).append(lhs); // inverted the logic of concatenation
}

int main()
{

    // c style strings
    char str1[10] = "hellow"; // string literal
    memcpy(str1, "pops", 1);
    std::cout << str1 << "\n";

    const char *str2 = "kpopse"; // we cant have direct cahr* strings, they neeed to be constant
    // because string literals exist in read only memory, so they need to be constant
    std::cout << str2 << "\n";

    // std string
    std::cout << "\n\n";
    std::string s1 = "helloWorld";
    char *ptr_s1 = s1.data();        // data() returns non constant pointer to the string
    ptr_s1 = &s1[0];                 // same as above
    const char *ptr2_s1 = s1.data(); // constant pointer to s1 data, cannot change data using this pointer
    ptr_s1[0] = 'P';
    std::cout << ptr_s1 << "\n";

    std::string s2 = "Around the world";
    std::string s3 = s2;
    s2[0] = 'o';
    std::cout << "S3: " << s3 << "\n";
    std::cout << "Address of s2's data buffer: " << static_cast<const void *>(s2.data())
              << "  | Address of s2 object: " << &s2 << "\n";

    std::cout << "Address of s3's data buffer: " << static_cast<const void *>(s3.data())
              << "  | Address of s3 object: " << &s3 << "\n";

    // testing the overloaded string + operator
    std::cout << "\n\n";
    std::string hello = "hello";
    std::string world = "world";
    std::string str3 = "pops";
    std::string concat = (hello + world) + str3; // works for first 2 strings, but 3rd one didnt get appended?
    std::cout << concat << "\n";
}