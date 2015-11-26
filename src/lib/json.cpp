#include "json.h"

using Lib::Json;
using std::string;
using std::vector;

Json::Json() {}

Json::~Json() {
	for (auto it = members.begin(); it != members.end(); ++it) {
		delete (*it);
	}
}

void Json::read(const string&) {}
