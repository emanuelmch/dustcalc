#include "libraryTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LibraryTest);

using Data::Library;
using Data::CardSet;
using std::string;

void LibraryTest::oneCommonCard() {
	const string json = "[{\"rarity\":\"COMMON\",\"set\":\"TGT\"}]";
	Library library;
	library.fromJson(json);

	CPPUNIT_ASSERT_EQUAL((size_t)1, library.cardSets.size());

	CardSet *cardSet = library.cardSets[0];
	CPPUNIT_ASSERT(cardSet != NULL);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, cardSet->commonCount);
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, cardSet->rareCount);
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, cardSet->epicCount);
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, cardSet->legendaryCount);
}
