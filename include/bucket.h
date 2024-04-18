/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_BUCKET_H_
#define HASHMAP_BUCKET_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "config.h"

typedef unsigned Value;

struct BucketNode {
    char key[defaults::MaxKeySize];
    Value value;
    BucketNode* next;
};

class Bucket {
    BucketNode fakeHead_;
    size_t size_;

   public:
    void create() {
        size_ = 0;
        fakeHead_.next = &fakeHead_;
    }

    size_t size() { return size_; }
    BucketNode* head() { return fakeHead_.next; }
    BucketNode* tail() { return &fakeHead_; }

    Value* insertAfter(BucketNode* node, const char key[], unsigned value);

    Value* pushFront(const char key[], unsigned value) {
        return insertAfter(&fakeHead_, key, value);
    }

    Value* find(const char key[]) {
        for (BucketNode* node = head(); node != tail(); node = node->next) {
            if (strcmp(node->key, key) == 0)
                return &node->value;
        }

        return nullptr;
    }

    void destroy();
};

#endif  // HASHMAP_BUCKET_H_
