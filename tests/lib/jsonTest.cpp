#include "jsonTest.h"

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

void JsonTest::objectWithSpacedStrings() {
	const string content = "{\"My name is\":\"Jason. Ha!\"}";

	Json json;
	json.read(content);

    CPPUNIT_ASSERT_EQUAL(JsonType::Object, json.type);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Member count should be 1", 1, (int)json.members.size());

	Json* member = json.getMember("My name is");
    CPPUNIT_ASSERT(member != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Member type should be String", JsonType::String, member->type);
    CPPUNIT_ASSERT_EQUAL(string("Jason. Ha!"), *(member->stringValue));
}

void JsonTest::objectWithManyMembers() {
    const string content = "{\"one\":\"one\",\"two\":2,\"three\":true,\"four\":false}";

    Json json;
    json.read(content);

    CPPUNIT_ASSERT_EQUAL(JsonType::Object, json.type);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Member count should be 4", 4, (int)json.members.size());

    Json *stringMember = json.members[0];
    CPPUNIT_ASSERT(stringMember != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Member type should be String", JsonType::String, stringMember->type);
    CPPUNIT_ASSERT_EQUAL(string("one"), *(stringMember->stringValue));

    Json *numberMember = json.members[1];
    CPPUNIT_ASSERT(numberMember != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Member type should be Number", JsonType::Number, numberMember->type);
    CPPUNIT_ASSERT_EQUAL((unsigned long)2, numberMember->numberValue);

    Json *trueMember = json.members[2];
    CPPUNIT_ASSERT(trueMember != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Member type should be Boolean", JsonType::Boolean, trueMember->type);
    CPPUNIT_ASSERT_EQUAL(true, trueMember->booleanValue);

    Json *falseMember = json.members[3];
    CPPUNIT_ASSERT(falseMember != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Member type should be Boolean", JsonType::Boolean, falseMember->type);
    CPPUNIT_ASSERT_EQUAL(false, falseMember->booleanValue);
}

void JsonTest::emptyArray() {
    const string content = "[]";

    Json json;
    json.read(content);

    CPPUNIT_ASSERT(json.members.empty());
    CPPUNIT_ASSERT_EQUAL(JsonType::Array, json.type);

    CPPUNIT_ASSERT(json.arrayValue.empty());
}

void JsonTest::arrayWithOneStringElement() {
    const string content = "[\"element\"]";

    Json json;
    json.read(content);

    CPPUNIT_ASSERT(json.members.empty());
    CPPUNIT_ASSERT(json.type == JsonType::Array);

    vector<Json*> elements = json.arrayValue;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Element count should be 1", 1, (int)elements.size());

    Json *element = elements[0];
    CPPUNIT_ASSERT(element != NULL);
    CPPUNIT_ASSERT_EQUAL(JsonType::String, element->type);
    CPPUNIT_ASSERT_EQUAL(string("element"), *(element->stringValue));
}

void JsonTest::arrayWithOneIntegerElement() {
    const string content = "[123]";

    Json json;
    json.read(content);

    CPPUNIT_ASSERT(json.members.empty());
    CPPUNIT_ASSERT(json.type == JsonType::Array);

    vector<Json*> elements = json.arrayValue;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Element count should be 1", 1, (int)elements.size());

    Json *element = elements[0];
    CPPUNIT_ASSERT(element != NULL);
    CPPUNIT_ASSERT_EQUAL(JsonType::Number, element->type);
    CPPUNIT_ASSERT_EQUAL((unsigned long)123, element->numberValue);
}

void JsonTest::arrayWithOneBooleanElement_True() {
    const string content = "[true]";

    Json json;
    json.read(content);

    CPPUNIT_ASSERT(json.members.empty());
    CPPUNIT_ASSERT(json.type == JsonType::Array);

    vector<Json*> elements = json.arrayValue;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Element count should be 1", 1, (int)elements.size());

    Json *element = elements[0];
    CPPUNIT_ASSERT(element != NULL);
    CPPUNIT_ASSERT_EQUAL(JsonType::Boolean, element->type);
    CPPUNIT_ASSERT_EQUAL(true, element->booleanValue);
}

void JsonTest::arrayWithOneBooleanElement_False() {
    const string content = "[false]";

    Json json;
    json.read(content);

    CPPUNIT_ASSERT(json.members.empty());
    CPPUNIT_ASSERT(json.type == JsonType::Array);

    vector<Json*> elements = json.arrayValue;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Element count should be 1", 1, (int)elements.size());

    Json *element = elements[0];
    CPPUNIT_ASSERT(element != NULL);
    CPPUNIT_ASSERT_EQUAL(JsonType::Boolean, element->type);
    CPPUNIT_ASSERT_EQUAL(false, element->booleanValue);
}

void JsonTest::arrayWithOneObject_Empty() {
    const string content = "[{}]";

    Json json;
    json.read(content);

    CPPUNIT_ASSERT(json.members.empty());
    CPPUNIT_ASSERT(json.type == JsonType::Array);

    vector<Json*> elements = json.arrayValue;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Element count should be 1", 1, (int)elements.size());

    Json *element = elements[0];
    CPPUNIT_ASSERT(element != NULL);
    CPPUNIT_ASSERT_EQUAL(JsonType::Object, element->type);

    CPPUNIT_ASSERT(element->type == JsonType::Object);
    CPPUNIT_ASSERT(element->members.empty());
}

void JsonTest::arrayWithManyElements() {
    const string content = "[\"one\",2,true,false]";

    Json json;
    json.read(content);
	checkArray("root", &json, 4);

    Json *stringElement = json.arrayValue[0];
    checkString("stringElement", stringElement, "one");

    Json *numberElement = json.arrayValue[1];
    checkNumber("numberElement", numberElement, 2);

    Json *trueElement = json.arrayValue[2];
    checkBoolean("trueElement", trueElement, true);

    Json *falseElement = json.arrayValue[3];
    checkBoolean("falseElement", falseElement, false);
}

void JsonTest::objectWithArrayWithObjectWithArrayWithObject() {
    const string content = "{\"a\":[222,{\"b\":[{\"c\":123}],\"bb\":\"8\"}]}";

    Json levelOne;
    levelOne.read(content);
    checkObject("levelOne", &levelOne, 1);

    Json *levelTwo = levelOne.getMember("a");
    checkArray("levelTwo", levelTwo, 2);

	Json *levelThreeValue = levelTwo->arrayValue[0];
	checkNumber("levelThreeValue", levelThreeValue, 222);

    Json *levelThreeObject = levelTwo->arrayValue[1];
    checkObject("levelThreeObject", levelThreeObject, 2);

    Json *levelFourObject = levelThreeObject->getMember("b");
    checkArray("levelFourObject", levelFourObject, 1);

	Json *levelFourValue = levelThreeObject->getMember("bb");
	checkString("levelFourValue", levelFourValue, "8");

    Json *levelFive = levelFourObject->arrayValue[0];
    checkObject("levelFive", levelFive, 1);

    Json *levelSix = levelFive->getMember("c");
    checkNumber("levelSix", levelSix, 123);
}

// Private helper methods
void JsonTest::checkString(const std::string &tag, const Lib::Json *json, const std::string &value) {
    CPPUNIT_ASSERT_MESSAGE(tag + " should not be null", json != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should be of type String", JsonType::String, json->type);

    CPPUNIT_ASSERT_MESSAGE(tag + " should not have any members", json->members.empty());
    CPPUNIT_ASSERT_MESSAGE(tag + " should not have any elements", json->arrayValue.empty());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should have the correct stringValue", value, *(json->stringValue));
}

void JsonTest::checkNumber(const std::string &tag, const Lib::Json *json, unsigned long value) {
    CPPUNIT_ASSERT_MESSAGE(tag + " should not be null", json != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should be of type Number", JsonType::Number, json->type);

    CPPUNIT_ASSERT_MESSAGE(tag + " should not have any members", json->members.empty());
    CPPUNIT_ASSERT_MESSAGE(tag + " should not have any elements", json->arrayValue.empty());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should have the correct numberValue", value, json->numberValue);
}

void JsonTest::checkArray(const string &tag, const Json *json, unsigned long count) {
    CPPUNIT_ASSERT_MESSAGE(tag + " should not be null", json != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should be of type Array", JsonType::Array, json->type);

    CPPUNIT_ASSERT_MESSAGE(tag + " should not have any members", json->members.empty());
    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should have correct number of elements", count, json->arrayValue.size());
}

void JsonTest::checkObject(const string &tag, const Json *json, unsigned long count) {
    CPPUNIT_ASSERT_MESSAGE(tag + " should not be null", json != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should be of type Object", JsonType::Object, json->type);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should have correct number of members", count, json->members.size());
    CPPUNIT_ASSERT_MESSAGE(tag + " should not have any elements", json->arrayValue.empty());
}

void JsonTest::checkBoolean(const std::string &tag, const Lib::Json *json, bool value) {
    CPPUNIT_ASSERT_MESSAGE(tag + " should not be null", json != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should be of type Boolean", JsonType::Boolean, json->type);

    CPPUNIT_ASSERT_MESSAGE(tag + " should not have any members", json->members.empty());
    CPPUNIT_ASSERT_MESSAGE(tag + " should not have any elements", json->arrayValue.empty());

    CPPUNIT_ASSERT_EQUAL_MESSAGE(tag + " should have the correct booleanValue", value, json->booleanValue);
}
