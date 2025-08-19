#include "mathUtils.h"

double add(double firstNum, double secondNum){
    return firstNum + secondNum;
}

double sub(double firstNum, double secondNum){
    return firstNum - secondNum;
}

double mult(double firstNum, double secondNum){
    return firstNum * secondNum;
}

double div(double firstNum, double secondNum){
    return firstNum/secondNum;
}

bool isPrime(int n){
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for(int i=3;i*i <= n;i++){
        if(n%i==0)return false;
    }
    return true;
}