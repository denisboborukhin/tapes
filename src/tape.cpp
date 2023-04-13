#include "tape.hpp"

namespace tape_space {

int Tape::read() const
{
    return data_.at(position_);
}

int Tape::write(const int value)
{
    data_.at(position_) = value;
    return value;
}

int Tape::next()
{
    ++position_;
    return position_;
}

int Tape::prev()
{
    --position_;
    return position_;
}

int Tape::get_size() const
{
    return data_.size();
}

int Tape::get_position() const
{
    return position_;
}

}  // namespace tape_space
