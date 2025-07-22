#include <iostream>

void passByRef(int& num){
    num = 50;
}
int x = 843;
void passByAddress(int* num){
    *num = 23;
    //num is a local param pointer, which receives a copy of address passed to it
    //so it can affectively make changes at that address, but it cant change where the original pointer, points to
    //over here the local copy now points to x, the original pointer of main() still points to original num
    //which now stores 23(and not 843)
    num = &x;  
}

void passByAddressRef(int*& num){
    *num = 111;
}
void passByAddressRef2(int*& num){
    num = &x;
}
int y = 2301293;
void passByPointerAddress(int** num){
*num = &y;
}


int main(){
    int num{60};

    std::cout<<"Num before passByRef: "<<num<<"\n";
    passByRef(num);
    std::cout<<"Num after passByRef: "<<num<<"\n\n";

    std::cout<<"Num before passByAdd: "<<num<<"\n";
    passByAddress(&num);
    std::cout<<"Num after passByAdd: "<<num<<"\n\n";

    int* ptrToNum = &num;
    std::cout<<"Num before passByAddRef: "<<*ptrToNum<<"\n";
    passByAddressRef(ptrToNum);
    std::cout<<"Num after passByAddRef: "<<*ptrToNum<<"\n";
    std::cout<<"Num before passByAddRef2: "<<*ptrToNum<<"\n";
    passByAddressRef2(ptrToNum);
    std::cout<<"Num after passByAddRef2: "<<*ptrToNum<<"\n\n";

    std::cout<<"Num before passBypointerAdd: "<<*ptrToNum<<"\n";
    passByPointerAddress(&ptrToNum);
    std::cout<<"Num after passBypointerAdd: "<<*ptrToNum<<"\n\n";
}