#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring>

int* shared_counter = nullptr;

void recursive() {
    (*shared_counter)++;
    int a = 10;
    recursive();
}

int main() {
    int fd = open("/tmp/my_shared_mem", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        std::cerr << "Failed to open shared memory file\n";
        return 1;
    }

    if (ftruncate(fd, sizeof(int)) == -1) {
        std::cerr << "Failed to truncate shared memory file\n";
        close(fd);
        return 1;
    }

    shared_counter = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_counter == MAP_FAILED) {
        std::cerr << "Failed to mmap shared memory\n";
        close(fd);
        return 1;
    }

    *shared_counter = 0;

    std::cout << "Starting recursion...\n";

    recursive();

    munmap(shared_counter, sizeof(int));
    close(fd);
    return 0;
}
