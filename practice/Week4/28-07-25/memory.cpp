#include<iostream>

// int arrayFirst[5];
// int arrayZeroInit[6] = {0};
// int arrayFirstInit[7]{12, 34};

void fun(int a){
    std::cout<<a<<std::endl;
}

void fun(int* a){
    std::cout<<*a<<std::endl;
}

int main(){
    //static int arrayStatic[4];
    // int localArray[4];

    int x = 10;
    // std::cout<<typeid(nullptr).name()<<std::endl;

    int* ptr = nullptr;
    int* ptr2 = 0;
    int* ptr3 = NULL;
    int* ptrNum = &x;

    fun(nullptr);
    return 0;
}