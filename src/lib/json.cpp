#include "json.h"

#include "parseHelpers.h"

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
	size_t previousIndex = 1;
	// We start the search at 2 so we don't run into {}
	size_t index = content.find_first_of(",}", 2);

	while (index != string::npos) {
		string nextMember = content.substr(previousIndex, index - previousIndex);

		string memberName;
		string memberContent;

		splitString(nextMember, ':', &memberName, &memberContent);

		Json *member = new Json();
		member->name = getInsideChunk(memberName);
		member->read(memberContent);
		this->members.push_back(member);

		previousIndex = index + 1;
		index = content.find_first_of(",}", index + 1);
	}
}

void Json::readArray(const string &content) {
	size_t previousIndex = 1;
	// We start the search at 2 so we don't run into []
	size_t index = content.find_first_of(",]", 2);

	while (index != string::npos) {
		string nextElement = content.substr(previousIndex, index - previousIndex);

		Json *element = new Json();
		element->read(nextElement);
		if (element->type == JsonType::Unknown) {
			delete element;
		} else {
			this->arrayValue.push_back(element);
		}

		previousIndex = index + 1;
		index = content.find_first_of(",]", index + 1);
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

