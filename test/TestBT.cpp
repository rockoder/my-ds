#include <algorithm>

#include "BinaryTree.h"
#include "gtest/gtest.h"

using namespace std;

class TestBT : public ::testing::Test
{
protected:

	BinaryTree<int> t1{ 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	BinaryTree<int> t2;
	BinaryTree<int> t3 { 200 };
	BinaryTree<int> t4 { 1, 2, 3, 4, 5, 6, 7 };
	BinaryTree<int> t5 { 5, 3, 7, 1, 4, 6, 8 };
	BinaryTree<int> t6 { 12, 3, 9, 1, 2, 4, 5 };
	BinaryTree<int> t7 { 50, 140, -90, 139, 1, 40, 80, 274,	95 };
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

TEST_F(TestBT, MethodMirror)
{
	BinaryTree<int> m1{ 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	vector<int> v1 = m1.inorder();

	m1.mirror();

	vector<int> v2 = m1.inorder();
	reverse(v2.begin(), v2.end());

	EXPECT_EQ(v1, v2);
}

TEST_F(TestBT, MethodToList)
{
	BinaryTree<int> m1{ 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	m1.toList();
}

TEST_F(TestBT, MethodLeafCount)
{
	EXPECT_EQ(5, t1.leafCount());
	EXPECT_EQ(0, t2.leafCount());
	EXPECT_EQ(1, t3.leafCount());
	EXPECT_EQ(4, t4.leafCount());
}

TEST_F(TestBT, MethodIsBST)
{
	EXPECT_FALSE(t1.isBST());
	EXPECT_TRUE(t2.isBST());
	EXPECT_TRUE(t3.isBST());
	EXPECT_FALSE(t4.isBST());
	EXPECT_TRUE(t5.isBST());
}

TEST_F(TestBT, MethodSpiralOrder)
{
	t1.spiralOrder();
	t2.spiralOrder();
}

TEST_F(TestBT, MethodIsSumProperty)
{
	EXPECT_FALSE(t1.isSumProperty());
	EXPECT_TRUE(t6.isSumProperty());
	t7.displayLevelOrder();
	EXPECT_FALSE(t7.isSumProperty());
}

TEST_F(TestBT, MethodToSumProperty)
{
	BinaryTree<int> tree { 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	tree.toSumProperty();
	tree.displayLevelOrder();
	EXPECT_TRUE(tree.isSumProperty());
}

TEST_F(TestBT, MethodIsBalanced)
{
	BinaryTree<int> tree { 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	EXPECT_TRUE(tree.isBalanced());
}

TEST_F(TestBT, MethodInorderWithoutRecursion)
{
	BinaryTree<int> m1{ 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	vector<int> v1 = m1.inorder();
	vector<int> v2 = m1.inorderWithoutRecursion();

	EXPECT_EQ(v1, v2);
}

TEST_F(TestBT, MethodInorderMorris)
{
	BinaryTree<int> m1{ 50, 25, 15, 35, 1, 40, 80, 55, 95 };
	vector<int> v1 = m1.inorder();
	vector<int> v2 = m1.inorderMorris();

	EXPECT_EQ(v1, v2);

	BinaryTree<int> m2;
	EXPECT_EQ(t2.inorder(), m2.inorderMorris());
}

TEST_F(TestBT, MethodCreateTree)
{
	std::initializer_list<int> in{ 55, 35, 95, 25, 1, 50, 40, 15, 80 };
	std::initializer_list<int> pre{ 50, 25, 35, 55, 95, 1, 15, 40, 80 };

	BinaryTree<int> m1(in, pre);
	BinaryTree<int> m2 { 50, 25, 15, 35, 1, 40, 80, 55, 95 };

	vector<int> v1 = m1.inorder();
	vector<int> v2 = m2.inorder();

	EXPECT_EQ(v1, v2);
}