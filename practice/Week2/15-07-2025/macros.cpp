
#define MAC(x,y) argument1: x argument2: y
#include <iostream>
//#define PRINT(a,b) cout << (a) << (b)
#define PRINT(a,b,c) cout << (a) << (b) << (c)
#define FAC(n) (n > 1) ? n * FAC(n-1) : 1

#define SQUARE(a) ((a) * (a))
#define INCR_xx (xx)++


int globalVar = 903;

int main(){
    //the code
    int xx = 0;
int y = SQUARE(xx+2);

INCR_xx;

std::cout<<"\n\n Today's Date: "<<__DATE__<<" LOC: "<<__LINE__;

    return 0;
}