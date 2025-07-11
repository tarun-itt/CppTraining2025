#include <iostream>
#include <array>
#include <algorithm>

int main()
{
    std::array<int, 5> numbers = {10, 20, 5, 40, 30};

    std::cout << "element at 2: " << numbers[2] << "\n";
    std::cout << "element at 2: " << numbers.at(2) << "\n";

    try
    {
        std::cout << "Trying out-of-bounds: " << numbers[10] << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }

    try
    {
        std::cout << "Trying out-of-bounds: " << numbers.at(10) << "\n";
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "Size: " << numbers.size() << "\n";

    std::sort(numbers.begin(), numbers.end());

    std::cout << "Sorted: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    numbers[0] = 99;

    for (const auto &n : numbers)
        std::cout << n << " ";
    std::cout << "\n";

    numbers.fill(42);
    std::cout << "After fill: ";
    for (auto v : numbers)
        std::cout << v << " ";
    std::cout << "\n";

    return 0;
}
