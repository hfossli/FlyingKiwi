#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Constraint, Basics) {
    
    Variable v("v");
    
    Constant x("x");
    Constant y("y");
    
    x.setValue(10);
    y.setValue(20);
    
    SimpleTerm leaf(x);
    SimpleTerm tree(leaf, SimpleTerm::RelationalOperator::multiply, y);
    
    Term term(v, tree);
    
    Expression expression(term, SimpleTerm( Constant ( 2.0 ) ) );
    
    Constraint constraint(term, Constraint::RelationalOperator::OP_EQ);
    
    EXPECT_TRUE(constraint.expression().terms().size() == 1);
}