/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "benchmark.h"

static const char DictFile[] = "data/dictionary.txt";

inline void getAllStats(Dict dict) {
    GET_HASH_STATS(dict, hash::zero);
    GET_HASH_STATS(dict, hash::strlen);
    GET_HASH_STATS(dict, hash::firstChar);
    GET_HASH_STATS(dict, hash::sum);
    GET_HASH_STATS(dict, hash::ror);
    GET_HASH_STATS(dict, hash::rol);
    GET_HASH_STATS(dict, hash::crc32);

    // часть задания
    getHashStats(dict, defaults::LowerBucketCount, hash::sum,
                 STATS_DIR "hash::sum(lower size).csv");
}

int main() {
    Dict dict;
    if (!dict.loadFromFile(DictFile))
        return EXIT_FAILURE;

    getAllStats(dict);

    dict.destroy();
    return 0;
}
