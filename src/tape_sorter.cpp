#include <vector>
#include <sys/stat.h>

#include "tape_sorter.hpp"

namespace tape_space {

static std::vector<Tape> create_sorted_temp_tapes(Tape &unsorted_tape, const int ram_limit);
static Tape merge_tapes(std::vector<Tape> &sorted_tapes, Tape &resulted_tape, const int num_elems);

static void sort_last_elem_decrease(std::vector<std::pair<int, int>> &elems);
static void sort_last_elem_increase(std::vector<int> &elems);
static Tape create_temp_tape(const int index_sorter, const int index, const std::vector<int> &elems);

static void close_tapes(std::vector<Tape> &tapes);

static std::string get_temp_name(const int index_sorter, const int index);

int Tape_sorter::RAM_LIMIT = 10;

int Tape_sorter::sort(Tape &unsorted_tape, Tape &resulted_tape)
{
    std::vector<Tape> sorted_tapes = create_sorted_temp_tapes(unsorted_tape, RAM_LIMIT);

    int num_elems = unsorted_tape.size() / sizeof(int);
    merge_tapes(sorted_tapes, resulted_tape, num_elems);

    close_tapes(sorted_tapes);

    return 0;
}

std::vector<Tape> create_sorted_temp_tapes(Tape &unsorted_tape, const int ram_limit)
{
    int limit_elems = ram_limit / sizeof(int);
    int num_elems = unsorted_tape.size() / sizeof(int);

    int num_packs = num_elems / limit_elems + 1;
    int num_elems_in_pack = num_elems / num_packs;

    std::vector<Tape> sorted_tapes;
    sorted_tapes.reserve(num_packs);

    int index_sorter = rand();
    mkdir((PROJECT_DIR_PATH + std::string("tmp/")).c_str(), 0777);
    for (int index_pack = 0; index_pack != num_packs - 1; ++index_pack) {
        std::vector<int> sort_pack_elems;
        sort_pack_elems.reserve(num_elems_in_pack);

        for (int index = 0; index != num_elems_in_pack; ++index) {
            sort_pack_elems.push_back(unsorted_tape.read());
            unsorted_tape.next();

            sort_last_elem_increase(sort_pack_elems);
        }

        Tape temp_tape = create_temp_tape(index_sorter, index_pack + 1, sort_pack_elems);
        sorted_tapes.push_back(temp_tape);
    }

    int num_elems_in_last_pack = num_elems - num_elems_in_pack * (num_packs - 1);
    std::vector<int> sort_pack_elems;
    sort_pack_elems.reserve(num_elems_in_last_pack);

    for (int index = 0; index != num_elems_in_last_pack; ++index) {
        sort_pack_elems.push_back(unsorted_tape.read());
        unsorted_tape.next();

        sort_last_elem_increase(sort_pack_elems);
    }

    Tape temp_tape = create_temp_tape(index_sorter, num_packs, sort_pack_elems);
    sorted_tapes.push_back(temp_tape);

    return sorted_tapes;
}

Tape merge_tapes(std::vector<Tape> &sorted_tapes, Tape &resulted_tape, const int num_elems)
{
    int index = 0;
    int num_packs = sorted_tapes.size();
    using elem_and_num_tape = typename std::pair<int, int>;
    std::vector<elem_and_num_tape> smallest_elems;
    smallest_elems.reserve(num_packs);
    for (int i = 0; i != num_packs; ++i) {
        Tape &tape = sorted_tapes[i];
        smallest_elems.push_back({tape.read(), i});
        tape.next();

        sort_last_elem_decrease(smallest_elems);
    }

    while (index != num_elems) {
        auto pair = smallest_elems.back();
        resulted_tape.write(pair.first);
        resulted_tape.next();
        ++index;

        smallest_elems.pop_back();

        int num_tape = pair.second;
        if (sorted_tapes[num_tape].is_end())
            continue;

        Tape &tape = sorted_tapes[num_tape];
        smallest_elems.push_back({tape.read(), num_tape});
        tape.next();

        sort_last_elem_decrease(smallest_elems);
    }

    return resulted_tape;
}

void sort_last_elem_decrease(std::vector<std::pair<int, int>> &elems)
{
    if (elems.size() < 2)
        return;

    for (auto it = elems.rbegin(), end_it = elems.rend() - 1; it != end_it; ++it) {
        auto &elem = *it;
        auto &next_elem = *(it + 1);
        if (elem.first <= next_elem.first)
            break;

        std::swap(elem, next_elem);
    }
}

void sort_last_elem_increase(std::vector<int> &elems)
{
    if (elems.size() < 2)
        return;

    for (auto it = elems.rbegin(), end_it = elems.rend() - 1; it != end_it; ++it) {
        int &elem = *it;
        int &next_elem = *(it + 1);
        if (elem >= next_elem)
            break;

        std::swap(elem, next_elem);
    }
}

Tape create_temp_tape(const int index_sorter, const int index, const std::vector<int> &elems)
{
    std::string tape_name = get_temp_name(index_sorter, index);
    Tape temp_tape(tape_name);

    for (auto elem : elems) {
        temp_tape.write(elem);
        temp_tape.next();
    }

    Tape::fast_create_text_from_tape(tape_name + ".txt", tape_name);
    temp_tape.go_to_begin();

    return temp_tape;
}

void close_tapes(std::vector<Tape> &tapes)
{
    for (auto &&elem : tapes) {
        elem.close();
    }
}

std::string get_temp_name(const int index_sorter, const int index)
{
    return PROJECT_DIR_PATH + std::string("/tmp/temp_tape_") + std::to_string(index) + "_" +
           std::to_string(index_sorter) + std::string(".tp");
}

}  // namespace tape_space
