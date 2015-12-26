#include "parseHelpersTest.h"

#include "../../src/lib/parseHelpers.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ParseHelpersTest);

using std::string;

void ParseHelpersTest::testInsideChunkWithMatchingSymbols() {
	const string original = "A '1234' B";
	int endIndex = 0;

	string *resultPtr = getInsideChunk(original, 2, &endIndex);

	// Move the result into a non-pointer string, so we don't leak it in case we fail
	string result = *resultPtr;
	delete resultPtr;

	CPPUNIT_ASSERT_EQUAL(string("1234"), result);
	CPPUNIT_ASSERT_EQUAL(6, endIndex);
}

void ParseHelpersTest::testInsideChunkWithDifferentSymbols() {
	const string original = "A [1234] B";
	int endIndex = 0;

	string *resultPtr = getInsideChunk(original, 2, &endIndex);

	// Move the result into a non-pointer string, so we don't leak it in case we fail
	string result = *resultPtr;
	delete resultPtr;

	CPPUNIT_ASSERT_EQUAL(string("1234"), result);
	CPPUNIT_ASSERT_EQUAL(6, endIndex);
}

void ParseHelpersTest::testOutsideChunkWithMatchingSymbols() {
	const string original = "A '1234' B";
	int endIndex = 0;

	string *resultPtr = getOutsideChunk(original, 2, &endIndex);

	// Move the result into a non-pointer string, so we don't leak it in case we fail
	string result = *resultPtr;
	delete resultPtr;

	CPPUNIT_ASSERT_EQUAL(string("'1234'"), result);
	CPPUNIT_ASSERT_EQUAL(7, endIndex);
}

void ParseHelpersTest::testOutsideChunkWithDifferentSymbols() {
	const string original = "A {1234} B";
	int endIndex = 0;

	string *resultPtr = getOutsideChunk(original, 2, &endIndex);

	// Move the result into a non-pointer string, so we don't leak it in case we fail
	string result = *resultPtr;
	delete resultPtr;

	CPPUNIT_ASSERT_EQUAL(string("{1234}"), result);
	CPPUNIT_ASSERT_EQUAL(7, endIndex);
}

void ParseHelpersTest::testSplitString() {
    const string original = "\"teste\":123";
    string first, second;

    splitString(original, ':', &first, &second);

    CPPUNIT_ASSERT_EQUAL(string("\"teste\""), first);
    CPPUNIT_ASSERT_EQUAL(string("123"), second);
}
