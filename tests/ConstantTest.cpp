#include <gtest/gtest.h>
#include "Constant.h"

using namespace FlyingKiwi;

TEST(Constant, Basics)
{
    Constant x("x");
    x.setValue(10);
    EXPECT_TRUE(x.editable());
    EXPECT_EQ(x.value(), 10);
}

TEST(Constant, Editable)
{
    Constant x(20, false);
    EXPECT_TRUE(!x.editable());
    EXPECT_THROW(x.setValue(30), ConstantEditError);
    EXPECT_EQ(x.value(), 20);
    
    Constant y(20, true);
    EXPECT_TRUE(y.editable());
    EXPECT_NO_THROW(y.setValue(30));
    EXPECT_EQ(y.value(), 30);
}

