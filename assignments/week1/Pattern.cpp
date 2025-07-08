#include <iostream>
#include <string.h>

int main()
{

    int len = 13;

    int s_start = 1;     // space start
    int s_end = len - 2; // space end

    int height = (len + 1) / 2; // height of the triangular space

    std::string to_print[] = {"1", "0"};
    int ptr = 0;

    for (int i = 0; i < len; i++, ptr = 0)
    {
        for (int j = 0; j < len; j++)
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