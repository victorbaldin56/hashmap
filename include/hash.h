/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_HASH_H_
#define HASHMAP_HASH_H_

#include <stdint.h>

typedef uint64_t Hash(const char key[]);

namespace hash {

Hash zero;
Hash strlen;
Hash firstChar;
Hash sum;
Hash ror;
Hash rol;
Hash crc32;

}  // namespace hash

#endif  // HASHMAP_HASH_H_
