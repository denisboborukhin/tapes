#include <cstdio>

#include "tape.hpp"

namespace tape_space {

Tape::Tape(const std::string &data_file_name) : data_file_name_ {data_file_name}, position_{0} 
{   
    FILE *data_stream = fopen(data_file_name_.c_str(), "rb");
    if (!data_stream)
    {
        std::cout << "incorrect file name: " << data_file_name_ << std::endl;
        return;
    }

    fseek(data_stream, 0, SEEK_END);
    size_ = ftell(data_stream);
    fclose (data_stream);
}

int Tape::read() const
{
    FILE *data_stream = fopen(data_file_name_.c_str(), "rb");
    if (!data_stream)
    {
        std::cout << "incorrect file name: " << data_file_name_ << std::endl;
        return 0;
    }

    if (fseek(data_stream, position_, SEEK_SET))
    {
        fclose (data_stream);
        return 0;   
    }

    int value = 0;
    fread (&value, sizeof (int), 1, data_stream);

    fclose (data_stream);
    return value;
}

int Tape::write(const int value)
{
    FILE *data_stream = fopen(data_file_name_.c_str(), "rb+");
    if (!data_stream)
    {
        std::cout << "incorrect file name: " << data_file_name_ << std::endl;
        return 0;
    }

    fseek(data_stream, position_, SEEK_SET);

    fwrite (&value, sizeof (int), 1, data_stream);
    fclose (data_stream);
    return value;
}

int Tape::next()
{
    position_ += sizeof (int);

    return position_;
}

int Tape::prev()
{
    position_ -= sizeof (int);

    return position_;
}

int Tape::position() const
{
    return position_;
}

bool Tape::size() const
{
    return size_;
}

}  // namespace tape_space
