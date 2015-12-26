#include "json.h"

#include "parseHelpers.h"

#include <algorithm>

using Lib::Json;
using std::string;
using std::vector;

Json::Json() : name(NULL), type(Unknown), stringValue(NULL) {}

Json::~Json() {
    for_each(members.begin(), members.end(),
        [](Json *member){ delete member;});
    for_each(arrayValue.begin(), arrayValue.end(),
        [](Json *element){ delete element;});

	if (name != NULL) {
		delete name;
		name = NULL;
	}

	if (stringValue != NULL) {
        delete stringValue;
        stringValue = NULL;
	}
}

void Json::read(const string &content) {
    //TODO: We assume it's a valid json, should we care about malformed documents?
    //TODO: We don't handle leading/trailing spaces...
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
        this->numberValue = std::stoul(content);
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

