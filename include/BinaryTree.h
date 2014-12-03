#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <initializer_list>
#include <queue>
#include <memory>
#include <iostream>
#include <stack>

#include "Node.h"

template<typename T>
class BinaryTree
{
public:
	explicit BinaryTree()
		: root_(nullptr)
	{	}

	explicit BinaryTree(std::initializer_list<T> il);

	~BinaryTree() = default;

	std::vector<T> inorder() const;
	std::vector<T> postorder() const;
	std::vector<T> preorder() const;

	void displayLevelOrder() const;
	void spiralOrder() const;

	void displayPretty() const;
	void displayAllPaths() const;

	size_t size() const;
	size_t height() const;
	size_t width() const;
	size_t leafCount() const;
	bool isBST() const;
	bool isSumProperty() const;
	void toSumProperty();

	void mirror();

	void toList();

	// Lowest Common Ancestor
	std::shared_ptr<Node<T>> lca(const T& data1, const T& data2) const;

private:
	void insert(const T& data);

	void inorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const;
	void postorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const;
	void preorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const;

	void levelorder(std::queue<std::shared_ptr<Node<T>>>& q) const;
	void displayPretty(std::queue<std::shared_ptr<Node<T>>>& q) const;
	void displayAllPaths(std::shared_ptr<Node<T>> root, std::vector<T> v) const;

	size_t size(std::shared_ptr<Node<T>> root) const;
	size_t height(std::shared_ptr<Node<T>> root) const;
	size_t width(std::shared_ptr<Node<T>> root) const;
	size_t leafCount(std::shared_ptr<Node<T>> root) const;
	bool isBST(std::shared_ptr<Node<T>> root, T min, T max) const;

	bool isSumProperty(std::shared_ptr<Node<T>> root) const;

	void increment(std::shared_ptr<Node<T>> root, const T& diff);
	void toSumProperty(std::shared_ptr<Node<T>> root);

	void mirror(std::shared_ptr<Node<T>> root);

	void join(std::shared_ptr<Node<T>> a, std::shared_ptr<Node<T>> b);
	std::shared_ptr<Node<T>> append(std::shared_ptr<Node<T>> a, std::shared_ptr<Node<T>> b);
	std::shared_ptr<Node<T>> toList(std::shared_ptr<Node<T>> root);

	virtual std::shared_ptr<Node<T>> lca(std::shared_ptr<Node<T>> root, 
											const T& data1, const T& data2) const;

protected:
	std::shared_ptr<Node<T>> root_;
};

template<typename T>
BinaryTree<T>::BinaryTree(std::initializer_list<T> il)
{
	for (const auto& data : il)
	{
		insert(data);
	}
}

template<typename T>
std::vector<T> BinaryTree<T>::inorder() const
{
	std::vector<T> v;

	inorder(root_, v);

	return v;
}

template<typename T>
std::vector<T> BinaryTree<T>::postorder() const
{
	std::vector<T> v;

	postorder(root_, v);

	return v;
}

template<typename T>
std::vector<T> BinaryTree<T>::preorder() const
{
	std::vector<T> v;

	preorder(root_, v);

	return v;
}

template<typename T>
void BinaryTree<T>::displayLevelOrder() const
{
	std::queue<std::shared_ptr<Node<T>>> q;
	q.push(root_);
	q.push(nullptr);

	levelorder(q);
}

template<typename T>
void BinaryTree<T>::spiralOrder() const
{
	if (!root_)
		return;

	std::stack<std::shared_ptr<Node<T>>> s1;
	std::stack<std::shared_ptr<Node<T>>> s2;

	s1.push(root_);

	while (!s1.empty() || !s2.empty())
	{
		while (!s1.empty())
		{
			std::shared_ptr<Node<T>> temp = s1.top();
			s1.pop();

			std::cout << temp->data << " ";

			if (temp->right)
				s2.push(temp->right);

			if (temp->left)
				s2.push(temp->left);
		}

		std::cout << std::endl;

		while (!s2.empty())
		{
			std::shared_ptr<Node<T>> temp = s2.top();
			s2.pop();

			std::cout << temp->data << " ";

			if (temp->left)
				s1.push(temp->left);

			if (temp->right)
				s1.push(temp->right);
		}

		std::cout << std::endl;
	}
}

template<typename T>
void BinaryTree<T>::displayPretty() const
{
	std::queue<std::shared_ptr<Node<T>>> q;

	q.push(root_);
	q.push(nullptr);

	displayPretty(q);
}

template<typename T>
void BinaryTree<T>::displayAllPaths() const
{
	std::vector<T> v;
	displayAllPaths(root_, v);
}

template<typename T>
size_t BinaryTree<T>::size() const
{
	return size(root_);
}

template<typename T>
size_t BinaryTree<T>::height() const
{
	return height(root_);
}

template<typename T>
size_t BinaryTree<T>::width() const
{
	return width(root_);
}

template<typename T>
size_t BinaryTree<T>::leafCount() const
{
	return leafCount(root_);
}

