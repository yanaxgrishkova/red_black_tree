#include <binary_search_tree.hpp>
#include <catch.hpp>

SCENARIO("default constructor") 
{
	BinarySearchTree<int> bst;
	REQUIRE(bst.root() == nullptr);
}

SCENARIO("insertElement")
{
	BinarySearchTree<int> bst;
	bst.insert(7);
	REQUIRE(bst.value_() == 7);
	REQUIRE(bst.leftNode_() == nullptr);
	REQUIRE(bst.rightNode_() == nullptr);
}

SCENARIO("findElement")
{
	BinarySearchTree<int> bst;
	bst.insert(7);
	REQUIRE(bst.isFound(7) == 1);
}

SCENARIO("infile")
{
	BinarySearchTree<int> bst;
	bst.infile("file.txt");
	REQUIRE(bst.count_(bst.root()) == 0);
}

SCENARIO("count_")
{
	BinarySearchTree<int> bst;
	int count = 0;
	bst.insert(7);
	count = bst.count_(bst.root ());
	REQUIRE(count == 1);
}

SCENARIO("deleteNode")
{
	BinarySearchTree<int> bst;
	int size1, size2, size3, size4;
	bst.insert(5);
	bst.insert(3);
	bst.insert(2);
	bst.insert(4);
	bst.insert(7);
	bst.insert(6);
	bst.insert(8);
	size1 = bst.count_(bst.root ());
	bst.deleteNode(8);
	size2 = bst.count_(bst.root ());
	bst.deleteNode(7);
	size3 = bst.count_(bst.root ());
	bst.deleteNode(3);
	size4 = bst.count_(bst.root ());
	REQUIRE(size1 == 7);
	REQUIRE(size2 == 6);
	REQUIRE(size3 == 5);
	REQUIRE(size4 == 4);
}
