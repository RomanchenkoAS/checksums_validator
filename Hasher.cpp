#include <algorithm> // for std::transform()
#include <fstream>
#include <iostream>
#include <iomanip> // for input/output manipulation (toHex)
#include <cmath>   // for pow
#include <chrono> // for using a high-res clock
#include <bitset> // for debugging
#include "Hasher.h"

AbstractHasher::AbstractHasher(std::string newFilename) {
    filename = std::move(newFilename);
    file.open(this->filename, std::ios::binary);
    fileSize = getFileSize();
    hashingSpeed = -1;
    if (!file) throw std::runtime_error("Cannot open file");
};

void AbstractHasher::toHex() {
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
    for (char byte: binaryHash) {
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

float AbstractHasher::getFileSize() {
    std::ifstream tempFile(filename, std::ios::binary | std::ios::ate);
    if (!tempFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::streampos fileSizeInBytes = tempFile.tellg();
    return fileSizeInBytes / std::pow(1024, 2); // in MB
}

void AbstractHasher::calculateHash() {
    EVP_MD_CTX *digest_context = EVP_MD_CTX_new();
    if (digest_context == nullptr) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }
//    Initialize digest operation
    initializeDigest(digest_context);

//    Process chunks of data and update hash_array
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
//        Free memory
        EVP_MD_CTX_free(digest_context);
        throw std::runtime_error("Failed to finalize digest.");
    }

    EVP_MD_CTX_free(digest_context);

//    Turn to string and generate hexadecimal hash_array
    binaryHash = std::string(reinterpret_cast<const char *>(hash_array), lengthOfHash);
    toHex();
};

void AbstractHasher::calculateSpeed(float duration) {
    if (duration == 0) {
        hashingSpeed = 0;
    } else {
        hashingSpeed = 1000 * fileSize / duration;
    }
}

void AbstractHasher::displaySpeed() const {
    if (hashingSpeed == -1) {
        throw std::runtime_error("Speed is not yet calculated.");
    } else {
        if (hashingSpeed != 0) {
            std::cout << "Hashing speed = " << hashingSpeed << " MB/s." << std::endl;
        } else {
            std::cout << "File is too small to calculate speed." << std::endl;
        }
    }
}

void AbstractHasher::checkHash() {
//    If hash is not yet calculated - do it
    if (binaryHash.empty()) {
        getFileSize();
        auto startTimeMS = std::chrono::high_resolution_clock::now();

        calculateHash();

        auto endTimeMS = std::chrono::high_resolution_clock::now();
        auto executionTimeMS = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeMS - startTimeMS).count();
        calculateSpeed((float) executionTimeMS);
    }
}

std::string AbstractHasher::getHash() {
    checkHash();
    return hash;
}

std::string AbstractHasher::getBinaryHash() {
    checkHash();
    return binaryHash;
}

void AbstractHasher::showBinaryHash() {
    checkHash();
    std::cout << std::endl << getMethod() << " binary hash = ";
    for (unsigned char c: binaryHash) {
        std::bitset<8> bits(c);
        std::cout << bits << ' ';
    }
    std::cout << std::endl;
}

void AbstractHasher::showHash() {
    std::cout << std::endl << getMethod() << " hash = " << getHash() << std::endl;
}

bool AbstractHasher::validate(const std::string &input) {
    checkHash();
//    Uppercase input string
    std::string compare_string = input;
    std::transform(compare_string.begin(), compare_string.end(), compare_string.begin(), ::toupper);
    return (hash == compare_string);
}

void HasherSHA1::initializeDigest(EVP_MD_CTX *digest_context) {
    if (EVP_DigestInit_ex(digest_context, EVP_sha1(), nullptr) != 1) {
        EVP_MD_CTX_free(digest_context);
        throw std::runtime_error("Failed to initialize digest context");
    }
}


void HasherSHA256::initializeDigest(EVP_MD_CTX *digest_context) {
    if (EVP_DigestInit_ex(digest_context, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(digest_context);
        throw std::runtime_error("Failed to initialize digest context");
    }
}

void HasherSHA3_256::initializeDigest(EVP_MD_CTX *digest_context) {
    if (EVP_DigestInit_ex(digest_context, EVP_sha3_256(), nullptr) != 1) {
        EVP_MD_CTX_free(digest_context);
        throw std::runtime_error("Failed to initialize digest context");
    }
}

void HasherSHA3_512::initializeDigest(EVP_MD_CTX *digest_context) {
    if (EVP_DigestInit_ex(digest_context, EVP_sha3_512(), nullptr) != 1) {
        EVP_MD_CTX_free(digest_context);
        throw std::runtime_error("Failed to initialize digest context");
    }
}

void HasherMD5::initializeDigest(EVP_MD_CTX *digest_context) {
    if (EVP_DigestInit_ex(digest_context, EVP_md5(), nullptr) != 1) {
        EVP_MD_CTX_free(digest_context);
        throw std::runtime_error("Failed to initialize digest context");
    }
}
