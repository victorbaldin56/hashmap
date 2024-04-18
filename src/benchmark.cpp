/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "benchmark.h"

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#include <immintrin.h>

inline uint64_t square(uint64_t x) {
    return x * x;
}

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

bool benchmarkLookup(Dict dict, const char* reportName) {
    assert(reportName);

    FILE* output = fopen(reportName, "w");
    if (!output) {
        fprintf(stderr, "Failed to open file %s: %s\n", reportName,
                strerror(errno));
        return false;
    }

    fprintf(output, "{\"elapsed_times\": [\n");

    HashMap map;
    map.create(defaults::UpperBucketCount, hash::crc32);

    dict.toHashMap(&map);

    uint64_t mean = 0;
    uint64_t dev = 0;
    uint64_t times[defaults::NumLookupMeasures] = {};

    for (unsigned k = 0; k < defaults::NumLookupMeasures; ++k) {
        uint64_t begin = __rdtsc();
        for (unsigned j = 0; j < defaults::NumLookupRepeats; ++j) {
            for (size_t i = 0; i < dict.capacity(); ++i) {
                map.find(dict[i]);
            }
        }
        uint64_t end = __rdtsc();
        times[k] = end - begin;
        mean += times[k];

        if (k < defaults::NumLookupMeasures - 1)
            fprintf(output, "%zu,\n", times[k]);
        else
            fprintf(output, "%zu\n", times[k]);
    }

    mean /= defaults::NumLookupMeasures;

    for (unsigned i = 0; i < defaults::NumLookupMeasures; ++i) {
        dev += square(times[i] - mean);
    }

    dev /= defaults::NumLookupMeasures;
    dev = (uint64_t)sqrt(dev);

    fprintf(output,
            "],\n"
            "\"mean_time\": %zu,\n"
            "\"stdev\": %zu}",
            mean, dev);

    return true;
}
