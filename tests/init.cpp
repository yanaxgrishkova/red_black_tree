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

SCENARIO("insert2", "[init]")
{
  RedBlackTree<int> rbt;
  rbt.insert(2);
  rbt.insert(3);
  rbt.insert(4);
  REQUIRE(tree._root() == tree.findElement(3));
  REQUIRE(tree._color(3) == 1);
  REQUIRE(tree._color(2) == 0);
  REQUIRE(tree._color(4) == 0);
  REQUIRE(tree.findElement(2) != 0);
  REQUIRE(tree.findElement(3) != 0);
  REQUIRE(tree.findElement(4) != 0);
}
