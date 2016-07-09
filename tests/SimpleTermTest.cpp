#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(SimpleTerm, Basics)
{
    Constant x("x");
    Constant y("y");

    x.setValue(10);
    y.setValue(20);
    
    SimpleTerm left(x);
    SimpleTerm right(y);
    SimpleTerm term(x, OP_MULTIPLY, y);
    
    EXPECT_TRUE(left.leftIsLeaf() && left.rightIsLeaf());
    EXPECT_TRUE(right.leftIsLeaf() && right.rightIsLeaf());
    EXPECT_TRUE(!term.leftIsLeaf() && !term.rightIsLeaf());
}

TEST(SimpleTerm, Implicit)
{
    Constant x("x");
    SimpleTerm term(x, OP_MULTIPLY, SimpleTerm(100, OP_SUBTRACT, 95));
    
    x.setValue(10);
    
    EXPECT_TRUE(!term.leftIsLeaf());
    EXPECT_EQ(term.leftTree()->leftLeaf().value(), 10.0);
}
