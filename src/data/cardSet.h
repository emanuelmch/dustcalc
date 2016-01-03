#pragma once

namespace Data {

class CardSet {
public:
	CardSet() {}
	CardSet(unsigned int common, unsigned int rare, unsigned int epic, unsigned int legendary) :
		commonCount(common), rareCount(rare), epicCount(epic), legendaryCount(legendary) {}

	unsigned int commonCount;
	unsigned int rareCount;
	unsigned int epicCount;
	unsigned int legendaryCount;
};

}
