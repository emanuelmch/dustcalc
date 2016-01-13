#include "json.h"

#include "parseHelpers.h"

#include <cassert>

using Lib::Json;
using std::size_t;
using std::string;
using std::vector;

Json::Json() : name(NULL), type(Unknown), stringValue(NULL) {}

Json::~Json() {
	for (auto it = members.begin(); it != members.end(); ++it) {
		delete (*it);
	}

	for (auto it = arrayValue.begin(); it != arrayValue.end(); ++it) {
		delete (*it);
	}

	if (name != NULL) {
		delete name;
	}

	if (stringValue != NULL) {
		delete stringValue;
	}
}

void Json::read(const string &content) {
	char firstChar = content[0];
	if (firstChar == '{') {
		this->type = JsonType::Object;
		this->readObject(content);
	} else if (firstChar == '[') {
		this->type = JsonType::Array;
		this->readArray(content);
	} else if (firstChar == '"') {
		this->type = JsonType::String;
		this->stringValue = getInsideChunk(content);
		// Now "un-escape" the quote characters
		size_t index = stringValue->find("\\\"");
		while (index != string::npos) {
			stringValue->replace(index, 2, "\"");
			index = stringValue->find("\\\"", index);
		}
	} else if (isNumber(firstChar)) {
		this->type = JsonType::Number;
		this->numberValue = stringToUnsignedLong(content);
	} else if (content == "true") {
		this->type = JsonType::Boolean;
		this->booleanValue = true;
	} else if (content == "false") {
		this->type = JsonType::Boolean;
		this->booleanValue = false;
	}
}

void Json::readObject(const string &content) {
	// Remove the enclosing {}
	auto innerContentPtr = getInsideChunk(content);
	string innerContent = *innerContentPtr;
	delete innerContentPtr;
	assert(innerContent.length() == content.length() - 2);

	size_t previousIndex = 0;
	size_t index = 0;
	size_t length = innerContent.length();

	while (previousIndex < length && index != string::npos) {
		index = innerContent.find(':', previousIndex);
		if (index == string::npos) break;

		string memberName = innerContent.substr(previousIndex, index - previousIndex);
		previousIndex = index + 1;

		index = findEnclosingIndex(innerContent, previousIndex) + 1;

		string memberContent = innerContent.substr(previousIndex, index - previousIndex);
		previousIndex = index + 1;

		Json *member = new Json();
		member->name = getInsideChunk(memberName);
		member->read(memberContent);
		this->members.push_back(member);
	}
}

void Json::readArray(const string &content) {
	// Remove the enclosing []
	auto innerContentPtr = getInsideChunk(content);
	string innerContent = *innerContentPtr;
	delete innerContentPtr;

	assert(innerContent.length() == content.length() - 2);

	size_t previousIndex = 0;
	size_t index = 0;
	size_t length = innerContent.length();

	while (previousIndex < length && index != string::npos) {
		char nextChar = innerContent.at(previousIndex);
		if (nextChar == ']') break;

		if (nextChar == '{' || nextChar == '[') {
			index = findEnclosingIndex(innerContent, previousIndex) + 1;
		} else {
			index = innerContent.find(',', previousIndex);
		}

		string nextElement = innerContent.substr(previousIndex, index - previousIndex);
		previousIndex = index + 1;

		Json *element = new Json();
		element->read(nextElement);
		if (element->type == JsonType::Unknown) {
			delete element;
		} else {
			this->arrayValue.push_back(element);
		}
	}
}

Json *Json::getMember(const string &name) {
	for (auto it = members.begin(); it != members.end(); it++) {
		Json *member = *it;
		if (*(member->name) == name) {
			return member;
		}
	}

	return NULL;
}

