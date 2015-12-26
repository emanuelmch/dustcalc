#pragma once

#include <cppunit/extensions/HelperMacros.h>

class ParseHelpersTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ParseHelpersTest);

	CPPUNIT_TEST(testInsideChunkWithMatchingSymbols);
	CPPUNIT_TEST(testInsideChunkWithDifferentSymbols);
	CPPUNIT_TEST(testOutsideChunkWithMatchingSymbols);
	CPPUNIT_TEST(testOutsideChunkWithDifferentSymbols);

	CPPUNIT_TEST_SUITE_END();
public:
	void testInsideChunkWithMatchingSymbols();
	void testInsideChunkWithDifferentSymbols();
	void testOutsideChunkWithMatchingSymbols();
	void testOutsideChunkWithDifferentSymbols();
};
