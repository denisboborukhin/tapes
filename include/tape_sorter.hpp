#ifndef TAPE_SORTER_HPP
#define TAPE_SORTER_HPP

#include "tape.hpp"

namespace tape_space {

class Tape_sorter final {
public:
    Tape_sorter(const Tape &first_tape, Tape &second_tape);

    static const int RAM_LIMIT = 100;

private:
    const Tape &unsorted_tape_;
    Tape &resulted_tape_;
};

}  // namespace tape_space

#endif
