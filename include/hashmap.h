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

class HashMap {
    typedef unsigned Value;

    class Bucket {
        struct Node {
            char key[defaults::MaxKeySize];
            Value value;
            Node* next;
        };

        Node fakeHead_;
        size_t size_;

       public:
        void create() {
            size_ = 0;
            fakeHead_.next = &fakeHead_;
        }

        size_t size() const { return size_; }
        Node* head() const { return fakeHead_.next; }
        const Node* tail() const { return &fakeHead_; }

        Value* insertAfter(Node* node, const char key[], unsigned value);

        Value* pushFront(const char key[], unsigned value) {
            return insertAfter(&fakeHead_, key, value);
        }

        Value* find(const char key[]) const {
            for (Node* node = head(); node != tail(); node = node->next) {
                if (strcmp(node->key, key) == 0)
                    return &node->value;
            }

            return nullptr;
        }

        void destroy();
    };

    size_t bucketCount_;
    Bucket* buckets_;
    Hash* hash_;

   public:
    struct InsertResult {
        bool isInserted;
        Value* valptr;
    };

    bool create(size_t bucketCount, Hash* hash);
    size_t bucketCount() const { return bucketCount_; }
    size_t bucketSize(size_t i) const { return buckets_[i].size(); }

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

    Value* find(const char key[]) const;
    void destroy();
};

#endif  // HASHMAP_H_
