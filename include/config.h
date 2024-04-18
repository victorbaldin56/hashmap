/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_CONFIG_H_
#define HASHMAP_CONFIG_H_

#include <stddef.h>

namespace defaults {

const unsigned MaxKeySize = 32;

// Should be prime numbers.
const size_t UpperBucketCount = 2027;
const size_t LowerBucketCount = 101;

}  // namespace defaults

#endif  // HASHMAP_CONFIG_H_
