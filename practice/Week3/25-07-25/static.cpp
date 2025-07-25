#include <stdio.h>
#include <stdlib.h>

//data segment
int initializedGlobalVar = 100;
char initializedGlobalString[] = "Hello World";

// bss segment
int uninitializedGlobalVar;
int uninitGlobalArray[1000];

int main();

void demonstrate_static() {

    static int count = 0;  
    static int uninitializedStaticVar;   
    
    // Local variables - stored on Stack
    int localVar = 42;
    char localArray[100];
    
    count++;
    uninitializedStaticVar += localVar;
    
    printf("Call #%d:\n", count);
    printf("  Static call_count: %d (address: %p)\n", count, &count);
    printf("  Static accumulator: %d (address: %p)\n", uninitializedStaticVar, &uninitializedStaticVar);
    printf("  Local local_var: %d (address: %p)\n", localVar, &localVar);
    printf("  Local array address: %p\n", localArray);
    printf("\n");
}

void showMemoryAdresses() {
    int *heap_var = new int(999);
    
    
    printf("TEXT SEGMENT (Code):\n");
    printf("  Function address: %p\n", demonstrate_static);
    printf("  Main function: %p\n", main);
    printf("\n");
    
    printf("DATA SEGMENT :\n");
    printf("  initializedGlobalVar: %d at %p\n", initializedGlobalVar, &initializedGlobalVar);
    printf("  initializedGlobalString: '%s' at %p\n", initializedGlobalString, initializedGlobalString);
    printf("\n");
    
    printf("BSS SEGMENT:\n");
    printf("  uninitializedGlobalVar: %d at %p\n", uninitializedGlobalVar, &uninitializedGlobalVar);
    printf("  uninitGlobalArray: starts at %p\n", uninitGlobalArray);
    printf("\n");
    
    printf("HEAP:\n");
    printf("  heapVar: %d at %p\n", *heap_var, heap_var);
    printf("\n");
    
    printf("STACK:\n");
    int stack_var = 123;
    printf("  stackVar: %d at %p\n", stack_var, &stack_var);
    printf("  heapVar pointer itself: %p\n", &heap_var);
    printf("\n");
    
    free(heap_var);
}

int main() {

    demonstrate_static();
    demonstrate_static();
    demonstrate_static();
    
    printf("\n");
    showMemoryAdresses(); // i can see that, all local variable are starts from 7.. meaning at higher adress
    
    return 0;
}