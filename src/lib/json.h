#pragma once

#include <string>
#include <vector>

namespace Lib {

class Json {
public:
	Json();
	~Json();

	std::vector<Json*> members;

	void read(const std::string&);
};

}

