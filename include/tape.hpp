#ifndef TAPE_HPP
#define TAPE_HPP

#include <iostream>

namespace tape_space {

class Tape final {
public:
    Tape(const std::string &data_file_name);
    Tape(const Tape &other) = delete;
    Tape(Tape &&other) = delete;

    Tape &operator=(const Tape &other) = delete;
    Tape &operator=(Tape &&other) = delete;

    ~Tape();

    int read() const;
    int write(const int value);

    int next();
    int prev();

    int size() const;
    int position() const;

    static void configurate(const std::string &config_file_name = {});

    static void fast_create_tape_from_text(const std::string &text_path_name, const std::string &tape_path_name);
    static void fast_create_text_from_tape(const std::string &text_path_name, const std::string &tape_path_name);

private:
    FILE *data_stream_;
    int position_;
    int size_;

    static int write_time_;
    static int read_time_;
    static int shift_time_;
};

}  // namespace tape_space

#endif
