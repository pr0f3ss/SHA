# @file
# @brief Makefile to compile the SHA library as a static or shared library
# Options to compile example binaries with static/shared linking
#

all:
	make clean
	make exampleStatic
	make exampleShared

# ========= compile static example ========
exampleStatic:
	make static
	g++ src/example.cpp -Lbin/static -lsha -o bin/static-example

# ========= compile static example ========
exampleShared:
	make shared
	g++ src/example.cpp -lsha -o bin/shared-example

# ========= created static library ========
static:
	g++ -c 	src/SHA256.cpp 	-o bin/static/SHA256.o
	g++ -c 	src/SHA384.cpp 	-o bin/static/SHA384.o
	g++ -c  src/SHA512.cpp 	-o bin/static/SHA512.o

	ar rcs bin/static/libsha.a bin/static/SHA256.o bin/static/SHA384.o bin/static/SHA512.o

# ========= create shared library =========
shared:
	#
	# object files for shared libraries need to be compiled as position independent
	# code (-fPIC) because they are mapped to any position in the address space.
	#
	g++ -c -fPIC src/SHA256.cpp 	-o bin/shared/SHA256.o
	g++ -c -fPIC src/SHA384.cpp 	-o bin/shared/SHA384.o
	g++ -c -fPIC src/SHA512.cpp 	-o bin/shared/SHA512.o

	g++ -shared bin/shared/SHA256.o bin/shared/SHA384.o bin/shared/SHA512.o -o bin/shared/libsha.so

	# moving the shared object to a standard location
	sudo mv bin/shared/libsha.so /usr/lib
	sudo chmod 755 /usr/lib/libsha.so

clean:
	find ./bin/ -type f -delete

