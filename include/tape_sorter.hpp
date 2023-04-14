#ifndef TAPE_SORTER_HPP
#define TAPE_SORTER_HPP

#include "tape.hpp"

namespace tape_space {

class Tape_sorter final {
public:
    Tape_sorter(const Tape &first_tape, const Tape &second_tape);

private:
    const Tape &unsorted_tape_;
    const Tape &resulted_tape_;
};

}  // namespace tape_space

#endif
