#include "Header.h"


void decr(std::string file_name, unsigned int key, unsigned int leftshift) {
	srand(key);

	std::ifstream readf;

	readf.open(file_name, std::ios::binary);

	std::vector<char> encryptData((std::istreambuf_iterator<char>(readf)),
		std::istreambuf_iterator<char>());

	readf.close();

	std::vector<char> decryptData(encryptData.size());

	for (int i = 0; i < encryptData.size(); i += 4) {
		unsigned int gamma = rand();
		unsigned char b0 = encryptData[i];
		unsigned char b1 = i + 1 < encryptData.size() ? encryptData[i + 1] : 0u;
		unsigned char b2 = i + 2 < encryptData.size() ? encryptData[i + 2] : 0u;
		unsigned char b3 = i + 3 < encryptData.size() ? encryptData[i + 3] : 0u;

		unsigned int encrypt = ((static_cast<unsigned int>(b0) << 24u) |
			(static_cast<unsigned int>(b1) << 16u) |
			(static_cast<unsigned int>(b2) << 8u) | (static_cast<unsigned int>(b3)));

		unsigned int shift_encrypt = ((encrypt & 0xFFFFFFFF) << leftshift) |
			encrypt >> (32 - leftshift);

		unsigned int res = shift_encrypt ^ gamma;

		unsigned char r0 = res >> 24;
		unsigned char r1 = res >> 16;
		unsigned char r2 = res >> 8;
		unsigned char r3 = res;

		decryptData[i] = r0;
		decryptData[i + 1] = r1;
		decryptData[i + 2] = r2;
		decryptData[i + 3] = r3;
	}

	for (int i = 0; i < decryptData.size(); i++) {
		std::cout << decryptData[i];
	}
}
