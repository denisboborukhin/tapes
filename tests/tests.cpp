#include <gtest/gtest.h>
#include <vector>

#include "tape.hpp"

using tape_space::Tape;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(tape, constructors)
{
    Tape tape;
    ASSERT_EQ(tape.get_size(), 0);
    ASSERT_EQ(tape.get_position(), 0);
}
