#include <iostream>
#include <string.h>

bool IsDigit(char ch){
    return (ch >= 48 && ch <= 57); // checks the ascii range of numerical digits
}

bool ValidateInput(const std::string input){
    for(char c: input){
        if(!IsDigit(c)) return 0;
    }
    return 1;
}

int StringToInt(std::string input){
    int num = 0;
    for(char c:input){
        num = (num*10) + (c-'0');
    }

    return num;
}


int main()
{
    std::string input;
    std::cout << "Enter Input: ";
    std::cin >> input;

    while (!ValidateInput(input))
    {
        std::cout<<"Please Enter a valid number (positive integer): ";
        std::cin>> input;
    }
    int len = StringToInt(input);

    len = (len*2) + 1;

    int s_start = 1;     // space start

    int height = (len + 1) / 2; // height of the triangular space

    std::string to_print[] = {"1", "0"};
    int ptr = 0;
    int width = len%4 == 1 ? len : len+1; // 

    int s_end = width - 2; // space end

    for (int i = 0; i < len; i++, ptr = 0)
    {
        for (int j = 0; j < width; j++)
        {
            if (j >= s_start && j <= s_end)
            {
                std::cout << "  ";
                ptr = 0;
            }
            else if (j < s_start || j > s_end)
            {
                std::cout << to_print[ptr] << " ";
                ptr = (ptr + 1) % 2; // reset to print 1 after every iteration
            }
        }

        // increment logic for upper triange (space)
        if (i < height - 1)
        {
            s_start++;
            s_end--;
        }
        // for lower triangle  (space)
        else
        {
            s_start--;
            s_end++;
        }
        std::cout << "\n"; //endline for next row
    }

    return 0;
}