#include <gtest/gtest.h>
#include "FlyingKiwi.h"

using namespace FlyingKiwi;

TEST(Constant, Basics) {
    Constant x("x");
    x.setValue(10);
    EXPECT_TRUE(x.editable());
    EXPECT_EQ(x.value(), 10);
}

TEST(Constant, Locking) {
    Constant x(20);
    EXPECT_TRUE(!x.editable());
    ASSERT_DEATH(x.setValue(30), "Error: Can not change .*");
    EXPECT_EQ(x.value(), 20);
}

