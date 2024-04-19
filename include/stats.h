/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#ifndef HASHMAP_STATS_H_
#define HASHMAP_STATS_H_

#include <stddef.h>

namespace stats {

long mean(long arr[], size_t len);
long stddev(long arr[], size_t len);

}  // namespace stats

#endif  // HASHMAP_STATS_H_