template<typename T>
bool BinaryTree<T>::isBST() const
{
	return isBST(root_, std::numeric_limits<T>::min(), 
						std::numeric_limits<T>::max());
}

template<typename T>
bool BinaryTree<T>::isSumProperty() const
{
	return isSumProperty(root_);
}

template<typename T>
void BinaryTree<T>::toSumProperty()
{
	toSumProperty(root_);
}

template<typename T>
void BinaryTree<T>::mirror()
{
	mirror(root_);
}

template<typename T>
void BinaryTree<T>::toList()
{
	std::shared_ptr<Node<T>> head = toList(root_);
	std::shared_ptr<Node<T>> start = nullptr;

	bool first = true;

	while (head)
	{
		if (first)
		{
			first = false;
			start = head;
		}
		else
		{
			if (start == head)
				break;
		}
		std::cout << head->data << "\t";
		head = head->right;
	}
}

template<typename T>
std::shared_ptr<Node<T>> BinaryTree<T>::lca(const T& data1, const T& data2) const
{
	return lca(root_, data1, data2);
}

/////////// Private Member Functions ///////////

template<typename T>
void BinaryTree<T>::insert(const T& data)
{
	if (!root_)
	{
		root_ = std::make_shared<Node<T>>(data);
		return;
	}

	std::queue<std::shared_ptr<Node<T>>> q;
	q.push(root_);

	while (!q.empty())
	{				
		std::shared_ptr<Node<T>> temp = q.front();
		q.pop();

		if (temp)
		{
			if (!temp->left)
			{
				temp->left = std::make_shared<Node<T>>(data);
				break;
			}
			else
			{
				q.push(temp->left);
			}

			if (!temp->right)
			{
				temp->right = std::make_shared<Node<T>>(data);
				break;
			}
			else
			{
				q.push(temp->right);
			}
		}
	}
}


template<typename T>
void BinaryTree<T>::inorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const
{
	if (root != nullptr)
	{
		inorder(root->left, v);

		v.push_back(root->data);
		
		inorder(root->right, v);
	}
}

template<typename T>
void BinaryTree<T>::postorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const
{
	if (root != nullptr)
	{
		postorder(root->left, v);
		postorder(root->right, v);

		v.push_back(root->data);
	}
}

template<typename T>
void BinaryTree<T>::preorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const
{
	if (root != nullptr)
	{
		v.push_back(root->data);

		preorder(root->left, v);
		preorder(root->right, v);
	}
}

template<typename T>
void BinaryTree<T>::levelorder(std::queue<std::shared_ptr<Node<T>>>& q) const
{
	while (!q.empty())
	{
		std::shared_ptr<Node<T>> temp = q.front();
		q.pop();

		if (temp)
		{
			std::cout << temp->data << "\t";

			if (temp->left)
			{
				q.push(temp->left);
			}

			if (temp->right)
			{
				q.push(temp->right);
			}

			if (!q.front())
			{
				q.pop();
				std::cout << std::endl;
				q.push(nullptr);
			}
		}
	}
}

// TODO: Works only for complete BT. Need to handle other cases.
template<typename T>
void BinaryTree<T>::displayPretty(std::queue<std::shared_ptr<Node<T>>>& q) const
{
	size_t h = 2 * height(q.front());
	size_t level = 1;
	bool firstNode = true;
	char space = '-';

	while (!q.empty())
	{
		std::shared_ptr<Node<T>> temp = q.front();
		q.pop();

		if (temp)
		{
			if (firstNode)
			{
				for (int i = 1; i < h / level; ++i)
				{
					std::cout << space;
				}

				firstNode = false;
				std::cout << temp->data;
			}
			else
			{
				for (int i = 1; i < 2 * (h / level); ++i)
				{
					std::cout << space;
				}

				std::cout << temp->data;
			}

			if (temp->left)
			{
				q.push(temp->left);
			}
			else
			{
				//q.push(std::make_shared<Node<T>>(T{}));
			}

			if (temp->right)
			{
				q.push(temp->right);
			}
			else
			{
				//q.push(std::make_shared<Node<T>>(T{}));
			}

			if (!q.front())
			{
				q.pop();
				std::cout << std::endl;
				q.push(nullptr);

				firstNode = true;
				level *= 2;
			}
		}
	}
}

template<typename T>
void BinaryTree<T>::displayAllPaths(std::shared_ptr<Node<T>> root,
					std::vector<T> v) const
{
	// 4 parts of recursion:

	// 1. termination condition
	if (!root)
	{
		return;
	}

	// 2. some task to perform
	v.push_back(root->data);

	// 3. generate result
	// condition when to generate result can be
	// different from termination condition.
	if (!root->left && !root->right)
	{
		for (const auto& ele : v)
		{
			std::cout << ele << "\t";
		}

		std::cout << std::endl;
		
		return;
	}

	// 4. recursion call(s)
	displayAllPaths(root->left, v);
	displayAllPaths(root->right, v);
}

