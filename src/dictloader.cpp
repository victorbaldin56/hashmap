/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "dictloader.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>

#include <fcntl.h>
#include <sys/stat.h>

// #define DEBUG

#ifdef DEBUG
#define DEBUG_LOG(...) fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif

inline size_t getFileSize(int fd) {
    struct stat st;
    fstat(fd, &st);
    return (size_t)st.st_size;
}

static FileBuffer mapFile(const char* filename);
static size_t countLines(const char* data);

bool Dict::loadFromFile(const char* filename) {
    assert(filename);

    buf_ = mapFile(filename);
    if (!buf_.data)
        return false;

    size_t cnt = countLines(buf_.data);

    // For alignment optimizations in future.
    keys_ = (char(*)[defaults::MaxKeySize])malloc(cnt * defaults::MaxKeySize);
    if (!keys_) {
        fprintf(stderr, "Failed to allocate memory\n");
        return false;
    }

    capacity_ = cnt;

    char* key = buf_.data;
    for (size_t i = 0; (size_t)(key - buf_.data) < buf_.size; ++i) {
        char* tmp = strchr(key, '\n');
        if (!tmp)
            break;
        *tmp = '\0';
        strncpy(keys_[i], key, defaults::MaxKeySize);
        key = tmp;
        ++key;
    }

    return true;
}

bool Dict::toHashMap(HashMap* map) {
    assert(map);

    for (size_t i = 0; i < capacity_; ++i) {
        DEBUG_LOG("%s: ", keys_[i]);

        HashMap::InsertResult res = map->insert(keys_[i], 1);
        if (!res.isInserted) {
            if (!res.valptr) {
                fprintf(stderr, "Failed to allocate node in bucket\n");
                return false;
            }

            // Increase number of occurencies.
            ++*res.valptr;
        }

        DEBUG_LOG("%u\n", *res.valptr);
    }

    return true;
}

static FileBuffer mapFile(const char* filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Failed to open file %s: %s\n", filename,
                strerror(errno));
        return {.data = nullptr};
    }

    size_t size = getFileSize(fd);
    char* mem =
        (char*)mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    if (mem == MAP_FAILED) {
        fprintf(stderr, "Failed to map memory\n");
        return {.data = nullptr};
    }

    return {.data = mem, .size = size};
}

static size_t countLines(const char* data) {
    assert(data);

    size_t cnt = 0;
    --data;

    for (; (data = strchr(data + 1, '\n')); ++cnt) {}
    return cnt;
}
