#ifndef CHECKSUMS_HASHER_H
#define CHECKSUMS_HASHER_H

#include <string>
#include <iostream>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#include <iomanip> // for input/output manipulation (toHex)
#include <fstream>
#include <utility> // for std::move()

#include <bitset> // for debugging

class AbstractHasher {
protected:
    std::string binary_hash;
    std::string hash;
    std::string filename;
    std::ifstream file;

    void toHex() {
        std::cout << "Binary string:" << std::endl;
        for (unsigned char c: binary_hash) {
            std::bitset<8> bits(c);
            std::cout << bits << ' ';
        }
        std::cout << std::endl;
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

    virtual void calculateHash() = 0;

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
        if (binary_hash.empty()) {
            calculateHash();
        }
        return binary_hash;
    }

};

class HasherSHA256 : public AbstractHasher {
private:
    void calculateHash() override {
        EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
        if (mdctx == nullptr) {
            throw std::runtime_error("Failed to create EVP_MD_CTX");
        }

        if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
            EVP_MD_CTX_free(mdctx);
            throw std::runtime_error("Failed to initialize digest context");
        }

        char buffer[4096];
        while (file.read(buffer, sizeof(buffer)) || file.gcount()) {
            if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
                EVP_MD_CTX_free(mdctx);
                throw std::runtime_error("Failed to update digest");
            }
        }

        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int lengthOfHash = 0;
        if (EVP_DigestFinal_ex(mdctx, hash, &lengthOfHash) != 1) {
            EVP_MD_CTX_free(mdctx);
            throw std::runtime_error("Failed to finalize digest");
        }

        EVP_MD_CTX_free(mdctx);

        binary_hash = std::string(reinterpret_cast<const char *>(hash), lengthOfHash);
        toHex();
    };
public:
    HasherSHA256() = delete;

    using AbstractHasher::AbstractHasher;


};

#endif //CHECKSUMS_HASHER_H
