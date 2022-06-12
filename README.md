# SHA512
C++ implementation of the SHA512, SHA384 and SHA256 hashing algorithms. Requires the messages to be of size `< size_t` bytes.

## Usage example
```c++
#include "SHA512.h" //include SHA512 definition

SHA512 sha512; //instantiate a SHA512 object
sha512.hash("Example"); //returns the hash as a string
```

## Compile and run
1. Clone the repository onto your disk: `git clone https://github.com/pr0f3ss/SHA512.git` 
2. Compile either statically or shared: `make static / make shared` 
3. Include the header file in your .cpp file, e.g. `#include "SHA256.h"`, and use the library functions
4. a) Compile using static library: `g++ main.cpp -Lbin/static -lsha -o static_binary` 
4. b) Compile using shared library: `g++ main.cpp -lsha -o shared_binary` 
5. Run: `./x_binary` (where `x` either `shared` or `static`) 

## Example
src/example.cpp provides an example usage of this repository. It hashes the first argument given when running the object file using the SHA512, SHA384 and SHA256 methods. `make all` compiles two binaries using either static or shared linking in `bin/static-example` or `bin/shared-example` respectively.

1. Clone the repository onto your disk: `git clone https://github.com/pr0f3ss/SHA512.git`
2. Compile: `make all`
3. Run: `./bin/x-example test` (where `x` either `shared` or `static`)
4. Output: 
```
SHA256:9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08
SHA384:768412320f7b0aa5812fce428dc4706b3cae50e02a64caa16a782249bfe8efc4b7ef1ccb126255d196047dfedf17a0a9
SHA512:ee26b0dd4af7e749aa1a8ee3c10ae9923f618980772e473f8819a5d4940e0db27ac185f8a0e1d5f84f88bc887fd67b143732c304cc5fa9ad8e6f57f50028a8ff
```
