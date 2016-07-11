
#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Symbolics, Constraints)
{
    Solver s;
    Variable v("v");
    Constant c1("c1", 20);
    Constant c2("c2", 2);
    
    s.addConstraint(c1 == v);
    s.updateVariables();
    EXPECT_EQ(v.value(), 20);
    s.reset();
    
    s.addConstraint(v == c1);
    s.updateVariables();
    EXPECT_EQ(v.value(), 20);
    s.reset();
    
    s.addConstraint(c1 == v + v);
    s.updateVariables();
    EXPECT_EQ(v.value(), 10);
    s.reset();
    
    s.addConstraint(v + v == c1);
    s.updateVariables();
    EXPECT_EQ(v.value(), 10);
    s.reset();
    
    s.addConstraint(v == c1 + c2);
    s.updateVariables();
    EXPECT_EQ(v.value(), 22);
    s.reset();
    
    s.addConstraint(c1 + c2 == v);
    s.updateVariables();
    EXPECT_EQ(v.value(), 22);
    s.reset();
    
    s.addConstraint(v + c2 == c1);
    s.updateVariables();
    EXPECT_EQ(v.value(), 18);
    s.reset();
    
    s.addConstraint(c1 == v + c2);
    s.updateVariables();
    EXPECT_EQ(v.value(), 18);
    s.reset();
    
    s.addConstraint(v * c2 == c1);
    s.updateVariables();
    EXPECT_EQ(v.value(), 10);
    s.reset();
    
    s.addConstraint(c1 == v * c2);
    s.updateVariables();
    EXPECT_EQ(v.value(), 10);
    s.reset();
    
    s.addConstraint(v / c2 == c1);
    s.updateVariables();
    EXPECT_EQ(v.value(), 40);
    s.reset();
    
    s.addConstraint(c1 == v / c2);
    s.updateVariables();
    EXPECT_EQ(v.value(), 40);
    s.reset();
}

TEST(Symbolics, Complex)
{
    Solver s;
    Variable v1("v1");
    Variable v2("v2");
    Constant c1("c1", 20);
    Constant c2("c2", 2);
    
    s.addConstraint(50 == v2);
    s.addConstraint(v1 == ((c1/c2) + 10 - 5) * v2);
    s.updateVariables();
    EXPECT_EQ(v1.value(), 750);
    
    c1.setValue(4);
    s.reevaluateConstants();
    s.updateVariables();
    EXPECT_EQ(v1.value(), 350);
    s.reset();
}

