#!/bin/bash

set -euo pipefail

if [[ $# == 0 ]]; then
    echo "Usage: $0 <path-to-test> [other popeye options ...]"
    exit 1
fi

. "$HOME/.cargo/env"

export CC=wllvm
export CXX=wllvm++
export LLVM_COMPILER=clang
export PATH="/usr/lib/llvm-12/bin:$PATH"
export CFLAGS='-g -O0 -fno-vectorize -fno-slp-vectorize'
export CXXFLAGS="$CFLAGS"
export RUSTFLAGS="-g -C llvm-args=-vectorize-slp=false -C llvm-args=-vectorize-loops=false --emit=llvm-bc"

cd "/$1"
echo "Building $1"
if [[ -f Cargo.toml ]]; then
    cargo build --release
    llvm-link target/release/deps/*.bc > main.a.bc
else
    make main.a
    extract-bc -b main.a
fi

output="/output/${1#tests/}"
name=$(basename "$1")
rm -rf "$output"
mkdir -p "$output"
cp main.a.bc "$output"
cd "$output"
echo "Running popeye"
popeye main.a.bc \
    -popeye-entry=popeye_main \
    -popeye-output=dot:"$name".dot \
    -popeye-output=bnf \
    "${@:2}" \
    2>"$name.err" | tee "$name.log"
