#!/bin/bash

VERSION=v1
BUILD_DIR=RelWithDebInfo
TARGET_EXEC=$BUILD_DIR/hashtest
PERF_DIR=reports
PERF_DATA="${PERF_DIR}/perf_${VERSION}.data"
PERF_SCRIPT="${PERF_DIR}/perf_${VERSION}.script"
FLAMEGRAPH="${PERF_DIR}/flamegraph_${VERSION}.svg"

sudo perf record -g -T --running-time --call-graph dwarf --output=$PERF_DATA -F 99 $TARGET_EXEC
sudo perf script -i $PERF_DATA > $PERF_SCRIPT
FlameGraph/stackcollapse-perf.pl $PERF_SCRIPT | FlameGraph/flamegraph.pl > $FLAMEGRAPH
