#include "gtest/gtest.h"
#include "include/mod_string.h"

TEST(StrMod, RecoverFirst) {
    EXPECT_EQ(recover_first_int("1abc2"), 1);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
