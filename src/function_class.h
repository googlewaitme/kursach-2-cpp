#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include <cmath>

class CalculatorFunction
{
public:
	CalculatorFunction() {

	};

	float virtual calc(float value) {
		return value;
	};
};


class ExpFunction: public CalculatorFunction
{
public:
	ExpFunction() {};
	float calc(float value) override {
		return exp(2 * value);
	}
};


class OneFunction: public CalculatorFunction
{
public:
	OneFunction() {};

	float calc(float value) override {
		return 1;
	}
};


#endif // CALCULATOR_H_INCLUDED
