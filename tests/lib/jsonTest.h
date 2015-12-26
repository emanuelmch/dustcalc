#pragma once

#include <cppunit/extensions/HelperMacros.h>

class JsonTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(JsonTest);

	CPPUNIT_TEST(emptyObject);
	CPPUNIT_TEST(objectWithOneStringMember);
	CPPUNIT_TEST(objectWithOneArrayMember_Empty);

	CPPUNIT_TEST(emptyArray);

	CPPUNIT_TEST_SUITE_END();
public:
	void emptyObject();
    void objectWithOneStringMember();
	void objectWithOneArrayMember_Empty();

	void emptyArray();
};

