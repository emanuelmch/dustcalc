#include "calculator.h"

using Calc::Calculator;
using Calc::CalcResult;
using Data::CardSet;
using std::vector;

Calculator::Calculator() { }
Calculator::~Calculator() { }

vector<CalcResult> Calculator::calculateAll(Data::Library &library, Data::Collection&) {
	const int CommonValue = 40;
	const int RareValue = 100;
	const int EpicValue = 400;
	const int LegendaryValue = 1600;

	vector<CalcResult> results;

	for(auto it = library.cardSets.begin(); it != library.cardSets.end(); ++it) {
		CardSet *cardSet = (*it);
		unsigned int dustTotal = (cardSet->commonCount * CommonValue) +
									(cardSet->rareCount * RareValue) +
									(cardSet->epicCount * EpicValue) +
									(cardSet->legendaryCount * LegendaryValue);
		CalcResult result;
		result.name = cardSet->name;
		result.expectedValue = dustTotal;
		results.push_back(result);
	}

	return results;
}

