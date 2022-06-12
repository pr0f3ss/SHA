/** @file
 * @brief Header file describing the function signatures and the constants of the SHA256 Algorithm
 */

#ifndef H_SHA256
#define H_SHA256

#include <string>
#include <cstdint>

class SHA256{
private:
	typedef uint32_t uint32;

	const uint32 hPrime[8] = {static_cast<unsigned int>(0xc6a09e667u), 
								static_cast<unsigned int>(0xbb67ae85u), 
								static_cast<unsigned int>(0x3c6ef372u), 
								static_cast<unsigned int>(0xa54ff53au), 
								static_cast<unsigned int>(0x510e527fu), 
								static_cast<unsigned int>(0x9b05688cu), 
								static_cast<unsigned int>(0x1f83d9abu), 
								static_cast<unsigned int>(0x5be0cd19u)
							};

	const uint32 k[64] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
		0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
		0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
		0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
		0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
		0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	};

	uint32** preprocess(const unsigned char* input, size_t& nBuffer);
	void appendLen(size_t l, uint32& lo, uint32& hi);
	void process(uint32** buffer, size_t nBuffer, uint32* h);
	std::string digest(uint32* h);
	void freeBuffer(uint32** buffer, size_t nBuffer);

	// Operations
	#define Ch_s(x,y,z) ((x&y)^(~x&z))
	#define Maj_s(x,y,z) ((x&y)^(x&z)^(y&z))
	#define RotR_s(x, n) ((x>>n)|(x<<((sizeof(x)<<3)-n)))
	#define Sig0_s(x) ((RotR_s(x, 2))^(RotR_s(x,13))^(RotR_s(x, 22)))
	#define Sig1_s(x) ((RotR_s(x, 6))^(RotR_s(x,11))^(RotR_s(x, 25)))
	#define sig0_s(x) (RotR_s(x, 7)^RotR_s(x,18)^(x>>3))
	#define sig1_s(x) (RotR_s(x, 17)^RotR_s(x,19)^(x>>10))

	// Constants
	unsigned int const SEQUENCE_LEN = (512/32);
	size_t const HASH_LEN = 8;
	size_t const WORKING_VAR_LEN = 8;
	size_t const MESSAGE_SCHEDULE_LEN = 64;
	size_t const MESSAGE_BLOCK_SIZE = 512;
	size_t const CHAR_LEN_BITS = 8;
	size_t const OUTPUT_LEN = 8;
	size_t const WORD_LEN = 4;

public:
	std::string hash(const std::string input);

	SHA256();
	~SHA256();
};



#endif