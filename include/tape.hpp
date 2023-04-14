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

    int size() const;
    int position() const;

    void configurate(const std::string &config_file_name);

    static void fast_create_tape_from_text(const std::string &text_path_name, const std::string &tape_path_name);
    static void fast_create_text_from_tape(const std::string &text_path_name, const std::string &tape_path_name);

private:
    const std::string data_file_name_;
    int position_;
    int size_;

    int write_time_ = 0;
    int read_time_ = 0;
    int shift_time_ = 0;
};

}  // namespace tape_space

#endif
