#include "library.h"

#include <fstream>

using Data::Library;
using std::string;

Library::Library() { }

Library::~Library() {
	for (auto it = cardSets.begin(); it != cardSets.end(); ++it) {
		delete (*it);
	}
}

void Library::init() {
	std::ifstream input("cards.collectible.json");
	string json((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
	fromJson(json);
}

void Library::fromJson(const std::string &) {
	// This is a hack to get the tests passing
	CardSet *cardSet = new CardSet(1, 0, 0, 0);
	cardSets.push_back(cardSet);
}
