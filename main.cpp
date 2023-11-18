#include <iostream>
#include "Hasher.h"

int main() {
    std::string filename = "/home/artur/dev/checksums/textfile";

    HasherSHA256 hasher1(filename);
    std::cout << "Binary hash: ";
    hasher1.showBinaryHash();
    std::cout << "Hex hash: ";
    hasher1.showHash();

    HasherMD5 hasher2(filename);
    std::cout << "Binary hash: ";
    hasher2.showBinaryHash();
    std::cout << "Hex hash: ";
    hasher2.showHash();
    return 0;
}
