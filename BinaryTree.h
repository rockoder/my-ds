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

	size_t size() const;
	size_t height() const;
	size_t width() const;

private:
	void insert(const T& data);

	void inorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const;
	void postorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const;
	void preorder(std::shared_ptr<Node<T>> root, std::vector<T>& v) const;

	void levelorder(std::queue<std::shared_ptr<Node<T>>>& q) const;

	size_t size(std::shared_ptr<Node<T>> root) const;
	size_t height(std::shared_ptr<Node<T>> root) const;
	size_t width(std::shared_ptr<Node<T>> root) const;

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

#endif