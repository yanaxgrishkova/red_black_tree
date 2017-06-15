#include <red_black_tree.hpp>
#include <catch.hpp>

SCENARIO("default constructor") 
{
	RedBlackTree<int> rbt;
	REQUIRE(rbt._root() == rbt._NIL());
}

SCENARIO("insert")
{
  RedBlackTree<int> rbt;
  rbt.insert(5);
  REQUIRE(rbt.findElement(5) != 0);
}
