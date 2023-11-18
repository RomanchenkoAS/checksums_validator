#include <iostream>
#include "Hasher.h"

int main() {

    HasherSHA256 hasher("/home/artur/dev/checksums/textfile");
    std::cout << "Binary hash: ";
    hasher.showBinaryHash();
    std::cout << "Hex hash: ";
    hasher.showHash();
    return 0;
}
