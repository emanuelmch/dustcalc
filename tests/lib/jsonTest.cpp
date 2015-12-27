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

	CPPUNIT_ASSERT(json.members.empty());
	CPPUNIT_ASSERT_EQUAL(JsonType::Array, json.type);

	vector<Json*> elements = json.arrayValue;
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Element count should be 4", 4, (int)elements.size());

	Json *stringElement = elements[0];
	CPPUNIT_ASSERT(stringElement != NULL);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Element type should be String", JsonType::String, stringElement->type);
	CPPUNIT_ASSERT_EQUAL(string("one"), *(stringElement->stringValue));

	Json *numberElement = elements[1];
	CPPUNIT_ASSERT(numberElement != NULL);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Element type should be Number", JsonType::Number, numberElement->type);
	CPPUNIT_ASSERT_EQUAL((unsigned long)2, numberElement->numberValue);

	Json *trueElement = elements[2];
	CPPUNIT_ASSERT(trueElement != NULL);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Element type should be Boolean", JsonType::Boolean, trueElement->type);
	CPPUNIT_ASSERT_EQUAL(true, trueElement->booleanValue);

	Json *falseElement = elements[3];
	CPPUNIT_ASSERT(falseElement != NULL);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Element type should be Boolean", JsonType::Boolean, falseElement->type);
	CPPUNIT_ASSERT_EQUAL(false, falseElement->booleanValue);
}

void JsonTest::objectWithArrayWithObjectWithArrayWithObject() {
	const string content = "{\"a\":[222,{\"b\":[{\"c\":123}],\"bb\":\"8\"}]}";

	Json levelOne;
	levelOne.read(content);

	CPPUNIT_ASSERT_EQUAL(JsonType::Object, levelOne.type);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Level One should have one member", (size_t)1, levelOne.members.size());

	Json *levelTwo = levelOne.getMember("a");
	CPPUNIT_ASSERT(levelTwo != NULL);
	CPPUNIT_ASSERT_EQUAL(JsonType::Array, levelTwo->type);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Level Two should have two elements", (size_t)2, levelTwo->arrayValue.size());

	Json *levelThreeValue = levelTwo->arrayValue[0];
	CPPUNIT_ASSERT_EQUAL(JsonType::Number, levelThreeValue->type);
	CPPUNIT_ASSERT_EQUAL((unsigned long)222, levelThreeValue->numberValue);

	Json *levelThreeObject = levelTwo->arrayValue[1];
	CPPUNIT_ASSERT_EQUAL(JsonType::Object, levelThreeObject->type);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Level Three should have two members", (size_t)2, levelThreeObject->members.size());

	Json *levelFourObject = levelThreeObject->getMember("b");
	CPPUNIT_ASSERT(levelFourObject != NULL);
	CPPUNIT_ASSERT_EQUAL(JsonType::Array, levelFourObject->type);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Level Four should have one element", (size_t)1, levelFourObject->arrayValue.size());

	Json *levelFourValue = levelThreeObject->getMember("bb");
	CPPUNIT_ASSERT(levelFourValue != NULL);
	CPPUNIT_ASSERT_EQUAL(JsonType::String, levelFourValue->type);
	CPPUNIT_ASSERT_EQUAL(string("8"), *(levelFourValue->stringValue));

	Json *levelFive = levelFourObject->arrayValue[0];
	CPPUNIT_ASSERT_EQUAL(JsonType::Object, levelFive->type);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Level Five should have one member", (size_t)1, levelFive->members.size());

	Json *levelSix = levelFive->getMember("c");
	CPPUNIT_ASSERT(levelSix != NULL);
	CPPUNIT_ASSERT_EQUAL(JsonType::Number, levelSix->type);
	CPPUNIT_ASSERT_EQUAL((unsigned long)123, levelSix->numberValue);
}
