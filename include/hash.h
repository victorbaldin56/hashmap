/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_HASH_H_
#define HASHMAP_HASH_H_

#include <stdint.h>

#include <immintrin.h>
namespace hash {

inline uint64_t crc32_sse(const __m256* key) {
    uint64_t crc = 0;

    // Цикл развернут вручную для гарантии
    crc = _mm_crc32_u64(crc, *(const uint64_t*)key + 0);
    crc = _mm_crc32_u64(crc, *(const uint64_t*)key + 1);
    crc = _mm_crc32_u64(crc, *(const uint64_t*)key + 2);
    crc = _mm_crc32_u64(crc, *(const uint64_t*)key + 3);

    return crc;
}

}  // namespace hash

#endif  // HASHMAP_HASH_H_
