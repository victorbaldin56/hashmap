/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "hashmap.h"

#include <assert.h>

bool HashMap::create(size_t bucketCount, Hash* hash) {
    assert(hash);

    buckets_ = (Bucket*)malloc(bucketCount * sizeof(*buckets_));
    if (!buckets_)
        return false;

    for (size_t i = 0; i < bucketCount; ++i)
        buckets_[i].create();

    hash_ = hash;
    bucketCount_ = bucketCount;
    return true;
}

Value* HashMap::find(const char key[]) {
    assert(key);

    Bucket* bucket = buckets_ + (*hash_)(key) % bucketCount_;
    return bucket->find(key);
}

void HashMap::destroy() {
    for (size_t i = 0; i < bucketCount_; ++i)
        buckets_[i].destroy();

    free(buckets_);
}
