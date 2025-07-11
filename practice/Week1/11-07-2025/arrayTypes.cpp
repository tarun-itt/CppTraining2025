#include <iostream>
#include <vector>
int *modifyVector(std::vector<int> &v)
{
    v[0] = 1000;
    std::vector<int> vv{394, 23, 23, 12, 87};
    int *dynamicArr = new int[7]{10, 23};

    std::cout << "Address inside function: " << &v << std::endl;
    return dynamicArr;
};

int main()
{
    std::vector<int> v1{1, 23, 4, 52, 12, 45, 9};
    std::cout << "Address v1: " << &v1 << "\n";
    int *p = modifyVector(v1);
    std::cout << *p << std::endl;
    return 0;
}