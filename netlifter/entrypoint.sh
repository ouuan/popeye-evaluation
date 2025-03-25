#!/bin/bash

set -euo pipefail

if [[ $# != 1 ]]; then
    echo "Usage: $0 <path-to-test>"
    exit 1
fi

export CC=wllvm
export CXX=wllvm++
export LLVM_COMPILER=clang
export PATH="/usr/lib/llvm-12/bin:$PATH"

cd "/$1"
echo "Building $1"
if ! make main.o.bc; then
    make main.o
    extract-bc main.o
fi

echo "Running popeye"
popeye main.o.bc -popeye-entry=popeye_main -popeye-output=bnf >/output/stdout.txt 2>/output/stderr.txt
