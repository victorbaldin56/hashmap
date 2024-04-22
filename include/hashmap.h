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
#include <string.h>

#include "config.h"
#include "hash.h"

typedef __m256 Key;
typedef unsigned Value;

extern "C" int strcmp_aligned32_noinline(const Key* str1, const Key* str2);

class HashMap {
    class Bucket {
        // Cache-friendly
        Key* keys_;
        Value* values_;
        size_t* next_;
        size_t free_;

        size_t size_;
        size_t capacity_;

       public:
        bool create();

        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }

        size_t head() const { return next_[0]; }

        bool reserve(size_t newCapacity);

        Value* insertAfter(size_t index, const __m256* key, unsigned value);

        Value* pushFront(const Key* key, unsigned value) {
            return insertAfter(0, key, value);
        }

        Value* find(const Key* key) const {
            for (size_t i = head(); i != 0; i = next_[i]) {
                if (strcmp_aligned32_noinline((keys_ + i), key) == 0)
                    return values_ + i;
            }

            return nullptr;
        }

        void destroy();
    };

    size_t bucketCount_;
    Bucket* buckets_;

   public:
    struct InsertResult {
        bool isInserted;
        Value* valptr;
    };

    bool create(size_t bucketCount);
    size_t bucketCount() const { return bucketCount_; }
    size_t bucketSize(size_t i) const { return buckets_[i].size(); }

    InsertResult insert(const Key* key, Value value) {
        Bucket* bucket = buckets_ + hash::crc32_sse(key) % bucketCount_;
        Value* valptr = bucket->find(key);
        if (valptr)
            return {false, valptr};

        valptr = bucket->pushFront(key, value);
        if (!valptr)
            return {false, nullptr};

        return {true, valptr};
    };

    Value* find(const Key* key) const;
    void destroy();
};

#endif  // HASHMAP_H_
