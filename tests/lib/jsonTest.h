#pragma once

#include "../../src/lib/json.h"

#include <cppunit/extensions/HelperMacros.h>

#include <string>

class JsonTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(JsonTest);

	CPPUNIT_TEST(emptyObject);
	CPPUNIT_TEST(objectWithOneStringMember);
	CPPUNIT_TEST(objectWithOneIntegerMember);
	CPPUNIT_TEST(objectWithOneBooleanMember_True);
	CPPUNIT_TEST(objectWithOneBooleanMember_False);
	CPPUNIT_TEST(objectWithOneArrayMember_Empty);
	CPPUNIT_TEST(objectWithSpacedStrings);
	CPPUNIT_TEST(objectWithManyMembers);

	CPPUNIT_TEST(emptyArray);
	CPPUNIT_TEST(arrayWithOneStringElement);
	CPPUNIT_TEST(arrayWithOneIntegerElement);
	CPPUNIT_TEST(arrayWithOneBooleanElement_True);
	CPPUNIT_TEST(arrayWithOneBooleanElement_False);
	CPPUNIT_TEST(arrayWithOneObject_Empty);
	CPPUNIT_TEST(arrayWithManyElements);

	CPPUNIT_TEST(objectWithArrayWithObjectWithArrayWithObject);
	CPPUNIT_TEST(simplifiedRealData);

	CPPUNIT_TEST_SUITE_END();
public:
	void emptyObject();
	void objectWithOneStringMember();
	void objectWithOneIntegerMember();
	void objectWithOneBooleanMember_True();
	void objectWithOneBooleanMember_False();
	void objectWithOneArrayMember_Empty();
	void objectWithSpacedStrings();
	void objectWithManyMembers();

	void emptyArray();
	void arrayWithOneStringElement();
	void arrayWithOneIntegerElement();
	void arrayWithOneBooleanElement_True();
	void arrayWithOneBooleanElement_False();
	void arrayWithOneObject_Empty();
	void arrayWithManyElements();

	void objectWithArrayWithObjectWithArrayWithObject();
	void simplifiedRealData();

private:
	void checkString(const std::string&, const Lib::Json*, const std::string&, const char* = NULL);
	void checkNumber(const std::string&, const Lib::Json*, unsigned long, const char* = NULL);
	void checkArray(const std::string&, const Lib::Json*, size_t, const char* = NULL);
	void checkObject(const std::string&, const Lib::Json*, size_t, const char* = NULL);
	void checkBoolean(const std::string&, const Lib::Json*, bool, const char* = NULL);
};

