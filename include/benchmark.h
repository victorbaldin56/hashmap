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

#define GET_HASH_TIME(dict, hash, output) getHashTime(dict, hash, output, #hash)

#define REPORTS_DIR "reports/"

/** @brief Prints stats in CSV format.
 *
 *  @param dict Test dictionary.
 *  @param hash Pointer to tested hash function.
 *  @param name Filename to open.
 *
 *  @return `false` in case of any failure.
 */
bool getHashStats(Dict dict, size_t bucketCount, Hash* hash, const char* name);

void getHashTime(Dict dict, Hash* hash, FILE* output, const char* name);
bool benchmarkLookup(Dict dict, const char* reportName);

#endif  // HASHMAP_BENCHMARK_H_
