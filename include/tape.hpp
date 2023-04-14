#ifndef TAPE_HPP
#define TAPE_HPP

#include <vector>
#include <iostream>

namespace tape_space {

class Tape final {
public:
    Tape(const std::string &data_file_name);

    int read() const;
    int write(const int value);

    int next();
    int prev();

    bool size() const;
    int position() const;

    static void fast_create_tape_from_text(const std::string &text_path_name, const std::string &tape_path_name);
    static void fast_create_text_from_tape(const std::string &text_path_name, const std::string &tape_path_name);

private:
    const std::string data_file_name_;
    int position_;
    int size_;
};

}  // namespace tape_space

#endif
