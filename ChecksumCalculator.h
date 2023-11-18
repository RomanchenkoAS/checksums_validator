#ifndef CHECKSUMS_CHECKSUMCALCULATOR_H
#define CHECKSUMS_CHECKSUMCALCULATOR_H

#include <string>
#include <iostream>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <iomanip>

class AbstractHasher {
protected:
    std::string binary_hash;
    std::string hash;

    void toHex() {
        // Transform binary hash string into hexadecimal
        std::stringstream ss;
        for (char byte: binary_hash) {
            /*
             * static_cast<int>(byte) - transform a byte into an integer 0..255
             * std::setw(2) - set length of a hex digit to 2 slots
             * std::setfill('0') - fill slots with 0 if empty up to 2 slots
             * std::hex - interpret input as a hexadecimal string
             */
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }
        hash = ss.str();
    }

public:
    virtual std::string getHash() = 0;
    virtual ~AbstractHasher() = default;

};

class HasherMD5 : public AbstractHasher {
public:
    std::string getHash() override {
        std::cout << "Hash is calculated" << std::endl;
    };

};

#endif //CHECKSUMS_CHECKSUMCALCULATOR_H
