#pragma once

#include <string>
#include <vector>

namespace Lib {

enum JsonType {
	Unknown, String, Number, Object, Array, Boolean
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
	std::string *stringValue;
	unsigned long numberValue;
	bool booleanValue;

private:
	void readObject(const std::string &);
};

}

