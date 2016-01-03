#include "library.h"

#include "../lib/json.h"
#include <fstream>
#include <iostream>

using Data::Library;
using Data::CardSet;
using Lib::Json;
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

void Library::fromJson(const std::string &content) {
	Json json;
	json.read(content);

	for (auto it = json.arrayValue.begin(); it != json.arrayValue.end(); ++it) {
		Json *card = (*it);
		string rarity = *(card->getMember("rarity")->stringValue);
		string setName = *(card->getMember("set")->stringValue);
		CardSet *cardSet = getCardSet(setName);
		if (rarity == "COMMON") {
			cardSet->commonCount++;
		} else if (rarity == "RARE") {
			cardSet->rareCount++;
		} else if (rarity == "EPIC") {
			cardSet->epicCount++;
		} else if (rarity == "LEGENDARY") {
			cardSet->legendaryCount++;
		}
	}
}

CardSet *Library::getCardSet(const std::string &name) {
	for (auto it = cardSets.begin(); it != cardSets.end(); ++it) {
		CardSet *cardSet = *it;
		if (cardSet->name == name)
			return *it;
	}
	CardSet *newSet = new CardSet(name);
	cardSets.push_back(newSet);
	return newSet;
}
