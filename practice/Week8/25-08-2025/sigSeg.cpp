#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

void signalHandler2(int sig, siginfo_t *info, void *ucontext){
        std::cerr << "Caught SIGSEGV ==== at address: " << info->si_addr << std::endl;
        

}

void signalHandler(int sig, siginfo_t *info, void *ucontext) {
  

    std::cerr << "Caught SIGSEGV at address: " << info->si_addr << std::endl;
        _exit(EXIT_FAILURE);

}

void fun(){
    struct sigaction sa{};
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signalHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, nullptr);

}

int main() {


    std::cout << "About to cause a segmentation fault..." << std::endl;


    int *ptr = nullptr;
    *ptr = 42;
    fun();
    std::cout << "This will never be printed." << std::endl;
    return 0;
}
