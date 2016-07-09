#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(SimpleTerm, Basics) {

    Constant x("x");
    Constant y("y");

    x.setValue(10);
    y.setValue(20);
    
    SimpleTerm leaf(x);
    SimpleTerm tree(leaf, SimpleTerm::RelationalOperator::multiply, y);
    SimpleTerm root(tree, SimpleTerm::RelationalOperator::multiply, y);
    
    EXPECT_TRUE(leaf.isLeaf());
    
    EXPECT_TRUE(!tree.isLeaf());
    EXPECT_TRUE(tree.tree()->isLeaf());
    
    EXPECT_TRUE(!root.isLeaf());
    EXPECT_TRUE(!root.tree()->isLeaf());
    EXPECT_TRUE(root.tree()->tree()->isLeaf());
    
    EXPECT_EQ(leaf.leaf().value(), 10);
    EXPECT_EQ(tree.tree()->leaf().value(), 10);
    EXPECT_EQ(tree.leaf().value(), 20);
    EXPECT_EQ(root.tree()->tree()->leaf().value(), 10);
    EXPECT_EQ(root.tree()->leaf().value(), 20);
    EXPECT_EQ(root.leaf().value(), 20);
    
    x.setValue(30);
    y.setValue(40);
    
    EXPECT_EQ(leaf.leaf().value(), 30);
    EXPECT_EQ(tree.tree()->leaf().value(), 30);
    EXPECT_EQ(tree.leaf().value(), 40);
    EXPECT_EQ(root.tree()->tree()->leaf().value(), 30);
    EXPECT_EQ(root.tree()->leaf().value(), 40);
    EXPECT_EQ(root.leaf().value(), 40);
}