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
    Tape tape (PROJECT_DIR_PATH + std::string("/tests/tests_data/first_tape.tp"));

    tape.write (1);
    ASSERT_EQ (tape.read (), 1);
    ASSERT_EQ (tape.position (), 0);
    tape.next ();
}

TEST(tape, read_write)
{
    Tape tape (PROJECT_DIR_PATH + std::string("/tests/tests_data/first_tape.tp"));

    tape.write (1);
    ASSERT_EQ (tape.read (), 1);
    ASSERT_EQ (tape.position (), 0);
    tape.next ();

    tape.write (2);
    ASSERT_EQ (tape.read (), 2);
    ASSERT_EQ (tape.position (), sizeof (int));
    tape.next ();

    tape.write (3);
    ASSERT_EQ (tape.read (), 3);
    tape.next ();

    tape.write (10);
    ASSERT_EQ (tape.read (), 10);
    tape.prev ();

    ASSERT_EQ (tape.position (), 2 * sizeof (int));
    ASSERT_EQ (tape.read (), 3);
    tape.write (30);
    ASSERT_EQ (tape.read (), 30);

    tape.next ();
    ASSERT_EQ (tape.read (), 10);
}