template<typename T>
size_t BinaryTree<T>::size(std::shared_ptr<Node<T>> root) const
{
	if (root)
	{
		return 1 + size(root->left) + size(root->right);
	}
	else
	{
		return 0;
	}
}

template<typename T>
size_t BinaryTree<T>::height(std::shared_ptr<Node<T>> root) const
{
	if (!root)
	{
		return 0;
	}

	return 1 + std::max(height(root->left), height(root->right));
}

template<typename T>
size_t BinaryTree<T>::width(std::shared_ptr<Node<T>> root) const
{
	if (!root)
	{
		return 0;
	}

	size_t leftHeight = height(root->left);
	size_t rightHeight = height(root->right);

	size_t leftWidth = width(root->left);
	size_t rightWidth = width(root->right);

	return std::max(1 + leftHeight + rightHeight,
		std::max(leftWidth, rightWidth));
}

template<typename T>
size_t BinaryTree<T>::leafCount(std::shared_ptr<Node<T>> root) const
{
	if (!root)
		return 0;

	if (root->left == nullptr && root->right == nullptr)
		return 1;

	return leafCount(root->left) + leafCount(root->right);
}

template<typename T>
bool BinaryTree<T>::isBST(std::shared_ptr<Node<T>> root, T min, T max) const
{
	if (!root)
		return true;

	if (root->data < min || root->data > max)
		return false;

	return isBST(root->left, min, root->data - 1) && 
			isBST(root->right, root->data + 1, max);
}

template<typename T>
bool BinaryTree<T>::isSumProperty(std::shared_ptr<Node<T>> root) const
{
	if (!root)
		return true;

	if (!root->left && !root->right)
		return true;

	T leftValue = {};
	T rightValue = {};

	if (root->left)
		leftValue = root->left->data;

	if (root->right)
		rightValue = root->right->data;

	return (root->data == leftValue + rightValue) &&
			isSumProperty(root->left) &&
			isSumProperty(root->right);
}

template<typename T>
void BinaryTree<T>::increment(std::shared_ptr<Node<T>> root, const T& diff)
{
	if (!root)
		return;

	root->data += diff;

	if (root->left)
		increment(root->left, diff);
	else
		increment(root->right, diff);
}

template<typename T>
void BinaryTree<T>::toSumProperty(std::shared_ptr<Node<T>> root)
{
	if (!root)
		return;

	if (!root->left && !root->right)
		return;

	toSumProperty(root->left);
	toSumProperty(root->right);

	T leftValue = {};
	T rightValue = {};

	if (root->left)
		leftValue = root->left->data;

	if (root->right)
		rightValue = root->right->data;

	T diff = root->data - (leftValue + rightValue);

	if (!diff)
		return;

	if (diff < 0)
		root->data += -diff;

	if (diff > 0)
		increment(root->left, diff);
}

template<typename T>
void BinaryTree<T>::mirror(std::shared_ptr<Node<T>> root)
{
	// 3 parts of recursion:

	// 1. termination condition
	if (!root)
		return;

	// step 3 can be done before step 2.

	// 2. recursion call
	mirror(root->left);
	mirror(root->right);

	// 3. some task to perform
	std::shared_ptr<Node<T>> temp = root->right;
	root->right = root->left;
	root->left = temp;
}

template<typename T>
void BinaryTree<T>::join(std::shared_ptr<Node<T>> a, 
										std::shared_ptr<Node<T>> b)
{
	a->right = b;
	b->left = a;
}

template<typename T>
std::shared_ptr<Node<T>> BinaryTree<T>::append(std::shared_ptr<Node<T>> a, 
										std::shared_ptr<Node<T>> b)
{
	if (!a)
		return b;

	if (!b)
		return a;

	std::shared_ptr<Node<T>> aLast = a->left;
	std::shared_ptr<Node<T>> bLast = b->left;

	join(aLast, b);
	join(bLast, a);

	return a;
}

template<typename T>
std::shared_ptr<Node<T>> BinaryTree<T>::toList(std::shared_ptr<Node<T>> root)
{
	if (!root)
	{
		return nullptr;
	}

	std::shared_ptr<Node<T>> aList = toList(root->left);
	std::shared_ptr<Node<T>> bList = toList(root->right);

	root->left = root;
	root->right = root;

	std::shared_ptr<Node<T>> temp1 = append(aList, root);
	std::shared_ptr<Node<T>> temp2 = append(temp1, bList);

	return temp2;
}

template<typename T>
std::shared_ptr<Node<T>> BinaryTree<T>::lca(std::shared_ptr<Node<T>> root, 
												const T& data1, const T& data2) const
{
	if (!root)
	{
		return nullptr;
	}

	if (root->data == data1 || root->data == data2)
	{
		return root;
	}

	std::shared_ptr<Node<T>> lca1 = lca(root->left, data1, data2);
	std::shared_ptr<Node<T>> lca2 = lca(root->right, data1, data2);

	if (lca1 && lca2)
	{
		return root;
	}

	return lca1 ? lca1 : lca2;
}

#endif