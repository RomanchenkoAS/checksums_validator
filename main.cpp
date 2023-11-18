#include <iostream>
#include "Hasher.h"

int main() {
    HasherSHA256 hasher("/home/artur/dev/checksums/textfile");
    std::cout << "Hello, checksums!" << std::endl;
    std::cout << hasher.getHash() << std::endl;
    return 0;
}
