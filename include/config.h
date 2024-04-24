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
const unsigned NumLookupMeasures = 5;
const unsigned NumLookupRepeats = 50;

const unsigned BucketGrowthFactor = 2;

const size_t HashMapSizes[] = {13, 23, 41, 67,
                               101, 157, 251, 401, 643, 1021, 1637, 2741,
                               4211, 6659, 10723, 17167, 27427, 43889, 68899,
                               100003};

}  // namespace defaults

#endif  // HASHMAP_CONFIG_H_
