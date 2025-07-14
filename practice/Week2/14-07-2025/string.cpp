#include <iostream>
#include <cstring>

int main() {
    char sentence[100] = ""; 
    const char* words[] = { "Hello", "world", "!" };

    for (int i = 0; i < 3; ++i) {
        strcat(sentence, words[i]);
        strcat(sentence, " ");
    }

    std::cout << sentence << "\n";
    return 0;
}
