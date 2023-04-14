#include "tape_sorter.hpp"

namespace tape_space {

Tape_sorter::Tape_sorter(const Tape &first_tape, Tape &second_tape)
    : unsorted_tape_ {first_tape}, resulted_tape_ {second_tape}
{
    int limit_elems = RAM_LIMIT / sizeof (int);
    int num_elems = unsorted_tape_.size () / sizeof (int);

}

}  // namespace tape_space
