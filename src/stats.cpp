/** @file
 *  @brief
 *
 *  @copyright (C) Victor Baldin, 2024.
 */

#include "stats.h"

#include <math.h>

long stats::mean(long arr[], size_t len) {
    long sum = 0;
    for (size_t i = 0; i < len; ++i)
        sum += arr[i];
    return sum / (long)len;
}

long stats::stddev(long arr[], size_t len) {
    long avg = mean(arr, len);
    long dev = 0;

    for (size_t i = 0; i < len; ++i)
        dev += (arr[i] - avg) * (arr[i] - avg);

    dev /= len;
    dev = (long)sqrt(dev);
    return dev;
}
