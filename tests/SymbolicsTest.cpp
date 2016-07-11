
#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Symbolics, ConstantsMultiply)
{
    Constant a(20, true);
    Constant b(40, true);
    SimpleTerm term = a * b;
    
    EXPECT_EQ(term.value(), 800);
}

TEST(Symbolics, ConstantAndPrimitive)
{
    Constant a("a");
    a.setValue(20);
    EXPECT_EQ((a * 40).value(), 800);
    EXPECT_EQ((a / 5).value(), 4);
    EXPECT_EQ((a + 5).value(), 25);
    EXPECT_EQ((a - 3).value(), 17);
    EXPECT_EQ((a - -3).value(), 23);
    
    EXPECT_EQ((-a).value(), -20);
    
    EXPECT_EQ((40 * a).value(), 800);
    EXPECT_EQ((80 / a).value(), 4);
    EXPECT_EQ((5 + a).value(), 25);
    EXPECT_EQ((-3 + a).value(), 17);
    EXPECT_EQ((-3 - -a).value(), 17);
}

TEST(Symbolics, ConstantAndConstant)
{
    Constant a("a");
    Constant b("b");
    a.setValue(20);
    b.setValue(2);
    EXPECT_EQ((a * b).value(), 40);
    EXPECT_EQ((a / b).value(), 10);
    EXPECT_EQ((a + b).value(), 22);
    EXPECT_EQ((a - b).value(), 18);
    EXPECT_EQ((a - -b).value(), 22);
}

TEST(Symbolics, VariableAndPrimitive)
{
    Variable v("v");
    EXPECT_EQ((v * 10).coefficient().value(), 10);
    EXPECT_EQ((v * 10).variable().name(), "v");
    
    EXPECT_EQ((v / 10).coefficient().value(), 0.1);
    EXPECT_EQ((v / 10).variable().name(), "v");
    
    EXPECT_EQ((10 * v).coefficient().value(), 10);
    EXPECT_EQ((10 * v).variable().name(), "v");
    
    EXPECT_EQ((10 / v).coefficient().value(), 0.1);
    EXPECT_EQ((10 / v).variable().name(), "v");
}

TEST(Symbolics, ConstantAndVariable)
{
    Variable v("v");
    Constant c(10, false);
    EXPECT_EQ((v * c).coefficient().value(), 10);
    EXPECT_EQ((v * c).variable().name(), "v");
    
    EXPECT_EQ((v / c).coefficient().value(), 0.1);
    EXPECT_EQ((v / c).variable().name(), "v");
    
    EXPECT_EQ((c * v).coefficient().value(), 10);
    EXPECT_EQ((c * v).variable().name(), "v");
    
    EXPECT_EQ((c / v).coefficient().value(), 0.1);
    EXPECT_EQ((c / v).variable().name(), "v");
}

TEST(Symbolics, Term)
{
    Constant tau(6.28, true);
    SimpleTerm pi(tau / 2);
    Variable v("foo");
    Term term(v * pi);
}