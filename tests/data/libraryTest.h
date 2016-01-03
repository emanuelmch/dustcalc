#pragma once

#include "../../src/data/library.h"

#include <cppunit/extensions/HelperMacros.h>

class LibraryTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(LibraryTest);

	CPPUNIT_TEST(oneCommonCard);

	CPPUNIT_TEST_SUITE_END();
public:
	void oneCommonCard();
};

