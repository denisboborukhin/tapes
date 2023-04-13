#ifndef TAPE_HPP
#define TAPE_HPP

#include <vector>
#include <iostream>

namespace tape_space {

class Tape final {
public:
    Tape() {}

    int read() const;
    int write(const int value);

    int next();
    int prev();

    int get_size() const;
    int get_position() const;

private:
    std::vector<int> data_ {};
    int position_ = 0;
};

}  // namespace tape_space

#endif
