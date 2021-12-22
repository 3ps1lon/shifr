#include "Header.h"

void enc(std::string word, std::string file_name, unsigned int key, unsigned int leftshift) {
	const char* data = word.data();
	int size = word.size();

	std::vector<char> byte(size);

	for (int i = 0; i < size; i++) {
		byte[i] = data[i];
		//std::cout << byte[i] << std::endl;
	}
	srand(key);

	std::ofstream file;
	file.open(file_name, std::ios::binary);

	for (int i = 0; i < byte.size(); i += 2) {
		unsigned int gamma = rand();
		unsigned char byte1 = byte[i];
		unsigned char byte2 = i + 1 < byte.size() ? byte[i + 1] : 0u;

		unsigned int message_xored = ((static_cast<unsigned int>(byte1) << 8u) |
			static_cast<unsigned int>(byte2)) ^ gamma;

		unsigned int encrypt = (message_xored << leftshift) | (message_xored & 0xFFFF) >> (16 - leftshift);

		//std::cout << message_xored << " xor \n" << encrypt << " enc \n";

		char r1 = encrypt >> 8;
		char r2 = encrypt;
		std::cout << r1 << r2;
		file.write(&r1, sizeof(r1));
		file.write(&r2, sizeof(r2));
	}
	file.close();
	std::cout << "\n";
}