#ifndef BinarySearchTree_H
#define BinarySearchTree_H

#include <queue>
#include <stack>
#include <memory>
#include <sstream>

#include "BinaryTree.h"

template<typename T>
class BinarySearchTree : public BinaryTree<T>
{
	using BinaryTree<T>::_root;

public:
	explicit BinarySearchTree() :
		BinaryTree<T>()
	{	}

	BinarySearchTree(std::initializer_list<T> il);
	BinarySearchTree(std::vector<T> v);

	BinarySearchTree(const BinarySearchTree& t) = delete;
	BinarySearchTree& operator=(const BinarySearchTree& t) = delete;

	~BinarySearchTree() = default;

	void serialize(std::ostream& preorderStream) const;
	void deserialize(std::istream& preorderStream);

	T min() const;
	T max() const;

private:
	void insert(std::shared_ptr<Node<T>>& root, const T& data);

	T min(std::shared_ptr<Node<T>> root) const;
	T max(std::shared_ptr<Node<T>> root) const;

private:

	// friends. good idea to list them at the start or end of the class. 
	// i am avoiding at the start because start is used for ctors.
	// TODO: remove definition of these functions outside the class.
	// access specifier does not have any effect on friend functions.
	// hence they can be private.
	// http://publib.boulder.ibm.com/infocenter/lnxpcomp/v7v91/index.jsp?topic=/com.ibm.vacpp7l.doc/language/ref/clrc16friends_and_templates.htm

	friend bool operator==(const BinarySearchTree<T>& lhs, const BinarySearchTree<T>& rhs)
	{
		std::vector<T> v1 = lhs.postorder();
		std::vector<T> v2 = rhs.postorder();

		return v1 == v2;
	}

	friend bool operator!=(const BinarySearchTree<T>& lhs, const BinarySearchTree<T>& rhs)
	{
		return !(lhs == rhs);
	}
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(std::initializer_list<T> il)
	: BinarySearchTree(std::vector<T>(il))
{	}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(std::vector<T> v)
	: BinaryTree<T>()
{
	for (const auto& i : v)
	{
		insert(_root, i);
	}
}

template<typename T>
void BinarySearchTree<T>::serialize(std::ostream& out) const
{
	// TODO: find consistent way to make base template name dependent.
	// Note: This wont work - using BinaryTree<T>::preorder;
	std::vector<T> v = this->preorder();

	// TODO const_reference here is not working in g++.
	//for_each(v.begin(), v.end(), [&out](std::vector<T>::const_reference e){ out << e << " "; });

	for (const auto& i : v)
	{
		out << i << " ";
	}
}

template<typename T>
void BinarySearchTree<T>::deserialize(std::istream& preorderStream)
{
	T ele;
	std::vector<T> preorderVector;

	while (preorderStream >> ele)
	{
		preorderVector.push_back(ele);
	}

	preorderStream.clear();

	if (!preorderVector.empty())
	{
		std::stack<std::shared_ptr<Node<T>>> s;

		std::shared_ptr<Node<T>> root = std::shared_ptr<Node<T>>(std::make_shared<Node<T>>(preorderVector[0]));

		s.push(root);
		_root = root;

		for (size_t i = 1; i < preorderVector.size(); ++i)
		{
			std::shared_ptr<Node<T>> temp;

			while (!s.empty() && preorderVector[i] > s.top()->data)
			{
				temp = s.top();
				s.pop();
			}

			if (temp)
			{
				temp->right = std::shared_ptr<Node<T>>(std::make_shared<Node<T>>(preorderVector[i]));
				s.push(temp->right);
			}
			else
			{
				s.top()->left = std::shared_ptr<Node<T>>(std::make_shared<Node<T>>(preorderVector[i]));
				s.push(s.top()->left);
			}
		}
	}
}

template<typename T>
T BinarySearchTree<T>::min() const
{
	return min(_root);
}

template<typename T>
T BinarySearchTree<T>::max() const
{
	return max(_root);
}

template<typename T>
void BinarySearchTree<T>::insert(std::shared_ptr<Node<T>>& root, const T& data)
{
	if (!root)
	{
		root = std::shared_ptr<Node<T>>(std::make_shared<Node<T>>(data));
	}
	else if (data < root->data)
	{
		insert(root->left, data);
	}
	else
	{
		insert(root->right, data);
	}
}

template<typename T>
T BinarySearchTree<T>::min(std::shared_ptr<Node<T>> root) const
{
	while (root->left != nullptr)
	{
		root = root->left;
	}

	return root->data;
}

template<typename T>
T BinarySearchTree<T>::max(std::shared_ptr<Node<T>> root) const
{
	while (root->right != nullptr)
	{
		root = root->right;
	}

	return root->data;
}

#endif