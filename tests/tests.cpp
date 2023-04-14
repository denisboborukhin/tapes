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
    Tape tape(PROJECT_DIR_PATH + std::string("/tests/tests_data/first_tape.tp"));

    tape.write(1);
    ASSERT_EQ(tape.read(), 1);
    ASSERT_EQ(tape.position(), 0);
    tape.next();
}

TEST(tape, read_write)
{
    Tape tape(PROJECT_DIR_PATH + std::string("/tests/tests_data/first_tape.tp"));

    tape.write(1);
    ASSERT_EQ(tape.read(), 1);
    ASSERT_EQ(tape.position(), 0);
    tape.next();

    tape.write(2);
    ASSERT_EQ(tape.read(), 2);
    ASSERT_EQ(tape.position(), sizeof(int));
    tape.next();

    tape.write(3);
    ASSERT_EQ(tape.read(), 3);
    tape.next();

    tape.write(10);
    ASSERT_EQ(tape.read(), 10);
    tape.prev();

    ASSERT_EQ(tape.position(), 2 * sizeof(int));
    ASSERT_EQ(tape.read(), 3);
    tape.write(30);
    ASSERT_EQ(tape.read(), 30);

    tape.next();
    ASSERT_EQ(tape.read(), 10);
}

TEST(tape, create_tape_from_text)
{
    Tape::fast_create_tape_from_text(PROJECT_DIR_PATH + std::string("/tests/tests_data/text_for_create.txt"),
                                     PROJECT_DIR_PATH + std::string("/tests/tests_data/created_tape.tp"));

    Tape tape(PROJECT_DIR_PATH + std::string("/tests/tests_data/created_tape.tp"));

    for (int i = 0; i != 10; ++i) {
        ASSERT_EQ(tape.read(), i);
        tape.next();
    }
    ASSERT_EQ(tape.read(), 100);
}

TEST(tape, create_text_from_tape)
{
    Tape::fast_create_text_from_tape(PROJECT_DIR_PATH + std::string("/tests/tests_data/text_for_create_copy.txt"),
                                     PROJECT_DIR_PATH + std::string("/tests/tests_data/created_tape.tp"));
}
