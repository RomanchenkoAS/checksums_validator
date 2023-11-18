#ifndef CHECKSUMS_HASHER_H
#define CHECKSUMS_HASHER_H

#include <string>
#include <iostream>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <iomanip> // for input/output manipulation (toHex)
#include <fstream>
#include <utility> // for std::move()

class AbstractHasher {
protected:
    std::string binary_hash;
    std::string hash;
    std::string filename;
    std::ifstream file;

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

    virtual std::string calculateHash() = 0;

public:
    AbstractHasher() = delete;

    explicit AbstractHasher(std::string filename) : filename(std::move(filename)),
                                                    file(this->filename, std::ios::binary) {
        if (!file) {
            throw std::runtime_error("Cannot open file");
        }
    };

//    Forbid copy
    AbstractHasher(const AbstractHasher &) = delete;

    AbstractHasher &operator=(const AbstractHasher &) = delete;

//    Forbid move
    AbstractHasher(AbstractHasher &&) = delete;

    AbstractHasher &operator=(AbstractHasher &&) = delete;


    virtual ~AbstractHasher() = default;

    std::string getHash() {
        if (hash.empty()) {
            calculateHash();
        }
        return hash;
    }

    std::string get_binary_hash() {
        return binary_hash;
    }

};

class HasherMD5 : public AbstractHasher {
private:
    std::string calculateHash() override {
        std::cout << "Hash is calculated" << std::endl;
    };
public:
    HasherMD5() = delete;

    using AbstractHasher::AbstractHasher;


};

#endif //CHECKSUMS_HASHER_H
