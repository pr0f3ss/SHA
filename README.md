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
