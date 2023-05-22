/** @file
 * @brief Implementation of the SHA256 Algorithm
 */

#include "SHA256.h"
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdint>
#include <sstream>
#include <cstdint>

typedef uint32_t uint32;

/**
 * SHA256 class constructor
 */
SHA256::SHA256() = default;

/**
 * SHA256 class destructor
 */
SHA256::~SHA256() = default;

/**
 * Returns a message digest using the SHA256 algorithm
 * @param input message string used as an input to the SHA256 algorithm, must be < size_t bits
 */
std::string SHA256::hash(const std::string& input) const{
	size_t nBuffer; // amount of message blocks
    // message block buffers (each 512-bit = 16 32-bit words)
    auto* h = new uint32[SHA_256::HASH_LEN]; // buffer holding the message digest (256-bit = 8 32-bit words)

	uint32** buffer = preprocess(reinterpret_cast<const unsigned char*>(input.c_str()), nBuffer);
	process(buffer, nBuffer, h);

	freeBuffer(buffer, nBuffer);
	return digest(h);
}

/**
 * Preprocessing of the SHA256 algorithm
 * @param input message in byte representation
 * @param nBuffer amount of message blocks 
 */
uint32** SHA256::preprocess(const unsigned char* input, size_t &nBuffer){
	// Padding: input || 1 || 0*k || l (in 64-bit representation)
    const size_t mLen = strlen(reinterpret_cast<const char*>(input));
    const size_t l = mLen * SHA_256::CHAR_LEN_BITS; // length of input in bits
    const size_t padding = (448-1-l) % SHA_256::MESSAGE_BLOCK_SIZE; // length of zero bit padding (l + 1 + k = 448 mod 512) 
	nBuffer = (l+1+padding+64) / SHA_256::MESSAGE_BLOCK_SIZE;

    auto** buffer = new uint32*[nBuffer];

	for(size_t i=0; i<nBuffer; i++){
		buffer[i] = new uint32[SHA_256::SEQUENCE_LEN];
	}

    // Either copy existing message, add 1 bit or add 0 bit
	for(size_t i=0; i<nBuffer; i++){
		for(size_t j=0; j< SHA_256::SEQUENCE_LEN; j++){
			uint32 in = 0x00u;
			for(size_t k=0; k< SHA_256::WORD_LEN; k++){
                const size_t index = i * 64 + j * 4 + k;
				if(index < mLen){
					in = in<<8 | static_cast<unsigned int>(input[index]);
				}else if(index == mLen){
					in = in<<8 | 0x80u;
				}else{
					in = in<<8 | 0x00u;
				}
			}
			buffer[i][j] = in;
		}
	}

	// Append the length to the last two 32-bit blocks
	appendLen(l, buffer[nBuffer-1][SHA_256::SEQUENCE_LEN-1], buffer[nBuffer-1][SHA_256::SEQUENCE_LEN-2]);
	return buffer;
}

/**
 * Processing of the SHA256 algorithm
 * @param buffer array holding the preprocessed 
 * @param nBuffer amount of message blocks 
 * @param h array of output message digest
 */
void SHA256::process(uint32** buffer, const size_t nBuffer, uint32* h) const
{
	uint32 s[SHA_256::WORKING_VAR_LEN];
	uint32 w[SHA_256::MESSAGE_SCHEDULE_LEN]; 

	memcpy(h, hPrime, SHA_256::WORKING_VAR_LEN*sizeof(uint32));

	for(size_t i=0; i<nBuffer; i++){
		// copy over to message schedule
		memcpy(w, buffer[i], SHA_256::SEQUENCE_LEN*sizeof(uint32));

		// Prepare the message schedule
		for(size_t j=16; j< SHA_256::MESSAGE_SCHEDULE_LEN; j++){
			w[j] = w[j-16] + sig0_s(w[j-15]) + w[j-7] + sig1_s(w[j-2]);
		}
		// Initialize the working variables
		memcpy(s, h, SHA_256::WORKING_VAR_LEN*sizeof(uint32));

		// Compression
		for(size_t j=0; j< SHA_256::MESSAGE_SCHEDULE_LEN; j++){
            const uint32 temp1 = s[7] + Sig1_s(s[4]) + Ch_s(s[4], s[5], s[6]) + k[j] + w[j];
            const uint32 temp2 = Sig0_s(s[0]) + Maj_s(s[0], s[1], s[2]);

			s[7] = s[6];
			s[6] = s[5];
			s[5] = s[4];
			s[4] = s[3] + temp1;
			s[3] = s[2];
			s[2] = s[1];
			s[1] = s[0];
			s[0] = temp1 + temp2;
		}

		// Compute the intermediate hash values
		for(size_t j=0; j< SHA_256::WORKING_VAR_LEN; j++){
			h[j] += s[j];
		}
	}

}

/**
 * Appends the length of the message in the last two message blocks
 * @param l message size in bits
 * @param lo pointer to second last message block
 * @param hi pointer to last message block
 */
void SHA256::appendLen(const size_t l, uint32& lo, uint32& hi){
	lo = l;
	hi = 0x00;
}

/**
 * Outputs the final message digest in hex representation
 * @param h array of output message digest
 */
std::string SHA256::digest(const uint32* h){
	std::stringstream ss;
	for(size_t i=0; i< SHA_256::OUTPUT_LEN; i++){
		ss << std::hex << std::setw(8) << std::setfill('0') << h[i];
	}
	delete[] h;
	return ss.str();
}
	
/**
 * Free the buffer correctly
 * @param buffer array holding the preprocessed 
 * @param nBuffer amount of message blocks 
 */
void SHA256::freeBuffer(uint32** buffer, const size_t nBuffer){
	for(size_t i=0; i<nBuffer; i++){
		delete[] buffer[i];
	}

	delete[] buffer;
}

