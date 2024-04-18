/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_BENCHMARK_H_
#define HASHMAP_BENCHMARK_H_

#include "dictloader.h"

#define STATS_DIR "stats/"
#define GET_HASH_STATS(dict, hash)                                             \
    getHashStats(dict, defaults::UpperBucketCount, hash, STATS_DIR #hash ".csv")

/** @brief Prints stats in CSV format.
 *
 *  @param dict Test dictionary.
 *  @param hash Pointer to tested hash function.
 *  @param name File name to open.
 *
 *  @return `false` in case of any failure.
 */
bool getHashStats(Dict dict, size_t bucketCount, Hash* hash, const char* name);

#endif  // HASHMAP_BENCHMARK_H_
