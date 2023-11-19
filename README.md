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

## Проверка контрольных сумм файла

**Цель:** Создать инструмент, который вычисляет и проверяет контрольные суммы или криптографические хэши для проверки целостности файла.

**Функциональные требования:**

- [x] Инструмент должен поддерживать как минимум два алгоритма хеширования (например, SHA-256, MD5).
- [x] Пользователи должны иметь возможность выбрать файл и вычислить его контрольную сумму.
- [x] Инструмент должен позволять пользователям сравнивать вычисленную контрольную сумму с предоставленной для проверки целостности файла.
- [x] Предоставить простой пользовательский интерфейс через командную строку.
- [x] Реализовать обработку ошибок для отсутствующих файлов или прав на чтение.

**Критерии производительности:**

- [x] Вычисление хеша должно быть оптимизировано по скорости, особенно для больших файлов.
- [x] Инструмент должен обеспечивать точные значения хеша, чтобы избежать ложных отрицательных результатов при проверке.