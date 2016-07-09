#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Expression, Basics) {

    Variable v("v");
    
    Constant x("x");
    Constant y("y");

    x.setValue(10);
    y.setValue(20);
    
    SimpleTerm leaf(x);
    SimpleTerm tree(leaf, SimpleTerm::RelationalOperator::multiply, y);
    
    Term term(v, tree);
    
    Expression expression(term, SimpleTerm( Constant ( 2.0 ) ) );
    EXPECT_TRUE(expression.terms().size() == 1);
    EXPECT_EQ(expression.constant().leaf().value(), 2.0);
}