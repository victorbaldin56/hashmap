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
const size_t UpperBucketCount = 2741;
const size_t LowerBucketCount = 101;

// For hashing time measurements
const unsigned NumHashMeasures = 100;
const unsigned NumHashRepeats = 10;

// For lookup time measurements
const unsigned NumLookupMeasures = 100;
const unsigned NumLookupRepeats = 10;

}  // namespace defaults

#endif  // HASHMAP_CONFIG_H_
