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
	//vector<int> v1 = 
	m1.toList();

	// m1.mirror();

	// vector<int> v2 = m1.inorder();
	// reverse(v2.begin(), v2.end());

	// EXPECT_EQ(v1, v2);
}
