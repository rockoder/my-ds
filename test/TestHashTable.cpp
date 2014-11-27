#include "HashTable.h"
#include "gtest/gtest.h"

using namespace std;

class TestHashTable : public ::testing::Test
{
protected:

	TestHashTable() : h1(10)
	{	}

	HashTable<int, float> h1;
};

TEST_F(TestHashTable, MethodPutGet)
{
	h1.put(1, 1.1f);
	h1.put(2, 2.2f);

	EXPECT_EQ(1.1f, h1.get(1));
	EXPECT_EQ(2.2f, h1.get(2));

	h1.put(2, 3.3f);

	EXPECT_EQ(3.3f, h1.get(2));
}
