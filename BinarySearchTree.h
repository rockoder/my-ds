#ifndef BinarySearchTree_H
#define BinarySearchTree_H

#include <queue>
#include <stack>
#include <memory>
#include <sstream>

template<typename T>
class BinarySearchTree
{
	// Forward declaration
	struct Node;

public:
	explicit BinarySearchTree() :
		_root(nullptr)
	{	}

	BinarySearchTree(std::initializer_list<T> il);
	BinarySearchTree(std::vector<T> v);

	BinarySearchTree(const BinarySearchTree& t) = delete;
	BinarySearchTree& operator=(const BinarySearchTree& t) = delete;

	~BinarySearchTree() = default;

	std::vector<T> inorder() const;
	std::vector<T> postorder() const;
	std::vector<T> preorder() const;

	void displayLevelOrder() const;

	void serialize(std::ostream& preorderStream) const;
	void deserialize(std::istream& preorderStream);

	T min() const;
	T max() const;
	size_t size() const;
	size_t height() const;
	size_t width() const;

private:
	void insert(std::shared_ptr<Node>& root, const T& data);

	void inorder(std::shared_ptr<Node> root, std::vector<T>& v) const;
	void postorder(std::shared_ptr<Node> root, std::vector<T>& v) const;
	void preorder(std::shared_ptr<Node> root, std::vector<T>& v) const;

	void levelorder(std::queue<std::shared_ptr<Node>>& q) const;

	T min(std::shared_ptr<Node> root) const;
	T max(std::shared_ptr<Node> root) const;
	size_t size(std::shared_ptr<Node> root) const;
	size_t height(std::shared_ptr<Node> root) const;
	size_t width(std::shared_ptr<Node> root) const;

private:
	struct Node
	{
		T data;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;

		Node(T d) :
			data(d), left(nullptr), right(nullptr)
		{	}

		~Node() = default;
	};

	std::shared_ptr<Node> _root;

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
	: _root(nullptr)
{
	for (const auto& i : v)
	{
		insert(_root, i);
	}
}

template<typename T>
std::vector<T> BinarySearchTree<T>::inorder() const
{
	std::vector<T> v;

	inorder(_root, v);

	return v;
}

template<typename T>
std::vector<T> BinarySearchTree<T>::postorder() const
{
	std::vector<T> v;

	postorder(_root, v);

	return v;
}

template<typename T>
std::vector<T> BinarySearchTree<T>::preorder() const
{
	std::vector<T> v;

	preorder(_root, v);

	return v;
}

template<typename T>
void BinarySearchTree<T>::displayLevelOrder() const
{
	std::queue<std::shared_ptr<Node>> q;
	q.push(_root);
	q.push(nullptr);

	levelorder(q);
}

template<typename T>
void BinarySearchTree<T>::serialize(std::ostream& out) const
{
	std::vector<T> v = preorder();

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
		std::stack<std::shared_ptr<Node>> s;

		std::shared_ptr<Node> root = std::shared_ptr<Node>(std::make_shared<Node>(preorderVector[0]));

		s.push(root);
		_root = root;

		for (size_t i = 1; i < preorderVector.size(); ++i)
		{
			std::shared_ptr<Node> temp;

			while (!s.empty() && preorderVector[i] > s.top()->data)
			{
				temp = s.top();
				s.pop();
			}

			if (temp)
			{
				temp->right = std::shared_ptr<Node>(std::make_shared<Node>(preorderVector[i]));
				s.push(temp->right);
			}
			else
			{
				s.top()->left = std::shared_ptr<Node>(std::make_shared<Node>(preorderVector[i]));
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
size_t BinarySearchTree<T>::size() const
{
	return size(_root);
}

template<typename T>
size_t BinarySearchTree<T>::height() const
{
	return height(_root);
}

template<typename T>
size_t BinarySearchTree<T>::width() const
{
	return width(_root);
}

template<typename T>
void BinarySearchTree<T>::insert(std::shared_ptr<Node>& root, const T& data)
{
	if (!root)
	{
		root = std::shared_ptr<Node>(std::make_shared<Node>(data));
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
void BinarySearchTree<T>::inorder(std::shared_ptr<Node> root, std::vector<T>& v) const
{
	if (root != nullptr)
	{
		inorder(root->left, v);

		v.push_back(root->data);
		
		inorder(root->right, v);
	}
}

template<typename T>
void BinarySearchTree<T>::postorder(std::shared_ptr<Node> root, std::vector<T>& v) const
{
	if (root != nullptr)
	{
		postorder(root->left, v);
		postorder(root->right, v);

		v.push_back(root->data);
	}
}

template<typename T>
void BinarySearchTree<T>::preorder(std::shared_ptr<Node> root, std::vector<T>& v) const
{
	if (root != nullptr)
	{
		v.push_back(root->data);

		preorder(root->left, v);
		preorder(root->right, v);
	}
}

template<typename T>
void BinarySearchTree<T>::levelorder(std::queue<std::shared_ptr<Node>>& q) const
{
	while (!q.empty())
	{
		std::shared_ptr<Node> temp = q.front();
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
T BinarySearchTree<T>::min(std::shared_ptr<Node> root) const
{
	while (root->left != nullptr)
	{
		root = root->left;
	}

	return root->data;
}

template<typename T>
T BinarySearchTree<T>::max(std::shared_ptr<Node> root) const
{
	while (root->right != nullptr)
	{
		root = root->right;
	}

	return root->data;
}

template<typename T>
size_t BinarySearchTree<T>::size(std::shared_ptr<Node> root) const
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
size_t BinarySearchTree<T>::height(std::shared_ptr<Node> root) const
{
	if (!root)
	{
		return 0;
	}

	return 1 + std::max(height(root->left), height(root->right));
}

template<typename T>
size_t BinarySearchTree<T>::width(std::shared_ptr<Node> root) const
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