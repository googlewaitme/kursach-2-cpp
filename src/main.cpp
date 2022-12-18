#include <iostream>
#include <fstream>
#include "utils.h"
#include <vector>
#include "function_class.h"
#include "solution.hpp"


int main() 
{
	// дано n-количество эл-в, x_mas и y_mas в input.txt
	std::cout << "Program started!" << std::endl;
	int n;
	float temp;

	std::ifstream fin("src/input.txt");
    
    if (fin) {
        std::cout << "file is opened" << std::endl;
    } else {
        std::cout << "file is NOT opened" << std::endl;
        return 0;
    }

	fin >> n;	

    std::cout << "n = " << n << std::endl;
	std::vector<float> x_vec(n);
	std::vector<float> y_vec(n);

	for (int i=0; i<n; i++) {
	    fin >> temp; 
        x_vec[i] = temp;
    }
    for (int i=0; i<n; i++) {
	    fin >> temp; 
        y_vec[i] = temp;
    }
    std::cout << "x_vec: ";	

	for (int i=0; i<n; i++) {
		std::cout << x_vec[i] << " ";
	}
	std::cout << std::endl;
    std::cout << "y_vec: ";
	for (int i=0; i<n; i++) {
		std::cout << y_vec[i] << " ";
	}
	std::cout << std::endl;

	std::vector<CalculatorFunction*> functions = {new OneFunction(), new CalculatorFunction(), new ExpFunction()};

	for (int func=0; func<3; func++) {
		for (int i=0; i<n; i++) {
			std::cout << functions[func] -> calc(x_vec[i]) << " ";
		}
		std::cout << std::endl;
	}

	Solution solution(n, x_vec, y_vec, functions);

	solution.solve();
	fin.close();
	return 0;
}

