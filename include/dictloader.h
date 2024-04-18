/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_DICTLOADER_H_
#define HASHMAP_DICTLOADER_H_

#include <stddef.h>

#include <sys/mman.h>

#include "hashmap.h"

struct FileBuffer {
    char* data;
    size_t size;
};

class Dict {
    FileBuffer buf_;
    char (*keys_)[defaults::MaxKeySize];
    size_t capacity_;

   public:
    bool loadFromFile(const char* filename);
    bool toHashMap(HashMap* map);

    size_t capacity() { return capacity_; }
    char* operator[](size_t i) { return keys_[i]; }

    void destroy() {
        munmap(buf_.data, buf_.size);
        free(keys_);
    };
};

#endif  // HASHMAP_DICTLOADER_H_
