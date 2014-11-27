#include "BinaryTree.h"
#include "gtest/gtest.h"

using namespace std;

class TestBT : public ::testing::Test
{
protected:

	BinaryTree<int> t1{ 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	BinaryTree<int> t2;
	BinaryTree<int> t3 { 200 };
};

TEST_F(TestBT, MethodWidth)
{
	EXPECT_EQ(6, t1.width());
	EXPECT_EQ(0, t2.width());
	EXPECT_EQ(1, t3.width());
}

TEST_F(TestBT, MethodLCA)
{
	EXPECT_EQ(50, t1.BinaryTree<int>::lca(15, 1)->data);
}
