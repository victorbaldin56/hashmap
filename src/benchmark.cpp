/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "benchmark.h"

#include <errno.h>
#include <stdio.h>

#include <chrono>

#include "stats.h"

#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

static void benchmarkLookupOnSize(Dict dict, size_t bucketCount, FILE* output);

#if 0
bool getHashStats(Dict dict, size_t bucketCount, Hash* hash, const char* name) {
    assert(hash);

    FILE* output = fopen(name, "w");
    if (!output) {
        fprintf(stderr, "Failed to open file %s: %s\n", name, strerror(errno));
        return false;
    }

    HashMap map;
    map.create(bucketCount, hash);
    dict.toHashMap(&map);

    fprintf(output, "num,load\n");
    for (size_t i = 0; i < map.bucketCount(); ++i)
        fprintf(output, "%zu,%zu\n", i, map.bucketSize(i));

    fclose(output);

    map.destroy();
    return true;
}

bool benchmarkHash(Dict dict, Hash* hash, const char* name) {
    assert(hash);

    FILE* output = fopen(name, "w");
    if (!output) {
        fprintf(stderr, "Failed to open file %s: %s\n", name, strerror(errno));
        return false;
    }

    fprintf(output, "time\n");

    for (unsigned i = 0; i < defaults::NumHashMeasures; ++i) {
        auto begin = std::chrono::high_resolution_clock::now();
        for (size_t k = 0; k < defaults::NumHashRepeats; ++k) {
            for (size_t j = 0; j < dict.capacity(); ++j) {
                (*hash)(dict[j]);
            }
        }
        auto end = std::chrono::high_resolution_clock::now();

        fprintf(
            output, "%ld\n",
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                    .count() /
                defaults::NumHashRepeats);
    }

    fclose(output);
    return true;
}
#endif

bool benchmarkLookup(Dict dict, const char* name) {
    FILE* output = fopen(name, "w");
    if (!output) {
        fprintf(stderr, "Failed to open file %s: %s\n", name, strerror(errno));
        return false;
    }

    fprintf(output, "{\"time\": [\n");

    HashMap map;
    map.create(defaults::UpperBucketCount);

    dict.toHashMap(&map);

    long times[defaults::NumLookupMeasures] = {};

    for (unsigned j = 0; j < defaults::NumLookupMeasures; ++j) {
        auto begin = std::chrono::high_resolution_clock::now();
        for (size_t k = 0; k < defaults::NumLookupRepeats; ++k) {
            for (size_t i = 0; i < dict.capacity(); ++i) {
                [[maybe_unused]] unsigned* value = map.find(dict[i]);
                // Compile in Debug to enable test
                assert(value && "Word in dictionary not found");
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        long nsec =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                .count() /
            defaults::NumLookupRepeats;
        times[j] = nsec;
        if (j < defaults::NumLookupMeasures - 1)
            fprintf(output, "%ld,\n", nsec);
        else
            fprintf(output, "%ld],\n", nsec);
    }

    fprintf(output,
            "\"avg\": %ld,\n"
            "\"stddev\": %ld}",
            stats::mean(times, defaults::NumLookupMeasures),
            stats::stddev(times, defaults::NumLookupMeasures));

    map.destroy();
    fclose(output);
    return true;
}

bool benchmarkLookupOnAllSizes(Dict dict, const char* name) {
    FILE* output = fopen(name, "w");
    if (!output) {
        fprintf(stderr, "Failed to open file %s: %s\n", name, strerror(errno));
        return false;
    }

    fprintf(output, "size,time,stddev\n");

    for (unsigned i = 0; i < ARRAY_SIZE(defaults::HashMapSizes); ++i)
        benchmarkLookupOnSize(dict, defaults::HashMapSizes[i], output);

    fclose(output);
    return true;
}

static void benchmarkLookupOnSize(Dict dict, size_t bucketCount,
                                  FILE* output) {
    assert(output);

    HashMap map;
    map.create(bucketCount);
    dict.toHashMap(&map);

    long times[defaults::NumLookupMeasures] = {};

    for (unsigned j = 0; j < defaults::NumLookupMeasures; ++j) {
        auto begin = std::chrono::high_resolution_clock::now();
        for (size_t k = 0; k < defaults::NumLookupRepeats; ++k) {
            for (size_t i = 0; i < dict.capacity(); ++i) {
                [[maybe_unused]] unsigned* value = map.find(dict[i]);
                // Compile in Debug to enable test
                assert(value && "Word in dictionary not found");
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        long nsec =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
                .count() /
            defaults::NumLookupRepeats;
        times[j] = nsec;
    }

    fprintf(output, "%zu,%ld,%ld\n", bucketCount,
            stats::mean(times, defaults::NumLookupMeasures),
            stats::stddev(times, defaults::NumLookupMeasures));

    map.destroy();
}
