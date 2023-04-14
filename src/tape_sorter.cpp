#include "tape_sorter.hpp"

namespace tape_space {

Tape_sorter::Tape_sorter(const Tape &first_tape, const Tape &second_tape)
    : unsorted_tape_ {first_tape}, resulted_tape_ {second_tape}
{
}

}  // namespace tape_space
