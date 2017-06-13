#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

template <typename T>
struct Node
{
	Node<T>* leftNode;
	Node<T>* rightNode;
	T value;

	Node(T value)
	{
		this->value = value;
		leftNode = nullptr;
		rightNode = nullptr;
	}
};

template <typename T>
class BinarySearchTree
{
private:
	Node<T>* _root;
	void destroyTree(Node<T>* node);
	void insertElement(Node<T>* &node, const T &value);
	Node<T>* findPrev(Node<T>* &node, const T& value);
	Node<T>* findElement(const T& value) const;

public:
	BinarySearchTree();
	~BinarySearchTree();

	T value_() const;
	int count_(const Node<T>* node) const;

	Node<T>* leftNode_() const;
	Node<T>* rightNode_() const;
	Node<T>* root() const;

	void insert(const T& value);
	bool isFound(const T& value) const;

	Node<T>* findPrev(const T& value);

	std::ifstream& infile(std::string filename);
	std::ostream& outfile(Node<T>* root, std::ostream& outfile) const;
	void out(std::string filename) const;
	void paintTree(const Node<T>* node, int level) const;
	void deleteNode(const T& value);
	
	friend std::ifstream& operator>> (std::ifstream& infile, BinarySearchTree<T>& node);
	friend std::ostream& operator<< (std::ostream& outfile, BinarySearchTree<T>& node);
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	_root = nullptr;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	destroyTree(_root);
}

template <typename T>
void BinarySearchTree<T>::destroyTree(Node<T>* node)
{
	if (!node)
		return;

	destroyTree(node->leftNode);
	destroyTree(node->rightNode);

	delete node;
}

template <typename T>
T BinarySearchTree<T>::value_() const
{
	return _root->value;
}

template <typename T>
int BinarySearchTree<T>::count_(const Node<T>* node) const
{
	if (!node)
		return 0;

	else
		return count_(node->leftNode) + count_(node->rightNode) + 1;
}

template <typename T>
Node<T>* BinarySearchTree<T>::root() const
{
	return _root;
}

template <typename T>
Node<T>* BinarySearchTree<T>::leftNode_() const
{
	return _root->leftNode;
}

template <typename T>
Node<T>* BinarySearchTree<T>::rightNode_() const
{
	return _root->rightNode;
}

template <typename T>
void BinarySearchTree<T>::insertElement(Node<T>* &node, const T &value)
{
	if (node)
	{
		if (value == node->value)
			throw std::logic_error("This is current element!\n");
		if (value < node->value)
			insertElement(node->leftNode, value);
		else if (value > node->value)
			insertElement(node->rightNode, value);
	}
	else node = new Node<T>(value);
}

template <typename T>
void BinarySearchTree<T>::insert(const T& value)
{
	insertElement(_root, value);
}

template <typename T>
Node<T>*  BinarySearchTree<T>::findElement(const T& value) const
{
	Node<T> *currNode = _root;

	while (currNode)
	{
		if (currNode->value == value)
			break;
		else
		{
			if (currNode->value < value)
				currNode = currNode->rightNode;
			else
				currNode = currNode->leftNode;
		}
	}
	return currNode;
}

template <typename T>
bool BinarySearchTree<T>::isFound(const T& value) const
{
	Node<T> *retNode = findElement(value);
	if (retNode)
		return true;
	else
		return false;
}

template <typename T>
std::ifstream& BinarySearchTree<T>::infile(std::string filename)
{
	std::ifstream inf;
	inf.open(filename);
	if (!inf)
		throw std::logic_error("The file isn't find");
	T value;
	int count;
	inf >> count;
	while (count--)
	{
		inf >> value;
		insert(value);
	}
	inf.close();
	
	return inf;
}

template <typename T>
std::ifstream& operator>> (std::string filename, BinarySearchTree<T>& node)
{
	return node.infile(filename);
} 

template <typename T>
void BinarySearchTree<T>::out(std::string filename) const
{
	std::ofstream ofile(filename);
	if (!ofile)
		throw std::logic_error("The file isn't find\n");
	int count = count_(_root);
	if (count == 0)
		throw std::logic_error("The tree is empty\n");
		ofile << count << " ";
	outfile(_root, ofile);
	ofile.close();
}

template <typename T>
std::ostream& BinarySearchTree<T>::outfile(Node<T>* root, std::ostream& ofile) const
{
	if (!root)
		throw std::logic_error("Binary Search Tree is empty!\n");
	else
	{
		ofile << root->value << " ";
		outfile(root->rightNode, ofile);
		outfile(root->leftNode, ofile);
	}
	
	return ofile;
}

template <typename T>
std::ostream& operator<< (std::ostream& outfile, BinarySearchTree<T>& node)
{
	return node.outfile(outfile);
}

template <typename T>
void BinarySearchTree<T>::paintTree(const Node<T>* node, int level) const
{
	if (node)
	{
		paintTree(node->rightNode, level++);
		for (int i = 0; i < level; i++)
		{
			std::cout << "-";
		}
		std::cout << node->value << std::endl;
		paintTree(node->leftNode, level++);
	}
}

template <typename T>
void BinarySearchTree<T>::deleteNode(const T& value)
{
	if (isFound(value) == false)
		throw std::logic_error("This element is not found in BST!\n");
	Node<T> *currNode = findElement(value);
	Node<T> *parentNode = findPrev(value);

	if (currNode->leftNode == nullptr && currNode->rightNode == nullptr)
	{
		if (parentNode->leftNode == currNode)
			parentNode->leftNode = nullptr;
		if (parentNode->rightNode == currNode)
			parentNode->rightNode = nullptr;
		currNode = nullptr;
	}

	else if (currNode->rightNode == nullptr)
	{
		if (parentNode->leftNode == currNode)
			parentNode->leftNode = currNode->leftNode;
		if (parentNode->rightNode == currNode)
			parentNode->rightNode = currNode->leftNode;
		currNode = nullptr;
	}

	else
	{
		Node <T>* minNode = currNode->rightNode;
		while (minNode->leftNode)
			minNode = minNode->leftNode;
		T val = minNode->value;
		deleteNode(minNode->value);
		currNode->value = val;
	}
}

template <typename T>
Node<T>* BinarySearchTree<T>::findPrev(Node<T>* &node, const T &value)
{
	Node<T>* currNode = node;

	if (isFound(value))
	{
		if (value < currNode->value)
			if (value == currNode->leftNode->value)
				return currNode;
			else
				return findPrev(currNode->leftNode, value);
		else if (value > currNode->value)
			if (value == currNode->rightNode->value)
				return currNode;
			else
				return findPrev(currNode->rightNode, value);
		else return nullptr;
	}

	else return nullptr;
}

template <typename T>
Node<T>* BinarySearchTree<T>::findPrev(const T& value)
{
	return findPrev(_root, value);
}
