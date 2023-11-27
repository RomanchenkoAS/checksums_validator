# File Integrity Check

## Requirements
- First, make sure you have OpenSSL installed. On Ubuntu or other Debian-like systems, you can install it with:
```bash
sudo apt-get update
sudo apt-get install libssl-dev
```
- To compile the code you need **cmake**, if you don't have it installed, run:
```bash
sudo apt-get install cmake
```

## Running the code

- To compile code, create a build directory and run cmake:
```bash
mkdir build && cd build
cmake ..
```
- Then compile the code with:
```bash
make
```
- Run code with:
```bash
./checksums
```

## Task description
**Objective**: Create a tool that calculates and verifies checksums or cryptographic hashes to verify file integrity.

**Functional Requirements:**

- [x] The tool should support at least two hashing algorithms (e.g., SHA-256, MD5).
- [x] Users should be able to select a file and calculate its checksum.
- [x] The tool should allow users to compare the calculated checksum with a provided one for file integrity verification.
- [x] Provide a simple user interface through the command line.
- [x] Implement error handling for missing files or read permissions.

**Performance Criteria:**

- [x] Hash calculation should be speed optimized, especially for large files.
- [x] The tool should ensure accurate hash values to avoid false negatives during verification.