/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "bucket.h"
#include "hash.h"

class HashMap {
    size_t bucketCount_;
    Bucket* buckets_;
    Hash* hash_;

   public:
    struct InsertResult {
        bool is_inserted;
        Value* valptr;
    };

    bool create(size_t bucketCount_, Hash* hash);
    size_t bucketCount() { return bucketCount_; }
    size_t bucketSize(size_t i) { return buckets_[i].size(); }

    InsertResult insert(const char key[], Value value) {
        Bucket* bucket = buckets_ + (*hash_)(key) % bucketCount_;
        Value* valptr = bucket->find(key);
        if (valptr)
            return {false, valptr};

        valptr = bucket->pushFront(key, value);
        if (!valptr)
            return {false, nullptr};

        return {true, valptr};
    };

    Value* find(const char key[]);
    void destroy();
};

#endif  // HASHMAP_H_
