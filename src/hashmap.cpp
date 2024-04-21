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

HashMap::Value* HashMap::Bucket::insertAfter(Node* node, const char key[],
                                             unsigned value) {
    assert(node);

    Node* new_node = (Node*)malloc(sizeof(*new_node));
    if (!new_node)
        return nullptr;

    ++size_;
    strncpy(new_node->key, key, defaults::MaxKeySize);
    new_node->value = value;
    new_node->next = node->next;
    node->next = new_node;
    return &new_node->value;
}

void HashMap::Bucket::destroy() {
    for (Node* node = head(); node != tail();) {
        Node* tmp = node->next;
        free(node);
        node = tmp;
    }
}
