#pragma once

#include "../data/collection.h"
#include "../data/library.h"

#include <string>
#include <vector>

namespace Calc {

struct CalcResult {
	std::string name;
	unsigned int expectedValue;
};

class Calculator {
public:
	Calculator();
	~Calculator();

	std::vector<CalcResult> calculateAll(Data::Library&,Data::Collection&);
};

}

