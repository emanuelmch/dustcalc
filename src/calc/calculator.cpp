#include "calculator.h"

using Calc::Calculator;
using Calc::CalcResult;

using std::list;

Calculator::Calculator() { }
Calculator::~Calculator() { }

list<CalcResult> Calculator::calculateAll(Data::Library&, Data::Collection&) {
	CalcResult x;
	x.name = "first";
	x.expectedValue = 1;

	CalcResult y;
	y.name = "second";
	y.expectedValue = 2;

	CalcResult z;
	z.name = "third";
	z.expectedValue = 3;

	list<CalcResult> results;
	results.push_back(x);
	results.push_back(y);
	results.push_back(z);

	return results;
}

