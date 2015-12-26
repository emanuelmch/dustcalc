#include "jsonTest.h"

#include "../../src/lib/json.h"

CPPUNIT_TEST_SUITE_REGISTRATION(JsonTest);

using Lib::Json;
using Lib::JsonType;
using std::string;
using std::vector;

void JsonTest::emptyObject() {
	string content = "{}";

	Json json;
	json.read(content);

	CPPUNIT_ASSERT(json.members.empty());
}

void JsonTest::emptyArray() {
	string content = "{\"array\":[]}";

	Json json;
	json.read(content);

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Member count should be 1", 1, (int)json.members.size());

	Json* member = json.getMember("array");
	CPPUNIT_ASSERT(member != NULL);
	CPPUNIT_ASSERT_EQUAL(JsonType::Array, member->type);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Array member should be called 'array'", string("array"), member->name);
	CPPUNIT_ASSERT(member->arrayValue.empty());
}
