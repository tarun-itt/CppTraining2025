#include <iostream>
#include <fstream>
#include <ios>

int main() {
    std::ofstream ofs;
    auto* buf = ofs.rdbuf(); // Get the underlying stream buffer

    std::cout << "Buffer address: " << static_cast<void*>(buf) << "\n\n";
    buf->sputn("Hello buffer!\n", 14); //writing directly to buffer

    char* myBuffer = new char[1024];
    myBuffer[0] = 'T';
    ofs.rdbuf()->pubsetbuf(myBuffer, 1024); //need to set the custom buffer before opening the file, after opening the file, internal buffer is assigned and we cant use our custom buffer


    ofs.open("test.txt", std::ios::app);

   // ofs.rdbuf()->pubsetbuf(myBuffer, 1024); //giving a custom buffer, it did not work here, because the file had been opened already, should be added before opening file
    
    ofs << "lopds\n";
    buf->sputn("\nNIuffer!\n", 7);

    std::cout<<myBuffer;

    ofs.flush(); //flushing, aka forcing to write to file from the buffer, putting it before delete, so now, the file will not have random characters


    //delete[] myBuffer; //if i delete the buffer, it seems like ofstream is not able to access the data which was there, so it writes some random characters in the file
    std::cout<<myBuffer; 

    ofs<<"\nnew data\n"; //so basically buffer's internal pointers are reset and not actually buffer is cleared, this is the reason this line will be printed, and there will be leftover data from previous write to the buffer `ffe` part
    std::cout<<myBuffer;
    
    ofs.close();
    return 0;
}
