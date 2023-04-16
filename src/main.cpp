#include "tape.hpp"
#include "tape_sorter.hpp"

using tape_space::Tape;
using tape_space::Tape_sorter;

int main(int argc, char **argv)
{
    std::string name_unsorted_tape;
    std::cin >> name_unsorted_tape;
    Tape unsorted_tape(PROJECT_DIR_PATH + name_unsorted_tape);

    std::string name_resulted_tape;
    std::cin >> name_resulted_tape;
    Tape resulted_tape(PROJECT_DIR_PATH + name_resulted_tape);

    Tape_sorter sorter;
    sorter.sort(unsorted_tape, resulted_tape);

    return 0;
}
