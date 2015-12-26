#pragma once

#include <string>
#include <vector>

namespace Lib {

enum JsonType {
    Unknown, Object, Array
};

class Json {
public:
	Json();
	~Json();

	std::vector<Json*> members;
	std::string name;
	JsonType type;

	void read(std::string);
	Json *getMember(std::string);

	std::vector<Json*> arrayValue;
};

}

