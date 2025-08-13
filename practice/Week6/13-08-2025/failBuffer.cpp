#include <fstream>
#include <iostream>
#include <string>

int main(){

    std::ofstream ofs;
    char* myBuffer = new char[1024];
    ofs.rdbuf()->pubsetbuf(myBuffer, 10);

    //this will not flush data to the file, for data to be written to the file, it has to be written through stream, and not directly buffer. Streams maintian internal pointers to the buffer, so what is happening i think is, that since we didnt use any stream methods to write, the pointers are in initial state, so maybe both start and enpointers are at -1, and therefore dont write anything to the file, eventhough the buffer has data in it
  
    // for(int i=0;i<9;i++){
    //     myBuffer[i] = (char)('a'+i);
    // }
    // std::cout<<myBuffer; //it prints the data inside the char array, but the stream still has no idea about this data

    //still wont work because the file is not yet open
    for(int i=0;i<19;i++){
        ofs.put((char)('a'+i));
    }

    ofs.open("overflow.txt");

    //now works because file is open and we use stram function
    for(int i=0;i<9;i++){
        ofs.put((char)('a'+i));
    }



    myBuffer[0]='T'; // this works because previously, we have set the internal pointers at different locations in the loop, 
    
    ofs.flush();
    ofs.close();
}