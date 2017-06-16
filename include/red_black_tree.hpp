#include <iostream>
#include <stdexcept>

const bool BLACK = 1;
const bool RED = 0;

template<typename T> 
struct Node
{
	T value;
	bool color;
	Node* leftNode;
	Node* rightNode;
	Node* parNode;
};

template<typename T> 
class RedBlackTree
{
private:
	Node<T>* root;
	Node<T>* NIL;
public:
	RedBlackTree();
	bool _color(const T& value) const;
	Node<T>* _root() const;
	Node<T>* _NIL() const;
	void left_rotate(Node<T>* currNode);
	void right_rotate(Node<T>* currNode);
	void insertFix(Node<T>* currNode);
	void insert(const T& value);
	void print(const Node<T>* tempNode, int level) const;
	Node<T>* findElement(const T& value) const;
};

template <typename T> 
RedBlackTree<T>::RedBlackTree()
{
	NIL = new Node<T>;
	NIL->leftNode = NIL->parNode = NIL->rightNode = nullptr;
	NIL->color = BLACK;
	root = NIL;
}

template <typename T>
bool RedBlackTree<T>::_color(const T& value) const
{
	return findElement(value)->color;
}

template <typename T>
Node<T>* RedBlackTree<T>::_root() const
{
	return root;
}

template <typename T>
Node<T>* RedBlackTree<T>::_NIL()const
{
	return NIL;
}

template <typename T>
void RedBlackTree<T>::left_rotate(Node<T>* currNode)
{
	Node<T>* tempNode= currNode->rightNode;
	currNode->rightNode = tempNode->leftNode;
	if (tempNode->leftNode != NIL)
		tempNode->leftNode->parNode = currNode;
	if (tempNode!= NIL)
		tempNode->parNode = currNode->parNode;
	if (currNode->parNode != NIL)
	{
		if (currNode == currNode->parNode->leftNode)
			currNode->parNode->leftNode = tempNode;
		else
			currNode->parNode->rightNode = tempNode;
	}
	else
	{
		root = tempNode;
	}
	tempNode->leftNode = currNode;
	if (currNode != NIL)
		currNode->parNode = tempNode;
}

template <typename T>
void RedBlackTree<T>::right_rotate(Node<T> *currNode)
{
	Node<T> *tempNode= currNode->leftNode;
	currNode->leftNode = tempNode->rightNode;
	if (tempNode->rightNode != NIL)
		tempNode->rightNode->parNode = currNode;
	if (tempNode!= NIL)
		tempNode->parNode = currNode->parNode;
	if (currNode->parNode != NIL)
	{
		if (currNode == currNode->parNode->rightNode)
			currNode->parNode->rightNode = tempNode;
		else
			currNode->parNode->leftNode = tempNode;
	}
	else
	{
		root = tempNode;
	}


	tempNode->rightNode = currNode;
	if (currNode != NIL)
		currNode->parNode = tempNode;
}

template <typename T>
void RedBlackTree<T>::insertFix(Node<T>* currNode)
{
	while (currNode != root && currNode->parNode->color == RED)
	{
		if (currNode->parNode == currNode->parNode->parNode->leftNode)
		{
			Node<T>* tempNode= currNode->parNode->parNode->rightNode;
			if (tempNode->color == RED)
			{
				currNode->parNode->color = BLACK;
				tempNode->color = BLACK;
				currNode->parNode->parNode->color = RED;
				currNode = currNode->parNode->parNode;
			}

			else
			{
				if (currNode == currNode->parNode->rightNode)
				{
					currNode = currNode->parNode;
					left_rotate(currNode);
				}
				currNode->parNode->color = BLACK;
				currNode->parNode->parNode->color = RED;
				right_rotate(currNode->parNode->parNode);
			}
		}

		else
		{
			Node<T>* tempNode= currNode->parNode->parNode->leftNode;
			if (tempNode->color == RED)
			{
				currNode->parNode->color = BLACK;
				tempNode->color = BLACK;
				currNode->parNode->parNode->color = RED;
				currNode = currNode->parNode->parNode;
			}
			else
			{
				if (currNode == currNode->parNode->leftNode)
				{
					currNode = currNode->parNode;
					right_rotate(currNode);
				}
				currNode->parNode->color = BLACK;
				currNode->parNode->parNode->color = RED;
				left_rotate(currNode->parNode->parNode);
			}
		}
	}
	root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::insert(const T& value)
{
	if (findElement(value))
	{
		throw std::logic_error("This value is already added!\n");
	}
	Node<T>* child = new Node<T>;
	child->value = value;
	child->color = RED;
	child->leftNode = child->rightNode = child->parNode = NIL;
	Node<T>* parNode = NIL;
	Node<T>* tempNode= root;
	if (root == NIL)
	{
		root = child;
		root->color = BLACK;
		return;
	}
	while (tempNode!= NIL)
	{

		if (child->value == tempNode->value)
			return;

		parNode = tempNode;
		if (value < tempNode->value)
			tempNode= tempNode->leftNode;
		else
			tempNode= tempNode->rightNode;
	}
	if (value < parNode->value)
	{
		parNode->leftNode = child;
	}
	else
	{
		parNode->rightNode = child;

	}
	child->parNode = parNode;
	insertFix(child);
}


template <typename T>
void RedBlackTree<T>::print(const Node<T>* tempNode, int level)const
{
		if (root == NIL)
		{
			throw std::logic_error("Error! The tree is empty!\n");
		}
		if (tempNode!= NIL)
		{
			print(tempNode->leftNode, level + 1);
			for (int i = 0; i < level; i++)
				std::cout << "\t";
			std::cout << "(" << tempNode->color << ")";
			std::cout << tempNode->value << "\n";
			print(tempNode->rightNode, level + 1);
		}
	}

template <typename T>
Node<T>* RedBlackTree<T>::findElement(const T& value) const
{
	Node<T>* currNode = root;
	while (currNode != NIL)
	{
		if (value == currNode->value)
			return currNode;
		else
		{
			if (value < currNode->value)
				currNode = currNode->leftNode;
			else currNode = currNode->rightNode;
		}
	}
	return 0;
}
