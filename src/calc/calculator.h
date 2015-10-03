#pragma once

#include "../data/collection.h"
#include "../data/library.h"

#include <list>
#include <string>

namespace Calc {

struct CalcResult {
	std::string name;
	int expectedValue;
};

class Calculator {
public:
	Calculator();
	~Calculator();

	std::list<CalcResult> calculateAll(Data::Library&,Data::Collection&);
};

}

