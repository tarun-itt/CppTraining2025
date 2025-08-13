#include <iostream>
#include <fstream>

int main() {
    std::fstream fout("test.txt", std::ios::app | std::ios::in);

    if (!fout) {
        std::cerr << "Cannot open file\n";
        return 1;
    }
    std::cout<<fout.tellp()<<"  "<<fout.tellg()<<std::endl;
    fout << "Hello";

    std::streampos pos = fout.tellp(); 
    std::cout << "Next write will be at position: " << pos << "\n";

    fout.seekp(2); 
    std::cout << "After seekp(2), tellp = " << fout.tellp() << "\n";

    fout.close();
}
