#include <vector>

#include "tape_sorter.hpp"

namespace tape_space {

// static void create_sorted_temp_tapes ();
static void sort_last_elem(std::vector<int> &elems);
static void create_temp_tape(const int index, const std::vector<int> &elems);
static std::string get_temp_name(const int index);

int Tape_sorter::RAM_LIMIT = 100;

int Tape_sorter::sort(Tape &unsorted_tape, Tape &resulted_tape)
{
    int limit_elems = RAM_LIMIT / sizeof(int);
    int num_elems = unsorted_tape.size() / sizeof(int);

    int num_packs = num_elems / limit_elems + 1;
    int num_elems_in_pack = num_elems / num_packs;

    for (int index_pack = 0; index_pack != num_packs - 1; ++index_pack) {
        std::vector<int> sort_pack_elems;
        sort_pack_elems.reserve(num_elems_in_pack);

        for (int index = 0; index != num_elems_in_pack; ++index) {
            sort_pack_elems.push_back(unsorted_tape.read());
            unsorted_tape.next();

            sort_last_elem(sort_pack_elems);
        }

        create_temp_tape(index_pack, sort_pack_elems);
    }

    int num_elems_in_last_pack = num_elems - num_elems_in_pack * (num_packs - 1);
    std::vector<int> sort_pack_elems;
    sort_pack_elems.reserve(num_elems_in_last_pack);

    for (int index = 0; index != num_elems_in_last_pack; ++index) {
        sort_pack_elems.push_back(unsorted_tape.read());
        unsorted_tape.next();

        sort_last_elem(sort_pack_elems);
    }

    create_temp_tape(num_packs, sort_pack_elems);

    return 0;
}

void sort_last_elem(std::vector<int> &elems)
{
    if (elems.size() < 2)
        return;

    for (auto it = elems.rbegin(), end_it = elems.rend(); it != end_it; ++it) {
        int &elem = *it;
        int &next_elem = *(it + 1);
        if (elem >= next_elem)
            break;

        std::swap(elem, next_elem);
    }
}

void create_temp_tape(const int index, const std::vector<int> &elems)
{
    Tape temp_tape(get_temp_name(index));

    for (auto elem : elems) {
        temp_tape.write(elem);
        temp_tape.next();
    }
}

std::string get_temp_name(const int index)
{
    return PROJECT_DIR_PATH + std::string("/tmp/temp_tape") + std::to_string(index) + std::string(".tp");
}

}  // namespace tape_space
