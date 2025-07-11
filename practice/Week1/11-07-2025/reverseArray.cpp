#include <iostream>
#include <array>

int main()
{
    std::array<int, 7> myArray = {1, 23, 4, 5343, 12, 653, 64};

    for (int i = 0, j = myArray.size() - 1; i < j; i++, j--)
    {
        std::swap(myArray[i], myArray[j]);
    }

    // printing the array
    for (int i = 0; i < myArray.size(); i++)
    {
        std::cout << myArray[i] << " ";
    }
    return 0;
}