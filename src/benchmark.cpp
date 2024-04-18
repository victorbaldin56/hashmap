/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "benchmark.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>

#include <immintrin.h>

bool getHashStats(Dict dict, size_t bucketCount, Hash* hash, const char* name) {
    assert(hash);

    HashMap map;
    if (!map.create(bucketCount, hash)) {
        fprintf(stderr, "Hash map allocation failed\n");
        return false;
    }

    dict.toHashMap(&map);
    bool ret = true;

    FILE* output = fopen(name, "w");
    if (!output) {
        fprintf(stderr, "Failed to open file %s: %s\n", name, strerror(errno));
        ret = false;
        goto cleanup;
    }

    fprintf(output, "num,load\n");
    for (size_t i = 0; i < map.bucketCount(); ++i)
        fprintf(output, "%zu,%zu\n", i, map.bucketSize(i));

    fclose(output);

cleanup:
    map.destroy();
    return ret;
}

void getHashTime(Dict dict, Hash* hash, FILE* output, const char* name) {
    assert(hash);
    assert(fileno(output) > 0);

    fprintf(output, "%s", name);

    for (unsigned k = 0; k < defaults::NumHashMeasures; ++k) {
        uint64_t begin = __rdtsc();
        for (unsigned j = 0; j < defaults::NumHashRepeats; ++j) {
            for (size_t i = 0; i < dict.capacity(); ++i) {
                (*hash)(dict[i]);
            }
        }
        uint64_t end = __rdtsc();
        fprintf(output, ",%zu", end - begin);
    }

    fprintf(output, "\n");
}
