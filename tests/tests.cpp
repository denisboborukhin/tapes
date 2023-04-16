#include <gtest/gtest.h>
#include <vector>

#include "tape.hpp"
#include "tape_sorter.hpp"

using tape_space::Tape;
using tape_space::Tape_sorter;

int main()
{
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(tape, constructors)
{
    Tape tape(PROJECT_DIR_PATH + std::string("tests/tests_data/first_tape.tp"));

    tape.write(1);
    ASSERT_EQ(tape.read(), 1);
    ASSERT_EQ(tape.position(), 0);
    tape.next();

    tape.close();
}

TEST(tape, read_write)
{
    Tape tape(PROJECT_DIR_PATH + std::string("tests/tests_data/first_tape.tp"));

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

    tape.close();
}

TEST(tape, create_tape_from_text)
{
    Tape::fast_create_tape_from_text(PROJECT_DIR_PATH + std::string("tests/tests_data/text_for_create.txt"),
                                     PROJECT_DIR_PATH + std::string("tests/tests_data/created_tape.tp"));

    Tape tape(PROJECT_DIR_PATH + std::string("tests/tests_data/created_tape.tp"));

    for (int i = 0, num = tape.size() / sizeof(int) - 1; i != num; ++i) {
        ASSERT_EQ(tape.read(), i);
        tape.next();
    }
    ASSERT_EQ(tape.read(), 100);

    tape.close();
}

TEST(tape, create_text_from_tape)
{
    Tape::fast_create_text_from_tape(PROJECT_DIR_PATH + std::string("tests/tests_data/text_for_create_copy.txt"),
                                     PROJECT_DIR_PATH + std::string("tests/tests_data/created_tape.tp"));
}

TEST(tape, configurate)
{
    Tape tape(PROJECT_DIR_PATH + std::string("tests/tests_data/first_tape.tp"));
    Tape::configurate(PROJECT_DIR_PATH + std::string("tests/tests_data/config.cfg"));

    ASSERT_EQ(tape.read(), 1);
    ASSERT_EQ(tape.position(), 0);
    tape.next();

    ASSERT_EQ(tape.read(), 2);
    ASSERT_EQ(tape.position(), sizeof(int));
    tape.next();

    ASSERT_EQ(tape.read(), 30);
    tape.next();

    Tape::configurate();

    tape.close();
}

TEST(tape_sorter, sort_1)
{
    Tape first(PROJECT_DIR_PATH + std::string("tests/tests_data/unsorted.tp"));
    Tape second(PROJECT_DIR_PATH + std::string("tests/tests_data/sorted.tp"));

    Tape_sorter sorter;
    sorter.sort(first, second);
    second.go_to_begin();
    for (int i = 0, num_elems = second.size() / sizeof(int); i != num_elems; ++i) {
        ASSERT_EQ(second.read(), i);
        second.next();
    }

    Tape::fast_create_text_from_tape(PROJECT_DIR_PATH + std::string("tests/tests_data/sorted.txt"),
                                     PROJECT_DIR_PATH + std::string("tests/tests_data/sorted.tp"));

    first.close();
    second.close();
}

TEST(tape_sorter, sort_2)
{
    Tape first(PROJECT_DIR_PATH + std::string("tests/tests_data/unsorted2.tp"));
    Tape second(PROJECT_DIR_PATH + std::string("tests/tests_data/sorted2.tp"));

    Tape_sorter sorter;
    sorter.sort(first, second);

    Tape::fast_create_text_from_tape(PROJECT_DIR_PATH + std::string("tests/tests_data/sorted2.txt"),
                                     PROJECT_DIR_PATH + std::string("tests/tests_data/sorted2.tp"));

    first.close();
    second.close();
}

TEST(tape_sorter, sort_3)
{
    Tape first(PROJECT_DIR_PATH + std::string("tests/tests_data/unsorted3.tp"));
    Tape second(PROJECT_DIR_PATH + std::string("tests/tests_data/sorted3.tp"));

    Tape_sorter sorter;
    sorter.sort(first, second);
    second.go_to_begin();
    for (int i = 0, num_elems = second.size() / sizeof(int); i != num_elems; ++i) {
        ASSERT_EQ(second.read(), i);
        second.next();
    }

    Tape::fast_create_text_from_tape(PROJECT_DIR_PATH + std::string("tests/tests_data/sorted3.txt"),
                                     PROJECT_DIR_PATH + std::string("tests/tests_data/sorted3.tp"));

    first.close();
    second.close();
}
