#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Term, Basics) {

    Variable v("v");
    
    Constant x("x");
    Constant y("y");

    x.setValue(10);
    y.setValue(20);
    
    SimpleTerm leaf(x);
    SimpleTerm tree(leaf, SimpleTerm::RelationalOperator::multiply, y);
    
    Term term(v, tree);
    EXPECT_TRUE(term.coefficient().equals(tree));
}