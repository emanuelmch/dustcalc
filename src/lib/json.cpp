#include "json.h"

#include <algorithm>

using Lib::Json;
using std::string;
using std::vector;

Json::Json() {}

Json::~Json() {
    for_each(members.begin(), members.end(),
        [](Json *member){ delete member;});
}

void Json::read(string) {}
