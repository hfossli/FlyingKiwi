
#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Symbolics, ConstantsMultiply)
{
    Constant a(20);
    Constant b(40);
    SimpleTerm term = a * b;
    
    EXPECT_EQ(term.value(), 800.0);
}

TEST(Symbolics, SimpleTerm)
{
    Constant a("const");
    a.setValue(20);
    EXPECT_EQ((a * 40).value(), 800.0);
    EXPECT_EQ((a / 5).value(), 4.0);
    EXPECT_EQ((a + 5).value(), 25.0);
    EXPECT_EQ((a - 3).value(), 17.0);
    EXPECT_EQ((a - -3).value(), 23.0);
    
    a.setValue(25);
    EXPECT_EQ((a - -3).value(), 28.0);
}

TEST(Symbolics, Term)
{
    Constant tau(6.28);
    SimpleTerm pi(tau, SimpleTerm::OP_DIVIDE, 2.0);
    Variable v("foo");
    Term term(v * pi);
}