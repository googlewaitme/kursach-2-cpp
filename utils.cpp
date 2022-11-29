#include <fstream>
#include "utils.h"
using namespace Utils;


float * get_float_array(int array_size, std::ifstream& fin) {
	float * array = new float[array_size];
	float temp;
	for (int i=0; i<array_size; i++) {
		fin >> temp;
		array[i] = temp;
	}
	return array;
}

