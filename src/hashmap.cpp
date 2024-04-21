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

    for (size_t i = 0; i < bucketCount; ++i) {
        if (!buckets_[i].create()) {
            for (size_t j = 0; j < i; ++j)
                buckets_[j].destroy();

            free(buckets_);
            return false;
        }
    }

    hash_ = hash;
    bucketCount_ = bucketCount;
    return true;
}

HashMap::Value* HashMap::find(const char key[]) const {
    assert(key);

    Bucket* bucket = buckets_ + (*hash_)(key) % bucketCount_;
    return bucket->find(key);
}

void HashMap::destroy() {
    for (size_t i = 0; i < bucketCount_; ++i)
        buckets_[i].destroy();

    free(buckets_);
}

bool HashMap::Bucket::create() {
    // clang-format off
            keys_ = (Key*)aligned_alloc(defaults::MaxKeySize, sizeof(*keys_));
            values_ = (Value*)malloc(sizeof(*values_));
            next_ = (size_t*)malloc(sizeof(*next_));
    // clang-format on
    if (!next_ || !values_ || !keys_) {
        free(next_);
        free(values_);
        free(keys_);
        return false;
    }

    size_ = 0;
    capacity_ = 1;
    next_[0] = 0;
    free_ = 0;

    return true;
}

bool HashMap::Bucket::reserve(size_t newCapacity) {
    if (newCapacity <= capacity_)
        return true;

    Key* newKeys = (Key*)aligned_alloc(defaults::MaxKeySize,
                                       newCapacity * sizeof(*newKeys));
    Value* newValues =
        (Value*)realloc(values_, newCapacity * sizeof(*newValues));
    size_t* newNext = (size_t*)realloc(next_, newCapacity * sizeof(*newNext));
    if (!newKeys || !newValues || !newNext) {
        free(newKeys);
        free(newValues);
        free(newNext);
        return false;
    }

    memcpy(newKeys, keys_, capacity_ * sizeof(*keys_));
    free(keys_);

    keys_ = newKeys;
    values_ = newValues;
    next_ = newNext;

    free_ = capacity_;
    for (size_t i = capacity_; i < newCapacity - 1; ++i) {
        next_[i] = i + 1;
    }

    next_[newCapacity - 1] = 0;
    capacity_ = newCapacity;

    return true;
}

HashMap::Value* HashMap::Bucket::insertAfter(size_t index, const char key[],
                                             Value value) {
    if (size_ == capacity_ - 1) {
        if (!reserve(capacity_ * defaults::BucketGrowthFactor))
            return nullptr;
    }

    ++size_;
    strncpy(keys_[free_], key, defaults::MaxKeySize);
    values_[free_] = value;

    size_t tmpNextFree = next_[free_];
    next_[free_] = next_[index];
    next_[index] = free_;
    size_t tmpFree = free_;
    free_ = tmpNextFree;

    return values_ + tmpFree;
}

void HashMap::Bucket::destroy() {
    free(keys_);
    free(values_);
    free(next_);
}
