#!/usr/bin/env sh

set -e -o pipefail -x

BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

cmake -S ../ -B ./ -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
