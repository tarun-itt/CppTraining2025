int uninitializedArray[10000];

int zeroInitializedArray[10000] = {0};

int main() {
    return uninitializedArray[0] + zeroInitializedArray[0];
}
