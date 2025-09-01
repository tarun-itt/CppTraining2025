#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

bool done = false;
std::string lines[3][3] = {
    {"The sun rises in the east.", "Birds sing in the morning sky.", "A gentle breeze moves through the trees."},
    {"Rivers flow toward the ocean.", "Fish swim beneath the surface.", "Nature follows its quiet rhythm."},
    {"Stars appear when night falls.", "The moon casts a silver glow.", "The world slows down and dreams begin."}
};

void writer() {
    for (int i = 0; i < 3; i++) {
        std::ofstream f("file.txt");
        if (f.is_open()) {
            f << "Entry " << i+1 << "\n";
            for (int j = 0; j < 3; j++) {
                f << lines[i][j] << "\n";
            }
            f.close();
            std::cout << "Wrote entry " << i+1 << "\n";
        } else {
            std::cout << "cannot open file!\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
    done = true;
}

void reader() {
    while (!done) {
        std::ifstream f("file.txt");
        if (f.is_open()) {
            std::cout << "\nReading file:\n";
            std::string s;
            while (std::getline(f, s)) {
                std::cout << s << "\n";
            }
            f.close();
        } else {
            std::cout << "File not ready\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::ifstream f("file.txt");
    std::cout << "\nFinal file:\n";
    std::string s;
    while (std::getline(f, s)) {
        std::cout << s << "\n";
    }
    f.close();
}

int main() {
    std::thread t1(writer);
    std::thread t2(reader);

    t1.join();
    t2.join();

    std::cout << "Done!\n";
    return 0;
}
