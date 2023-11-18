#include <iostream>
#include "Hasher.h"

int main() {

    HasherSHA256 hasher("/home/artur/dev/checksums/textfile");
    std::cout << "Binary hash: ";
    hasher.showBinaryHash();
    std::cout << hasher.getHash() << std::endl;
    return 0;
}
