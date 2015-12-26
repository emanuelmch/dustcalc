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

	CPPUNIT_ASSERT_EQUAL(JsonType::Object, json.type);
	CPPUNIT_ASSERT(json.members.empty());
}

void JsonTest::objectWithOneStringMember() {
	string content = "{\"name\":\"value\"}";

	Json json;
	json.read(content);

	CPPUNIT_ASSERT_EQUAL(JsonType::Object, json.type);
	CPPUNIT_ASSERT_EQUAL(1, (int)json.members.size());

	Json* member = json.getMember("name");
	CPPUNIT_ASSERT(member != NULL);
	CPPUNIT_ASSERT_EQUAL(JsonType::String, member->type);
	CPPUNIT_ASSERT_EQUAL(string("name"), *(member->name));
	CPPUNIT_ASSERT_EQUAL(string("value"), *(member->stringValue));
}

void JsonTest::objectWithOneIntegerMember() {
	string content = "{\"name\":123}";

	Json json;
	json.read(content);

	CPPUNIT_ASSERT_EQUAL(JsonType::Object, json.type);
	CPPUNIT_ASSERT_EQUAL(1, (int)json.members.size());

	Json* member = json.getMember("name");
	CPPUNIT_ASSERT(member != NULL);
	CPPUNIT_ASSERT_EQUAL(JsonType::Number, member->type);
	CPPUNIT_ASSERT_EQUAL(string("name"), *(member->name));
	CPPUNIT_ASSERT_EQUAL((unsigned long)123, member->numberValue);
}

void JsonTest::objectWithOneBooleanMember_True() {
	string content = "{\"bool\":true}";

	Json json;
	json.read(content);

	CPPUNIT_ASSERT_EQUAL(JsonType::Object, json.type);
	CPPUNIT_ASSERT_EQUAL(1, (int)json.members.size());

	Json* member = json.getMember("bool");
	CPPUNIT_ASSERT(member != NULL);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Member type should be Boolean", JsonType::Boolean, member->type);
	CPPUNIT_ASSERT_EQUAL(string("bool"), *(member->name));
	CPPUNIT_ASSERT_EQUAL(true, member->booleanValue);
}

void JsonTest::objectWithOneBooleanMember_False() {
	string content = "{\"bool\":false}";

	Json json;
	json.read(content);

	CPPUNIT_ASSERT_EQUAL(JsonType::Object, json.type);
	CPPUNIT_ASSERT_EQUAL(1, (int)json.members.size());

	Json* member = json.getMember("bool");
	CPPUNIT_ASSERT(member != NULL);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Member type should be Boolean", JsonType::Boolean, member->type);
	CPPUNIT_ASSERT_EQUAL(string("bool"), *(member->name));
	CPPUNIT_ASSERT_EQUAL(false, member->booleanValue);
}

void JsonTest::objectWithOneArrayMember_Empty() {
	string content = "{\"array\":[]}";

	Json json;
	json.read(content);

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Member count should be 1", 1, (int)json.members.size());

	Json* member = json.getMember("array");
	CPPUNIT_ASSERT(member != NULL);
	CPPUNIT_ASSERT_EQUAL(JsonType::Array, member->type);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Array member should be called 'array'", string("array"), *(member->name));
	CPPUNIT_ASSERT(member->arrayValue.empty());
}

void JsonTest::emptyArray() {
	const string content = "[]";

	Json json;
	json.read(content);

	CPPUNIT_ASSERT(json.members.empty());
	CPPUNIT_ASSERT_EQUAL(JsonType::Array, json.type);

	CPPUNIT_ASSERT(json.arrayValue.empty());
}
