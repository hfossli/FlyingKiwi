#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Solver, Basics)
{
    Constant constant("x");
    constant.setValue(6.28);
    
    Variable leftSide("v");
    SimpleTerm rightSide(constant, OP_MULTIPLY, -0.5);
    Expression expression(leftSide, rightSide);
    Constraint constraint(expression, Constraint::RelationalOperator::OP_EQ);
    
    Solver solver;
    
    EXPECT_TRUE(!solver.hasConstraint(constraint));
    
    solver.addConstraint(constraint);
    
    EXPECT_TRUE(solver.hasConstraint(constraint));
    EXPECT_TRUE(solver.hasConstraint(constraint));
    
    solver.updateVariables();
    EXPECT_EQ(leftSide.value(), 3.14);
    
    solver.removeConstraint(constraint);
    EXPECT_TRUE(!solver.hasConstraint(constraint));
}

TEST(Solver, UpdateConstants)
{
    Constant constant("x");
    constant.setValue(6.28);
    
    Variable leftSide("v");
    SimpleTerm rightSide(constant, OP_MULTIPLY, -0.5);
    Expression expression(leftSide, rightSide);
    Constraint constraint(expression, Constraint::RelationalOperator::OP_EQ);
    
    Solver solver;
    
    solver.addConstraint(constraint);
    solver.updateVariables();
    EXPECT_EQ(leftSide.value(), 3.14);
    
    constant.setValue(50.0);
    solver.reevaluateConstants();
    
    solver.updateVariables();
    EXPECT_EQ(leftSide.value(), 25);
}




