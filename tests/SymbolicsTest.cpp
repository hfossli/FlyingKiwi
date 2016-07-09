
#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Symbolics, ConstantsMultiply) {
    
    Constant a(20);
    Constant b(40);
    SimpleTerm term = a * b;
    
    EXPECT_EQ(term.value(), 800.0);
}

TEST(Symbolics, SimpleTerm) {
    
    Constant a(20);
    EXPECT_EQ((a * 40).value(), 800.0);
    EXPECT_EQ((a / 5).value(), 4.0);
    EXPECT_EQ((a + 5).value(), 25.0);
    EXPECT_EQ((a - 3).value(), 17.0);
}