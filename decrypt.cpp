#include "Header.h"


void decr(std::string file_name, unsigned int key, unsigned int leftshift) {
	srand(key);

	std::ifstream readf;

	readf.open(file_name, std::ios::binary);

	std::vector<char> encryptData((std::istreambuf_iterator<char>(readf)),
		std::istreambuf_iterator<char>());

	readf.close();

	std::vector<char> decryptData(encryptData.size());

	for (int i = 0; i < encryptData.size(); i += 2) {
		unsigned int gamma = rand();
		unsigned char byte1 = encryptData[i];
		unsigned char byte2 = i + 1 < encryptData.size() ? encryptData[i + 1] : 0u;

		unsigned int encrypt = ((static_cast<unsigned int>(byte1) << 8u) |
			static_cast<unsigned int> (byte2));

		unsigned int shift_encrypt = ((encrypt & 0xFFFF) >> leftshift) |
			encrypt << (16 - leftshift);

		unsigned int res = shift_encrypt ^ gamma;

		unsigned char r1 = res >> 8;
		unsigned char r2 = res;
		decryptData[i] = r1;
		decryptData[i + 1] = r2;
	}

	for (int i = 0; i < decryptData.size(); i++) {
		std::cout << decryptData[i];
	}
}