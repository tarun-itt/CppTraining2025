#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>



bool isDigit(char ch){
    return (ch >= 48 && ch <= 57); // checks the ascii range of numerical digits
}

bool isSpace(char ch){
    return ch==' ';
}

//bool flags[] = {0, 0, 0, 0}; //sign, dot, exponent, sign2
int flag = 0; //0 0 0 0 => expSing, exponent, dot, sign

double custom_atof(const std::string str){
    double num = 0.0;
    double afterDecimal = 0.0;
    int decimalPlaces = 0;
    int expSign = 1;
    int expNums = 0;

    double sign = 1.0;
    for(char ch: str){
        if(isSpace(ch) && ((flag&15)==0))continue;
        else if(isspace(ch) && ((flag&15)!=0)){break;}

        if(ch=='+' && ((flag&1)  == 0) && num==0.0){
           sign = 1.0; 
           flag = (flag | 1);
           continue;
        }else if(ch=='-' && ((flag&1)==0) && num==0.0){
            sign = -1.0;
            flag = (flag | 1);
            continue;
        }

        if(ch=='.' && ((flag&2)==0)){
            flag = (flag|2);
            continue;
        }else if(ch=='.' && ((flag&2)==1)){
            break;
        }

        if(isDigit(ch) && ((flag&2)==0)){
            num = (num*10) + (ch - '0');
            continue;
        }else if(isDigit(ch) && ((flag&2)==2)){
            decimalPlaces++;
            afterDecimal = (afterDecimal*10)+(ch-'0');
        }

        if((ch=='e'||ch=='E') && ((flag&4)==4)){
            break;
        }else  if((ch=='e'||ch=='E') && ((flag&4)!=4)){
            flag = flag | 4;
            continue;
        }

        if(ch=='+' && ((flag&8)==8)){
            break;
        }else if(ch=='+' && ((flag&8)!=0)){
            flag = flag | 8;
            expSign = 1;
            continue;
        }

        if(ch=='-' && ((flag&8)==8)){
            break;
        }else if(ch=='-' && ((flag&8)==8)){
            flag = flag | 8;
            expSign = -1;
            continue;
        }

        if((flag&4)==4 && isDigit(ch)){
            expNums = (expNums*10) + (ch-'0');
            continue;
        }
    }

    double result = (num+(afterDecimal/pow(10,decimalPlaces)));
    

    double mult = pow(10,expNums);

    result = expSign == 1 ? result*mult:result/mult;
    
    return result*sign;
}

int main(){

  // custom_atof("     1000.312");
  std::cout<< std::setprecision(9)<<custom_atof("    -1000.312e3")<<"\n";

    return 0;
}