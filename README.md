# SHA512
C++ implementation of the SHA512 hashing algorithm.

## Usage
```c++
#include "SHA512.h" //include SHA512 definition

SHA512 sha512; //instantiate a SHA512 object
sha512.hash("Example"); //returns the hash as a string
```

## Compile and run
1. Clone the repository onto your disk: `git clone https://github.com/pr0f3ss/SHA512.git` 
2. Include the header file in your .cpp file: `#include "SHA512.h"`
3. Compile: `g++ yourFileName.cpp SHA512.cpp` 
4. Run: `./a.out`

## Example
hashVal.cpp provides an example usage of this SHA512 repository. It hashes the first argument given when running the object file.

1. Clone the repository onto your disk: `git clone https://github.com/pr0f3ss/SHA512.git`
2. Compile: `g++ hashVal.cpp SHA512.cpp -o SHA512Hash.out`
3. Run: `./SHA512Hash.out exampleString`
4. Output: `fb1d5d8e10288f1e13bdf61e81c1b8eea4522504e16d2dbbd8f76bc7641ea59787498d44932ef5f1545a7dfe0396515ed9cb7c728c76e7ee25cf538f2a3294`
