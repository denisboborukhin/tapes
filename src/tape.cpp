#include <cstdio>
#include <thread>
#include <fstream>

#include "tape.hpp"

namespace tape_space {

Tape::Tape(const std::string &data_file_name) : position_ {0}
{
    data_stream_ = fopen(data_file_name.c_str(), "rb+");
    if (!data_stream_) {
        data_stream_ = fopen(data_file_name.c_str(), "wb+");
    }

    fseek(data_stream_, 0, SEEK_END);
    size_ = ftell(data_stream_);
    rewind(data_stream_);
}

void Tape::close()
{
    fclose(data_stream_);
}

int Tape::write_time_ = 0;
int Tape::read_time_ = 0;
int Tape::shift_time_ = 0;

int Tape::read() const
{
    int value = 0;
    fread(&value, sizeof(int), 1, data_stream_);
    fseek(data_stream_, -sizeof(int), SEEK_CUR);

    std::this_thread::sleep_for(std::chrono::milliseconds(read_time_));

    return value;
}

int Tape::write(const int value)
{
    fwrite(&value, sizeof(int), 1, data_stream_);
    fseek(data_stream_, -sizeof(int), SEEK_CUR);
    if (position_ == size_)
        size_ += sizeof(int);

    std::this_thread::sleep_for(std::chrono::milliseconds(write_time_));

    return value;
}

int Tape::next()
{
    position_ += sizeof(int);
    fseek(data_stream_, sizeof(int), SEEK_CUR);
    std::this_thread::sleep_for(std::chrono::milliseconds(shift_time_));

    return position_;
}

int Tape::prev()
{
    position_ -= sizeof(int);
    fseek(data_stream_, -sizeof(int), SEEK_CUR);
    std::this_thread::sleep_for(std::chrono::milliseconds(shift_time_));

    return position_;
}

int Tape::go_to_begin()
{
    fseek(data_stream_, 0, SEEK_SET);
    std::this_thread::sleep_for(std::chrono::milliseconds(shift_time_ * position_ / sizeof(int)));

    position_ = 0;
    return position_;
}

int Tape::go_to_end()
{
    fseek(data_stream_, 0, SEEK_END);
    std::this_thread::sleep_for(std::chrono::milliseconds(shift_time_ * (size_ - position_) / sizeof(int)));

    position_ = size_;
    return position_;
}

int Tape::position() const
{
    return position_;
}

int Tape::size() const
{
    return size_;
}

bool Tape::is_end() const
{
    return position_ == size_;
}

void Tape::configurate(const std::string &config_file_name)
{
    if (config_file_name.empty()) {
        write_time_ = 0;
        read_time_ = 0;
        shift_time_ = 0;

        return;
    }

    std::ifstream config_stream(config_file_name);

    config_stream >> write_time_;
    config_stream >> read_time_;
    config_stream >> shift_time_;

    config_stream.close();
}

void Tape::fast_create_tape_from_text(const std::string &text_path_name, const std::string &tape_path_name)
{
    std::ifstream text_stream(text_path_name);

    int num_elem = 0;
    text_stream >> num_elem;
    int *data = new int[num_elem];

    int index = 0;
    while (!text_stream.eof()) {
        text_stream >> data[index];
        index++;
    }

    text_stream.close();

    FILE *data_stream = fopen(tape_path_name.c_str(), "wb");
    fwrite(data, sizeof(int), num_elem, data_stream);

    fclose(data_stream);
    delete[] data;
}

void Tape::fast_create_text_from_tape(const std::string &text_path_name, const std::string &tape_path_name)
{
    FILE *tape_stream = fopen(tape_path_name.c_str(), "rb");
    if (!tape_stream) {
        std::cout << "incorrect file name: " << tape_path_name << std::endl;
        return;
    }

    fseek(tape_stream, 0, SEEK_END);
    int size = ftell(tape_stream) / sizeof(int);
    rewind(tape_stream);

    int *data = new int[size];
    int num_readed_elem = fread(data, sizeof(int), size, tape_stream);
    fclose(tape_stream);

    if (num_readed_elem != size) {
        std::cout << "error reading, readed " << num_readed_elem << " elems" << std::endl;
        return;
    }

    std::ofstream text_stream(text_path_name);
    text_stream << num_readed_elem;
    text_stream << ' ';

    for (int index = 0; index != num_readed_elem; ++index) {
        text_stream << data[index];
        text_stream << ' ';
    }

    text_stream << '\n';
    text_stream.close();

    delete[] data;
}

}  // namespace tape_space
