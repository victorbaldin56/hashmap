/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "hash.h"

#include <string.h>

uint64_t hash::zero([[maybe_unused]] const char key[]) {
    return 0;
}

uint64_t hash::strlen(const char key[]) {
    return ::strlen(key);
}

uint64_t hash::firstChar(const char key[]) {
    return (uint64_t)key[0];
}

uint64_t hash::sum(const char key[]) {
    uint64_t sum = 0;

    for (; *key; ++key)
        sum += (unsigned char)*key;

    return sum;
}

uint64_t hash::ror(const char key[]) {
    uint64_t hash = 0;

    for (; *key; ++key)
        hash = ((hash >> 1) | (hash << 63)) + (unsigned char)*key;

    return hash;
}

uint64_t hash::rol(const char key[]) {
    uint64_t hash = 0;

    for (; *key; ++key)
        hash = ((hash << 1) | (hash >> 63)) + (unsigned char)*key;

    return hash;
}

uint64_t hash::crc32(const char key[]) {
    uint32_t crc = 0xffffffff;
    uint32_t mask = 0;

    for (; *key; ++key) {
        crc ^= (unsigned char)*key;
        for (int i = 7; i >= 0; --i) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xedb88320 & mask);
        }
    }

    return ~crc;
}

uint64_t hash::gnu(const char key[]) {
    uint64_t hash = 5381;

    for (; *key; ++key) {
        hash = ((hash << 5) + hash) + (unsigned char)*key;
    }

    return hash;
}
