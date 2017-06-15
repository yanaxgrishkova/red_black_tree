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
  REQUIRE(rbt._root() == rbt.findElement(3));
  REQUIRE(rbt._color(3) == 1);
  REQUIRE(rbt._color(2) == 0);
  REQUIRE(rbt._color(4) == 0);
  REQUIRE(rbt.findElement(2) != 0);
  REQUIRE(rbt.findElement(3) != 0);
  REQUIRE(rbt.findElement(4) != 0);
}

SCENARIO("insert3")
{
  RedBlackTree<int> rbt;
  rbt.insert(1);
  rbt.insert(2);
  rbt.insert(3);
  rbt.insert(4);
  rbt.insert(5);
  REQUIRE(rbt._root() == rbt.findElement(2));
  REQUIRE(rbt._color(2) == 1);
  REQUIRE(rbt._color(1) == 1);
  REQUIRE(rbt._color(4) == 1);
  REQUIRE(rbt._color(3) == 0);
  REQUIRE(rbt._color(5) == 0);
  REQUIRE(rbt.findElement(1) != 0);
  REQUIRE(rbt.findElement(2) != 0);
  REQUIRE(rbt.findElement(3) != 0);
  REQUIRE(rbt.findElement(4) != 0);
  REQUIRE(rbt.findElement(5) != 0);
}

SCENARIO ("insert4")
{
  RedBlackTree<int> rbt;
  rbt.insert(3);
  rbt.insert(1);
  rbt.insert(2);
  REQUIRE(rbt._root() == rbt.findElement(2));
  REQUIRE(rbt._color(2) == 1);
  REQUIRE(rbt._color(1) == 0);
  REQUIRE(rbt._color(3) == 0);
  REQUIRE(rbt.findElement(1) != 0);
  REQUIRE(rbt.findElement(2) != 0);
  REQUIRE(rbt.findElement(3) != 0);
}

SCENARIO("insert5")
{
  RedBlackTree<int> rbt;
  rbt.insert(3);
  rbt.insert(2);
  rbt.insert(1);
  REQUIRE(rbt._root() == rbt.findElement(2));
  REQUIRE(rbt._color(2) == 1);
  REQUIRE(rbt._color(1) == 0);
  REQUIRE(rbt._color(3) == 0);
  REQUIRE(rbt.findElement(1) != 0);
  REQUIRE(rbt.findElement(2) != 0);
  REQUIRE(rbt.findElement(3) != 0);
}
