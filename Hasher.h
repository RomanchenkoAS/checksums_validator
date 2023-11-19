#ifndef CHECKSUMS_HASHER_H
#define CHECKSUMS_HASHER_H

#include <string>
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <utility> // for std::move()


class AbstractHasher {
protected:
    std::string binary_hash;
    std::string hash;
    std::string filename;
    std::ifstream file;

    void toHex();

    virtual void initializeDigest(EVP_MD_CTX *digest_context) = 0;

    void calculateHash();

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

    void checkHash();

    std::string getHash();

    std::string getBinaryHash();

    void showBinaryHash();

    void showHash();

    bool validate(const std::string &input);

    virtual std::string getMethod() = 0;

};

class HasherSHA1 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override;

public:
    using AbstractHasher::AbstractHasher;

    std::string getMethod() override { return "SHA1"; }
};

class HasherSHA256 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override;

public:
    using AbstractHasher::AbstractHasher;
    std::string getMethod() override { return "SHA256"; }

};

class HasherSHA3_256 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override;

public:
    using AbstractHasher::AbstractHasher;
    std::string getMethod() override { return "SHA3_256"; }

};

class HasherSHA3_512 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override;

public:
    using AbstractHasher::AbstractHasher;
    std::string getMethod() override { return "SHA3_512"; }

};

class HasherMD5 : public AbstractHasher {
private:
    void initializeDigest(EVP_MD_CTX *digest_context) override;

public:
    using AbstractHasher::AbstractHasher;
    std::string getMethod() override { return "MD5"; }

};



#endif //CHECKSUMS_HASHER_H
