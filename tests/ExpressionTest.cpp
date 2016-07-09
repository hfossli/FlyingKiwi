#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Expression, Basics) {

    Variable v("v");
    SimpleTerm tree(10, OP_MULTIPLY, 20);
    Term term(v, tree);
    
    Expression expression(term, SimpleTerm( Constant ( 2.0 ) ) );
    EXPECT_TRUE(expression.terms().size() == 1);
    EXPECT_EQ(expression.constant().leftLeaf().value(), 2.0);
}