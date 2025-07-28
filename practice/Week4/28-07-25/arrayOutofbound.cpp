#include <iostream>
int main(){
    int arr[10];
   // arr[11]  = 234; //stack smashing detected

    for(int i=0;i<12;i++)
    {
        arr[i] = (i*3)+4;
    }
std::cout<<arr[10]<<" "<<arr[11]<<std::endl;
    return 0;
}