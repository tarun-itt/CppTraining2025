#include <iostream>

extern "C"{
void recursive(){
    static int count = 0;
    int a = 9;
    
    count++;
    recursive();
}



int main(){
    recursive();
    
    return 0;
}
}