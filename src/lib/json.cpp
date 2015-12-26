#include "json.h"

#include "parseHelpers.h"

using Lib::Json;
using std::string;
using std::vector;

Json::Json() : name(NULL), type(Unknown) {}

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
}

void Json::read(const string &content) {
	char firstChar = content[0];
	if (firstChar == '{') {
		this->type = JsonType::Object;
		this->readObject(content);
	} else if (firstChar == '[') {
		this->type = JsonType::Array;
	}
}

static string *readName(const string &content, const int index, int *endIndex) {
	if (content[index] == '\"') {
		return getInsideChunk(content, index, endIndex);
	} else {
		return NULL;
	}
}

void Json::readObject(const string &content) {
	// We don't actually care about the '{' anymore
	int index = 1;

	std::string *memberName;
	int endIndex;
	while ((memberName = readName(content, index, &endIndex))) {
		index = endIndex + 3; // Let's bypass the closing " and the upcoming : as well

		string *memberContent = getOutsideChunk(content, index, &endIndex);
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

