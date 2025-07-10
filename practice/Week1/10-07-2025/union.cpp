#include <iostream>
#include <string>
#include <cstring>


/*
    since we can represent colors in different formats, my code tries to mimic color in rgb,rgba
    hash and hsl formats.

    this defined colorCode, can be used in objects where we need to store color information in one variable
    but using different formats. 
*/
typedef union colorCode
{
    char hash[9];
    struct
    {
        int r;
        int g;
        int b;
    } rgb;
    struct
    {
        int r;
        int g;
        int b;
        int a;
    } rgba;
    struct
    {
        int h;
        int s;
        int l;
    } hsl;
}colorCode;

typedef struct Car
{
    int modelNo;
    colorCode color;
    union{
        int rgb[3];
        int rgba[4];
    };
}Car;

int main()
{
    Car car1, car2;
    car1.modelNo = 8433244;
    strcpy(car1.color.hash, "#F0B23");

    car2.modelNo = 38443002;
    car2.color.rgb.r = 123;
    car2.color.rgb.g = 59;
    car2.color.rgb.b = 204;

    std::cout << "Car1 Model: " << car1.modelNo << "\n";
    std::cout << "Car1 Color (hex): " << car1.color.hash << "\n";

    std::cout << "Car2 Model: " << car2.modelNo << "\n";
    std::cout << "Car2 Color (RGB): ("
              << car2.color.rgb.r << ", "
              << car2.color.rgb.g << ", "
              << car2.color.rgb.b << ")\n";

    return 0;
}