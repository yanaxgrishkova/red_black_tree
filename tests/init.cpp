#include <red_black_tree.hpp>
#include <catch.hpp>

SCENARIO("default constructor") 
{
	BinarySearchTree<int> rbt;
	REQUIRE(rbt._root() == rbt._NIL());
}
