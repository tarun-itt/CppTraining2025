#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    int fd = open("/tmp/my_shared_mem", O_RDWR, 0666);
    int* shared_counter = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    std::cout << "Read from shared memory: " << *shared_counter << std::endl;

    munmap(shared_counter, sizeof(int));
    close(fd);
    return 0;
}
