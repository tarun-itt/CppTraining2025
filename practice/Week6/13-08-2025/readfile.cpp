#include <iostream>
#include <fstream>

int main(){
    char* myBuffer = new char[10000];
    std::ifstream ifs;
    auto* buffer = ifs.rdbuf()->pubsetbuf(myBuffer,10000);
    ifs.open("overflow.txt");

    if(!ifs){
        std::cout<<"File does not exist!";
        return 1;
    }
    ifs.get(); //this funtion makes a system call asking os to load the file data in the buffer (generally 4kb of data), and moves the beginpointer by 1, and returns the first read character from the buffer, but the buffer more than 1character data

    std::cout<<myBuffer; //i am checking if buffer is loaded with data as soon as file is opened

    // std::string line;

    // while(getline(ifs,line)){
    //     std::cout<<line<<"\n";
    //     std::streampos pos = ifs.tellg();
    //     std::cout<<pos<<std::endl;
    //     ifs.seekg(3,std::ios::cur);
    // }
    return 0;
}