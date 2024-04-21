/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_BENCHMARK_H_
#define HASHMAP_BENCHMARK_H_

#include "dictloader.h"

#define LOOKUP_STATS_DIR "stats/lookup/"
#define STATS_DIR "stats/hash/"
#define GET_HASH_STATS(dict, hash)                                             \
    getHashStats(dict, defaults::UpperBucketCount, hash, STATS_DIR #hash ".csv")

#define BENCHMARK_HASH(dict, hash)                                             \
    benchmarkHash(dict, hash, STATS_DIR #hash "_time.csv")

#if 0
/** @brief Prints stats in CSV format.
 *
 *  @param dict Test dictionary.
 *  @param hash Pointer to tested hash function.
 *  @param name Filename to open.
 *
 *  @return `false` in case of any failure.
 */
bool getHashStats(Dict dict, size_t bucketCount, Hash* hash, const char* name);

bool benchmarkHash(Dict dict, Hash* hash, const char* name);
#endif

bool benchmarkLookup(Dict dict, const char* name);

#endif  // HASHMAP_BENCHMARK_H_
