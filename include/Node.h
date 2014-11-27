#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node
{
	T data;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
	
	Node(const T& d) 
		: data(d), left(nullptr), right(nullptr)
	{	}

	~Node() = default;
};

#endif