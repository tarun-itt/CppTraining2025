#include <iostream>
#include <fstream>

int main() {
    const char* filename = "writeFile.txt";

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return 1;
    }
    outFile << "Hello world.\n";
    outFile.close();

    std::ofstream appendFile("trialText.txt", std::ios::app);
    if (!appendFile) {
        std::cerr << "Error opening file for appending.\n";
        return 1;
    }
    appendFile << "Though file was for reading, but i still appended xd.\n";
    appendFile.close();

    std::cout<<"Open the writeFile txt before pressing enter\n";
    getchar();

    std::ofstream overwriteFile(filename, std::ios::trunc);
    if (!overwriteFile) {
        std::cerr << "Error opening file for overwriting.\n";
        return 1;
    }
    overwriteFile << "I overwrote the entire file.\n";
    overwriteFile.close();
    
    return 0;
}
