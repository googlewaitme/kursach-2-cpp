#include <fstream>
#include <iostream>
#include "utils.h"
#include <vector>


void get_array(std::vector<float> & vec, int array_size, std::ifstream& fin) {
	float temp;
	for (int i=0; i<array_size; i++) {
		fin >> temp;
		vec.push_back(temp);
	}
}
