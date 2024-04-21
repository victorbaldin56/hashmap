#!/bin/bash

VERSION=v2
BUILD_DIR=RelWithDebInfo
TARGET_EXEC=$BUILD_DIR/hashtest
PERF_DIR=stats/lookup
PERF_DATA="${PERF_DIR}/perf_${VERSION}.data"

sudo perf record -g -T --running-time --call-graph dwarf --output=$PERF_DATA -e cache-references,cache-misses,instructions,cycles \
-F 99 $TARGET_EXEC
sudo chmod +r $PERF_DATA
hotspot $PERF_DATA
