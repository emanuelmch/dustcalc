#pragma once

#include <string>

namespace Data {

class CardSet {
public:
	CardSet(const std::string &setName) :
		name(setName), commonCount(0), rareCount(0), epicCount(0), legendaryCount(0) {}

	std::string name;

	unsigned int commonCount;
	unsigned int rareCount;
	unsigned int epicCount;
	unsigned int legendaryCount;
};

}
