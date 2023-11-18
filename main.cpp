#include <iostream>
#include "Hasher.h"

int main() {
    HasherMD5 hasher("/home/artur/dev/checksums/textfile");
    hasher.getHash();
    std::cout << "Hello, checksums!" << std::endl;
    return 0;
}
