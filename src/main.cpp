/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include <errno.h>

#include "benchmark.h"

// #define HASH_STATS_MEASURE
// #define HASH_TIME_MEASURE
#define LOOKUP_PERF_TEST

#define VERSION "v1"

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

static const char DictFile[] = "data/dictionary.txt";

inline void getAllStats(Dict dict) {
    GET_HASH_STATS(dict, hash::zero);
    GET_HASH_STATS(dict, hash::firstChar);
    GET_HASH_STATS(dict, hash::strlen);
    GET_HASH_STATS(dict, hash::sum);
    GET_HASH_STATS(dict, hash::ror);
    GET_HASH_STATS(dict, hash::rol);
    GET_HASH_STATS(dict, hash::crc32);
    GET_HASH_STATS(dict, hash::gnu);

    // часть задания
    getHashStats(dict, defaults::LowerBucketCount, hash::sum,
                 STATS_DIR "hash::sum(lower size).csv");
}

inline void benchmarkAllHash(Dict dict) {
    BENCHMARK_HASH(dict, hash::ror);
    BENCHMARK_HASH(dict, hash::rol);
    BENCHMARK_HASH(dict, hash::crc32);
    BENCHMARK_HASH(dict, hash::gnu);
}

int main() {
    Dict dict;
    if (!dict.loadFromFile(DictFile))
        return EXIT_FAILURE;

#if (defined(HASH_STATS_MEASURE))
    getAllStats(dict);
#endif

#if (defined(HASH_TIME_MEASURE))
    benchmarkAllHash(dict);
#endif

#if (defined(LOOKUP_PERF_TEST))
    benchmarkLookup(dict, LOOKUP_STATS_DIR VERSION ".json");
#endif

    dict.destroy();
    return 0;
}
