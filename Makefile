CC=clang++ -std=c++11 -I/usr/local/Cellar/openssl/1.0.2k/include/ -L/usr/local/Cellar/openssl/1.0.2k/lib/

hash: hash.cc
	$(CC) -o hash hash.cc -lcrypto
