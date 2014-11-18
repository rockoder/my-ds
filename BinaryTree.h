#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <initializer_list>
#include <queue>
#include <memory>

#include "Node.h"

// Only those algorithms that are unique to binary
// tree (and not to BST) will be implemented here.

template<typename T>
class BinaryTree
{
public:
	explicit BinaryTree()
		: _root(nullptr)
	{	}

	BinaryTree(std::initializer_list<T> il);

	~BinaryTree() = default;

	std::vector<T> inorder() const;
	std::vector<T> postorder() const;
	std::vector<T> preorder() const;

	void displayLevelOrder() const;
	void displayPretty() const;
	void displayAllPaths() const;

	size_t size() const;
	size_t height() const;
	size_t width() const;

	void mirror();

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

	void mirror(std::shared_ptr<Node<T>> root);

	virtual std::shared_ptr<Node<T>> lca(std::shared_ptr<Node<T>> root, 
											const T& data1, const T& data2) const;

protected:
	std::shared_ptr<Node<T>> _root;
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

	inorder(_root, v);

	return v;
}

template<typename T>
std::vector<T> BinaryTree<T>::postorder() const
{
	std::vector<T> v;

	postorder(_root, v);

	return v;
}

template<typename T>
std::vector<T> BinaryTree<T>::preorder() const
{
	std::vector<T> v;

	preorder(_root, v);

	return v;
}

template<typename T>
void BinaryTree<T>::displayLevelOrder() const
{
	std::queue<std::shared_ptr<Node<T>>> q;
	q.push(_root);
	q.push(nullptr);

	levelorder(q);
}

template<typename T>
void BinaryTree<T>::displayPretty() const
{
	std::queue<std::shared_ptr<Node<T>>> q;

	q.push(_root);
	q.push(nullptr);

	displayPretty(q);
}

template<typename T>
void BinaryTree<T>::displayAllPaths() const
{
	std::vector<T> v;
	displayAllPaths(_root, v);
}

template<typename T>
size_t BinaryTree<T>::size() const
{
	return size(_root);
}

template<typename T>
size_t BinaryTree<T>::height() const
{
	return height(_root);
}

template<typename T>
size_t BinaryTree<T>::width() const
{
	return width(_root);
}

template<typename T>
void BinaryTree<T>::mirror()
{
	mirror(_root);
}

template<typename T>
std::shared_ptr<Node<T>> BinaryTree<T>::lca(const T& data1, const T& data2) const
{
	return lca(_root, data1, data2);
}

/////////// Private Member Functions ///////////

template<typename T>
void BinaryTree<T>::insert(const T& data)
{
	if (!_root)
	{
		_root = std::make_shared<Node<T>>(data);
		return;
	}

	std::queue<std::shared_ptr<Node<T>>> q;
	q.push(_root);

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
void BinaryTree<T>::mirror(std::shared_ptr<Node<T>> root)
{
	// 3 parts of recursion:

	// 1. termination condition
	if (!root)
		return;

	// 2. some task to perform
	std::shared_ptr<Node<T>> temp = root->right;
	root->right = root->left;
	root->left = temp;

	// 3. recursion call
	mirror(root->left);
	mirror(root->right);
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