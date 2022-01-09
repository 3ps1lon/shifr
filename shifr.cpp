#include "Header.h"


int main() {

	enc("d d.da/sda","test",45,4);       // word, file_name, seed_random, leftshift
	decr("test",45,3);					// file_name, seed_random, leftshift
	
	return 0;
}
