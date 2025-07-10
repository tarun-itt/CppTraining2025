#include <iostream>

int main(){

    int n;
    std::cin>>n;

    int arr[n];

    int* parr = new int[n];
    int* ptrb = parr;
    for(int i=23;i<23+n;i++,ptrb++){
        *ptrb = i;
    }

    std::cout<<(*parr)<<"\n";
    std::cout<<*(ptrb-n)<<"\n";
    return 0;
}