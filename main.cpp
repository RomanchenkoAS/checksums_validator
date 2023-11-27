#include <iostream>
#include <unistd.h> // for getcwd()
#include <limits.h> // for PATH_MAX
#include "Hasher.h"

std::string getFilename() {
//    Display current directory and receive filename from user
    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) != nullptr) {
        std::cout << "Current directory: " << path << std::endl;
    } else {
        std::cout << "getcwd() error" << std::endl;
        return "";
    }

    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;
    return filename;
}

void displayHashOptions(AbstractHasher &hasher) {
    int choice;
    do {
        std::cout << "\nMenu (current method " << hasher.getMethod() << "):\n";
        std::cout << "1. Display Hash\n";
        std::cout << "2. Display Binary Hash\n";
        std::cout << "3. Validate Hash\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                hasher.showHash();
                break;
            }
            case 2: {
                hasher.showBinaryHash();
                break;
            }
            case 3: {
                std::string userHash;
                std::cout << "Enter hash to validate: ";
                std::cin >> userHash;
                if (hasher.validate(userHash)) {
                    std::cout << "Hash is valid.\n";
                } else {
                    std::cout << "Hash is invalid.\n";
                }
                break;
            }
            case 0: {
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 0);
}

int main() {
    int choice;
    for (;;) {
        std::cout << "\n-- Main menu --\n";
        std::cout << "Select an option:\n";
        std::cout << "1. SHA1\n";
        std::cout << "2. SHA256\n";
        std::cout << "3. SHA3_256\n";
        std::cout << "4. SHA3_512\n";
        std::cout << "5. MD5\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice) {
            std::string filename = getFilename();

            try {
                switch (choice) {
                    case 1: {
                        HasherSHA1 hasher(filename);
                        displayHashOptions(hasher);
                        break;
                    }
                    case 2: {
                        HasherSHA256 hasher(filename);
                        displayHashOptions(hasher);
                        break;
                    }
                    case 3: {
                        HasherSHA3_256 hasher(filename);
                        displayHashOptions(hasher);
                        break;
                    }
                    case 4: {
                        HasherSHA3_512 hasher(filename);
                        displayHashOptions(hasher);
                        break;
                    }
                    case 5: {
                        HasherMD5 hasher(filename);
                        displayHashOptions(hasher);
                        break;
                    }
                    default: {
                        std::cout << "Invalid choice. Please try again.\n";

                    }
                }
            } catch (const std::runtime_error &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else {
            return 0;
        }
    }
}