#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

int flag = 0; // 0 0 0 0 => exponentSign, exponent, dot, sign

enum class ParseResult
{
    FALSE,
    TRUE,
    INVALID
};

enum FlagBits
{
    SIGN = 1 << 0,
    DOT = 1 << 1,
    EXPONENT = 1 << 2,
    EXP_SIGN = 1 << 3
};

bool isDigit(char currentChar)
{
    return (currentChar >= '0' && currentChar <= '9');
}

bool isLeadingSpace(char currentChar)
{
    return currentChar == ' ' && (flag == 0); // all flag bits should be 0
}

ParseResult handleNumSign(char currentChar, double &sign, double num)
{
    ParseResult result = ParseResult::FALSE;
    if ((currentChar == '+' || currentChar == '-'))
    {
        if (flag == 0 && num == 0.0)
        {
            sign = currentChar == '+' ? 1.0 : -1.0;
            flag |= FlagBits::SIGN; // sets the number sign bit
            result = ParseResult::TRUE;
        }
        else if ((flag & FlagBits::SIGN) != 0 && num == 0.0)
        {
            result = ParseResult::INVALID;
        }
    }

    return result;
}

ParseResult handleExponentSign(char currentChar, int &exponentSign)
{
    ParseResult result = ParseResult::FALSE;

    // checks exponent flag bit should be set and exponentSign bit should not be set
    if ((currentChar == '+' || currentChar == '-'))
    {
        if ((flag & FlagBits::EXPONENT) && (flag & FlagBits::EXP_SIGN) == 0)
        {
            exponentSign = currentChar == '+' ? 1 : -1;
            flag |= FlagBits::EXP_SIGN; // sets the exponent sign flag-bit
            result = ParseResult::TRUE;
        }
        else
        {
            result = ParseResult::INVALID;
        }
    }
    return result;
}

double custom_atof(const std::string str)
{
    double num = 0.0;
    double afterDecimal = 0.0;
    int decimalPlaces = 0;
    int expSign = 1;
    int expNums = 0;
    double sign = 1.0;

    for (char currentChar : str)
    {
        if (isLeadingSpace(currentChar))
        {
            continue;
        }

        ParseResult signResult = handleNumSign(currentChar, sign, num);
        if (signResult == ParseResult::TRUE)
        {
            continue;
        }
        else if (signResult == ParseResult::INVALID)
        {
            break;
        }

        if (currentChar == '.' && ((flag & FlagBits::DOT) == 0))
        {
            flag |= 2;
            continue;
        }
        else if ((currentChar == 'e' || currentChar == 'E') && ((flag & FlagBits::EXPONENT) == 0))
        {
            flag |= FlagBits::EXPONENT; // sets exponent bit
            flag |= FlagBits::SIGN; // sets num bit (in case sign was not entered by user)
            continue;
        }

        ParseResult expSignResult = handleExponentSign(currentChar, expSign);
        if (expSignResult == ParseResult::TRUE)
        {
            continue;
        }
        else if (expSignResult == ParseResult::INVALID)
        {
            break;
        }

        if ((flag & FlagBits::EXPONENT) == FlagBits::EXPONENT && isDigit(currentChar))
        {
            expNums = (expNums * 10) + (currentChar - '0');
            continue;
        }
        else if (isDigit(currentChar) && ((flag & FlagBits::DOT) == 0))
        {
            num = (num * 10) + (currentChar - '0');
            continue;
        }
        else if (isDigit(currentChar) && ((flag & FlagBits::DOT) != 0))
        {
            decimalPlaces++;
            afterDecimal = (afterDecimal * 10) + (currentChar - '0');
        }
        else
        {
            break;
        }
    }

    double result = num + (afterDecimal / pow(10, decimalPlaces));
    double multiplier = pow(10, expNums);
    result = expSign == 1 ? result * multiplier : result / multiplier;

    return result * sign;
}

int main()
{
    std::string input;
    std::cout << "Input: ";
    std::cin >> input;

    std::cout << std::setprecision(16) << custom_atof(input) << std::endl;

    return 0;
}