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
	std::string *name;
	JsonType type;

	void read(const std::string&);
	Json *getMember(const std::string&);

	std::vector<Json*> arrayValue;

private:
	void readObject(const std::string &);
};

}

