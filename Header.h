#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void enc(std::string word, std::string file_name, unsigned int key, unsigned int leftshift);

void decr(std::string file_name, unsigned int key, unsigned int leftshift);