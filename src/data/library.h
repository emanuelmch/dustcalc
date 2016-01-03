#pragma once

#include "cardSet.h"

#include <string>
#include <vector>

namespace Data {

class Library {
public:
	Library();
	~Library();

	void init();
	void fromJson(const std::string &);

	std::vector<CardSet*> cardSets;
};

}

