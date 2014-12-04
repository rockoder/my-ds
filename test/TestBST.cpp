#include <algorithm>

#include "BinarySearchTree.h"
#include "gtest/gtest.h"

using namespace std;

class TestBST : public ::testing::Test
{
protected:

	BinarySearchTree<int> t1{ 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	BinarySearchTree<int> t2;
	BinarySearchTree<int> t3 { 200 };
	BinarySearchTree<int> t4 { 1, 2, 3, 4, 5, 6, 7, 8 };
};

TEST_F(TestBST, MethodWidth)
{
	EXPECT_EQ(6, t1.width());
	EXPECT_EQ(0, t2.width());
	EXPECT_EQ(1, t3.width());
}

TEST_F(TestBST, MethodLCA)
{
	EXPECT_EQ(15, t1.BinaryTree<int>::lca(15, 1)->data);
}

TEST_F(TestBST, MethodToList)
{
	BinarySearchTree<int> m1{ 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	m1.toList();
}

TEST_F(TestBST, MethodIsBalanced)
{
	EXPECT_FALSE(t4.isBalanced());
}
