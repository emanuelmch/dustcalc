#include <iostream>

#include "calc/calculator.h"
#include "data/collection.h"
#include "data/library.h"

using Calc::Calculator;
using Calc::CalcResult;
using Data::Collection;
using Data::Library;

int main() {
	std::cout << "Reading library..." << std::endl;
	Library library;
	library.init();

	std::cout << "Reading collection..." << std::endl;
	Collection collection;
	collection.init();

    std::cout << "Calculating stuff..." << std::endl;
	Calculator calculator;
	auto results = calculator.calculateAll(library, collection);

	for (CalcResult result : results) {
		std::cout << result.name << " has an EV of " << result.expectedValue << std::endl;
	}
}

