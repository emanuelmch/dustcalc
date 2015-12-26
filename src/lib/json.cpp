#include "json.h"

#include "parseHelpers.h"

using Lib::Json;
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
	// We don't actually care about the '{' anymore
	int index = 1;

	while (content[index] == '\"') {
		int endIndex;
		std::string *memberName = getInsideChunk(content, index, &endIndex);
		index = endIndex + 3; // Let's bypass the closing " and the upcoming : as well

		string *memberContent = getOutsideChunk(content, index, &endIndex);
		index = endIndex +1;

		Json *member = new Json();
		member->name = memberName;
		member->read(*memberContent);
		this->members.push_back(member);

		delete memberContent;
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

