#ifndef CHECKSUMS_CHECKSUMCALCULATOR_H
#define CHECKSUMS_CHECKSUMCALCULATOR_H

#include <string>
#include <iostream>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <iomanip>

class AbstractHasher {
protected:
    std::string hash;

public:
    virtual std::string getHash() = 0;

    virtual ~AbstractHasher() = default;

};

class MD5 : public AbstractHasher {
public:
    std::string getHash() override {
        std::cout << "Hash is calculated" << std::endl;
    };

};

#endif //CHECKSUMS_CHECKSUMCALCULATOR_H
