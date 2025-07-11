#include <iostream>
#include <string.h>

bool IsDigit(char currentChar)
{
    return (currentChar >= '0' && currentChar <= '9');
}

bool ValidateInput(std::string input)
{
    for (char currentChar : input)
    {
        if (!IsDigit(currentChar))
            return 0;
    }
    return 1;
}

int StringToInt(std::string input)
{
    int num = 0;
    for (char currentChar : input)
    {
        num = (num * 10) + (currentChar - '0');
    }

    return num;
}

void printPattern(int len, int width, int spaceStart, int spaceEnd, int patternHeight)
{
    std::string toPrint[] = {"1", "0"};
    int ptr = 0;

    for (int i = 0; i < len; i++, ptr = 0)
    {
        for (int j = 0; j < width; j++)
        {
            if (j >= spaceStart && j <= spaceEnd)
            {
                std::cout << "  ";
                ptr = 0;
            }
            else if (j < spaceStart || j > spaceEnd)
            {
                std::cout << toPrint[ptr] << " ";
                ptr = (ptr + 1) % 2; 
            }
        }

        //increment logic
        if (i < patternHeight - 1)
        {
            spaceStart++;
            spaceEnd--;
        }
        else
        {
            spaceStart--;
            spaceEnd++;
        }
        std::cout << "\n";
    }
}
int main()
{
    std::string input;
    std::cout << "Enter Input: ";
    std::cin >> input;

    while (!ValidateInput(input))
    {
        std::cout << "Please Enter a valid number (positive integer): ";
        std::cin >> input;
    }
    int len = StringToInt(input);

    len = (len * 2) + 1;

    int spaceStart = 1; // space start

    int height = (len + 1) / 2; // height of the triangular space

    int width = len % 4 == 1 ? len : len + 1; //

    int spaceEnd = width - 2; // space end

    printPattern(len, width, spaceStart, spaceEnd, height);

    return 0;
}