/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "bucket.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

Value* Bucket::insertAfter(BucketNode* node, const char key[], unsigned value) {
    assert(node);

    BucketNode* new_node = (BucketNode*)malloc(sizeof(*new_node));
    if (!new_node)
        return nullptr;

    ++size_;
    strncpy(new_node->key, key, defaults::MaxKeySize);
    new_node->value = value;
    new_node->next = node->next;
    node->next = new_node;
    return &new_node->value;
}

void Bucket::destroy() {
    for (BucketNode* node = head(); node != tail();) {
        BucketNode* tmp = node->next;
        free(node);
        node = tmp;
    }
}
