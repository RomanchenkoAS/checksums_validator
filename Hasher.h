#ifndef CHECKSUMS_HASHER_H
#define CHECKSUMS_HASHER_H

#include <string>
#include <iostream>
#include <openssl/evp.h>

#include <iomanip> // for input/output manipulation (toHex)
#include <fstream>
#include <utility> // for std::move()
#include <algorithm> // for std::transform()

#include <bitset> // for debugging

class AbstractHasher {
protected:
    std::string binary_hash;
    std::string hash;
    std::string filename;
    std::ifstream file;

    void toHex() {
        // Transform binary hash string into hexadecimal
#ifdef DEBUG
        std::cout << "Binary string:" << std::endl;
        for (unsigned char c: binary_hash) {
            std::bitset<8> bits(c);
            std::cout << bits << ' ';
        }
        std::cout << std::endl;
#endif
        std::stringstream ss;
        for (char byte: binary_hash) {
            /*
             * (int)(unsigned char)(byte) - transform a signed char to unsigned and then into an integer 0..255
             * std::setw(2) - set length of a hex digit to 2 slots
             * std::setfill('0') - fill slots with 0 if empty up to 2 slots
             * std::hex - interpret input as a hexadecimal string
             */
            ss << std::hex << std::setw(2) << std::setfill('0') << (int) (unsigned char) (byte);
        }
        hash = ss.str();
        std::transform(hash.begin(), hash.end(), hash.begin(), ::toupper);
    }

    virtual void initializeDigest(EVP_MD_CTX *digest_context) = 0;

    void calculateHash() {
        EVP_MD_CTX *digest_context = EVP_MD_CTX_new();
        if (digest_context == nullptr) {
            throw std::runtime_error("Failed to create EVP_MD_CTX");
        }
//        Initialize digest operation
        initializeDigest(digest_context);

//        Process chunks of data and update hash_array
        char buffer[4096];
        while (file.read(buffer, sizeof(buffer)) || file.gcount()) {
            if (EVP_DigestUpdate(digest_context, buffer, file.gcount()) != 1) {
                EVP_MD_CTX_free(digest_context);
                throw std::runtime_error("Failed to update digest");
            }
        }

//        Finish processing hash_array
        unsigned char hash_array[EVP_MAX_MD_SIZE];
        unsigned int lengthOfHash = 0;
        if (EVP_DigestFinal_ex(digest_context, hash_array, &lengthOfHash) != 1) {
//            Free memory
            EVP_MD_CTX_free(digest_context);
            throw std::runtime_error("Failed to finalize digest");
        }

        EVP_MD_CTX_free(digest_context);

//        Turn to string and generate hexadecimal hash_array
        binary_hash = std::string(reinterpret_cast<const char *>(hash_array), lengthOfHash);
        toHex();
    };

public:
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

    void checkHash() {
//        Make sure hash is already generated
        if (binary_hash.empty()) {
            calculateHash();
        }
    }

    std::string getHash() {
        checkHash();
        return hash;
    }

    std::string getBinaryHash() {
        checkHash();
        return binary_hash;
    }

    void showBinaryHash() {
        checkHash();
        for (unsigned char c: binary_hash) {
            std::bitset<8> bits(c);
            std::cout << bits << ' ';
        }
        std::cout << std::endl;
    }

    void showHash() {
        std::cout << getHash() << std::endl;
    }

    bool validate(const std::string &input) {
        checkHash();
        return (hash == input);
    }

};

class HasherSHA1 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override {
        if (EVP_DigestInit_ex(digest_context, EVP_sha1(), nullptr) != 1) {
            EVP_MD_CTX_free(digest_context);
            throw std::runtime_error("Failed to initialize digest context");
        }
    }

public:
    using AbstractHasher::AbstractHasher;
};

class HasherSHA256 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override {
        if (EVP_DigestInit_ex(digest_context, EVP_sha256(), nullptr) != 1) {
            EVP_MD_CTX_free(digest_context);
            throw std::runtime_error("Failed to initialize digest context");
        }
    }

public:
    using AbstractHasher::AbstractHasher;
};

class HasherSHA3_256 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override {
        if (EVP_DigestInit_ex(digest_context, EVP_sha3_256(), nullptr) != 1) {
            EVP_MD_CTX_free(digest_context);
            throw std::runtime_error("Failed to initialize digest context");
        }
    }

public:
    using AbstractHasher::AbstractHasher;
};

class HasherSHA3_512 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override {
        if (EVP_DigestInit_ex(digest_context, EVP_sha3_512(), nullptr) != 1) {
            EVP_MD_CTX_free(digest_context);
            throw std::runtime_error("Failed to initialize digest context");
        }
    }

public:
    using AbstractHasher::AbstractHasher;
};

class HasherMD5 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override {
        if (EVP_DigestInit_ex(digest_context, EVP_md5(), nullptr) != 1) {
            EVP_MD_CTX_free(digest_context);
            throw std::runtime_error("Failed to initialize digest context");
        }
    }

public:
    using AbstractHasher::AbstractHasher;
};


class HasherMD4 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override {
        if (EVP_DigestInit_ex(digest_context, EVP_md4(), nullptr) != 1) {
            EVP_MD_CTX_free(digest_context);
            throw std::runtime_error("Failed to initialize digest context");
        }
    }

public:
    using AbstractHasher::AbstractHasher;
};

#endif //CHECKSUMS_HASHER_H
