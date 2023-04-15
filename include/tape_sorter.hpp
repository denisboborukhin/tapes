#ifndef TAPE_SORTER_HPP
#define TAPE_SORTER_HPP

#include "tape.hpp"

namespace tape_space {

class Tape_sorter final {
public:
    int sort(Tape &unsorted_tape, Tape &resulted_tape);

public:
    static int RAM_LIMIT;
};

}  // namespace tape_space

#endif
