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

	for (int i = 0; i < byte.size(); i += 4) {
		unsigned int gamma = rand();
		unsigned char b0 = byte[i];
		unsigned char b1 = i + 1 < byte.size() ? byte[i + 1] : 0u;
		unsigned char b2 = i + 2 < byte.size() ? byte[i + 2] : 0u;
		unsigned char b3 = i + 3 < byte.size() ? byte[i + 3] : 0u;
		unsigned int message_to_int =
			((static_cast<unsigned int>(b0) << 24u) | (static_cast<unsigned int>(b1) << 16u) |
				(static_cast<unsigned int>(b2) << 8u) | (static_cast<unsigned int>(b3)));

		unsigned int message_xored = message_to_int ^ gamma;

		unsigned int encrypt = (message_xored << leftshift) | (message_xored & 0xFFFFFFFF) << (32 - leftshift);

		//std::cout << message_xored << " xor \n" << encrypt << " enc \n";

		char r1 = encrypt << 24;
		char r2 = encrypt << 16;
		char r3 = encrypt << 8;
		char r4 = encrypt;
		std::cout << r1 << r2 << r3 << r4;
		file.write(&r1, sizeof(r1));
		file.write(&r2, sizeof(r2));
		file.write(&r3, sizeof(r3));
		file.write(&r4, sizeof(r4));
	}
	file.close();
	std::cout << "\n";
}
