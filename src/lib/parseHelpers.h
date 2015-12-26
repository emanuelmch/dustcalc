#pragma once

#include <string>
#include <sstream>

static inline char getClosingSymbol(const char openingSymbol) {
	switch (openingSymbol) {
		case '[': return ']';
		case '{': return '}';
	}
	return openingSymbol;
}

static inline std::string *getInsideChunk(const std::string &original, const int index, int *endIndexPtr) {
	auto endChar = getClosingSymbol(original[index]);
	int &endIndex = *endIndexPtr;
	auto beginIndex = index + 1;
	endIndex = original.find(endChar, beginIndex);

	auto length = endIndex - beginIndex;
	--endIndex;

	return new std::string(original, beginIndex, length);
}

static inline std::string *getInsideChunk(const std::string &original) {
	int endIndex;
	return getInsideChunk(original, 0, &endIndex);
}

static inline std::string *getOutsideChunk(const std::string &original, const int index, int *endIndexPtr) {
	auto endChar = getClosingSymbol(original[index]);
	int &endIndex = *endIndexPtr;
	auto beginIndex = index + 1;
	endIndex = original.find(endChar, beginIndex);

	auto length = endIndex + 1 - index;

	return new std::string(original, index, length);
}

static inline bool isNumber(char character) {
	return character >= '0' && character <= '9';
}

static inline unsigned long stringToUnsignedLong(const std::string &original) {
	unsigned long result;
	std::istringstream is(original);
	is >> result;
	return result;
}

