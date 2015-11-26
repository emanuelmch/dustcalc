#include "jsonTest.h"

#include "../../src/lib/json.h"

CPPUNIT_TEST_SUITE_REGISTRATION(JsonTest);

using Lib::Json;
using std::string;
using std::vector;

void JsonTest::emptyObject() {
    string content = "{}";

    Json json;
    json.read(content);

    CPPUNIT_ASSERT(json.members.empty());
}
