#include "SHA512.h"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]){

	SHA512 sha512;
	std::stringstream ss;
	ss << argv[1];
	//abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu
	std::cout << sha512.hash(ss.str()) << std::endl;;

	return 0;
}