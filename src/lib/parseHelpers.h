#pragma once

#include <cassert>
#include <string>
#include <sstream>

static inline char getClosingSymbol(const char openingSymbol);
static inline bool isNumber(char character);

static inline int findEnclosingIndex(const std::string &original, int index) {
	const char start = original[index];

	// Numbers are special! oh my! They end on the first non-numerical char
	if (isNumber(start)) {
		// Numbers end on the first non-numerical char
		while (isNumber(original[++index]));

		return index - 1;
	}

	const char end = getClosingSymbol(start);
	// If they're the same we don't need to worry about nesting
	if (start == end) {
		int end = original.find(start, index + 1);

		// But we still have to ignore escaped characters
		while (original.at(end - 1) == '\\') {
			end = original.find(start, end + 1);
		}

		return end;
	}

	// Otherwise we might get some nasty stuff like {{{}{}}{}}.
	int level = 1;
	while (level > 0) {
		const char nextChar = original[++index];
		assert(nextChar != 0);

		if (nextChar == start) level++;
		if (nextChar == end) level--;
	}

	return index;
}

static inline char getClosingSymbol(const char openingSymbol) {
	switch (openingSymbol) {
		case '[': return ']';
		case '{': return '}';
		case 'f': return 'e'; // false
		case 't': return 'e'; // true
	}
	return openingSymbol;
}

static inline std::string *getInsideChunk(const std::string &original, const int index, int *endIndexPtr) {
	auto endChar = getClosingSymbol(original[index]);
	int &endIndex = *endIndexPtr;
	auto beginIndex = index + 1;
	endIndex = original.find_last_of(endChar, original.length() - beginIndex);

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
	endIndex = original.find_last_of(endChar, original.length() - beginIndex);

	auto length = endIndex + 1 - index;

	return new std::string(original, index, length);
}

static inline bool isNumber(char character) {
	return character >= '0' && character <= '9';
}

static inline void splitString(const std::string &original, const char delimiter, std::string *first, std::string *second) {
	auto index = original.find(delimiter);
	(*first) = original.substr(0, index);
	(*second) = original.substr(index + 1, original.length() - (index + 1));
}

static inline unsigned long stringToUnsignedLong(const std::string &original) {
	unsigned long result;
	std::istringstream is(original);
	is >> result;
	return result;
}

