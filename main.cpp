#include <fstream>
#include "utils.h"


int main() 
{
	// дано n-количество эл-в, x_mas и y_mas в input.txt
	int n;
	float temp;
	fin >> n;	

	std::ifstream fin("input.txt");
	float * x_mas = Utils::get_float_array(n, fin);
	float * y_mas = Utils::get_float_array(n, fin);
	

	return 0;
}

