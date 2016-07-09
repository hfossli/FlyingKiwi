#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Solver, Basics)
{
    Constant constant("x");
    constant.setValue(6.28);
    
    Variable leftSide("v");
    SimpleTerm rightSide(constant, SimpleTerm::OP_MULTIPLY, -0.5);
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
    Constant c1("c1");
    Constant c2("c2");
    c1.setValue(6.28);
    c2.setValue(0.5);
    
    Variable v1("v1");
    
    Expression expression(-v1, SimpleTerm(c1, SimpleTerm::OP_MULTIPLY, c2));
    Constraint constraint(expression, Constraint::OP_EQ);
    
    Solver solver;
    
    solver.addConstraint(constraint);
    solver.updateVariables();
    EXPECT_EQ(v1.value(), 3.14);
    
    c1.setValue(50.0);
    solver.reevaluateConstants();
    solver.updateVariables();
    EXPECT_EQ(v1.value(), 25);
    
    c2.setValue(1.0);
    solver.reevaluateConstants();
    solver.updateVariables();
    EXPECT_EQ(v1.value(), 50.0);
}




