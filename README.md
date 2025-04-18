# EncryptedCommunication
This project is a C++ library that contains a set of classes that implement, using ```openssl``` under the hood, the following cryptographic functions :  

* AES 256 GCM :
    - Key generation, encryption and decryption
* RSA : 
    - Key generation, encryption, decryption, message digest (with SHA256) sing and verify
* SHA256 :
    - Hashing of arbitrary strings
* UTILITIES : 
    - String padding
    - Random string generation
    - Read/write/delete files
    - Base 64 encoding of ```std::vector<unsigned char>```
    - Base 64 decoding of strings

# Developement environment
This project was developed on Ubuntu 20.04.6 LTS

# Dependencies
cmake : 
```bash
$ sudo apt install cmake
```
openssl : 
```bash
$ sudo apt install libssl-dev
```
doxygen : 
```bash
$ sudo apt install doxygen
```
graphviz : 
```bash
$ sudo apt install graphviz
```

# Compilation instrunctions
Download the repository
```bash
$ git clone https://github.com/andresOchoaHernandez/EncryptedCommunication
```
Enter the repo, create a build folder and compile : 
```bash
$ cd EncryptedCommunication
$ mkdir build
$ mkdir cd build

# Configure CMake
$ cmake ..

# Build
$ make

# Run all the tests
$ make test
```
Some tests are very long, so if you want to run a specific test do :
```bash
# List all available tests
$ ctest -N

# Execute one test
$ ctest -R <test_name>
```