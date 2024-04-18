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

#define HASH_TIME_FILE "hashtime.csv"

#define VERSION "v1"

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

inline bool getAllTime(Dict dict) {
    FILE* output = fopen("stats/hashtime.csv", "w");
    if (!output) {
        fprintf(stderr, "Failed to open file %s: %s\n", HASH_TIME_FILE,
                strerror(errno));
        return false;
    }

    fprintf(output, "Measure");
    for (size_t i = 1; i <= defaults::NumHashMeasures; ++i) {
        fprintf(output, ",%zu", i);
    }
    fprintf(output, "\n");

    GET_HASH_TIME(dict, hash::zero, output);
    GET_HASH_TIME(dict, hash::firstChar, output);
    GET_HASH_TIME(dict, hash::strlen, output);
    GET_HASH_TIME(dict, hash::sum, output);
    GET_HASH_TIME(dict, hash::ror, output);
    GET_HASH_TIME(dict, hash::rol, output);
    GET_HASH_TIME(dict, hash::crc32, output);
    GET_HASH_TIME(dict, hash::gnu, output);

    fclose(output);
    return true;
}

int main() {
    Dict dict;
    if (!dict.loadFromFile(DictFile))
        return EXIT_FAILURE;

#if (defined(HASH_STATS_MEASURE))
    getAllStats(dict);
#endif

#if (defined(HASH_TIME_MEASURE))
    getAllTime(dict);
#endif

#if (defined(LOOKUP_PERF_TEST))
    benchmarkLookup(dict, REPORTS_DIR VERSION ".json");
#endif

    dict.destroy();
    return 0;
}
