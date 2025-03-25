#!/bin/bash

set -euo pipefail

if [[ $# != 1 ]]; then
    echo "Usage: $0 <path-to-test>"
    exit 1
fi

. "$HOME/.cargo/env"

export CC=wllvm
export CXX=wllvm++
export LLVM_COMPILER=clang
export PATH="/usr/lib/llvm-12/bin:$PATH"

cd "/$1"
echo "Building $1"
if [[ -f Cargo.toml ]]; then
    RUSTFLAGS="--emit=llvm-bc" cargo build --release
    llvm-link target/release/deps/*.bc > main.a.bc
else
    make main.a
    extract-bc -b main.a
fi

echo "Running popeye"
popeye main.a.bc -popeye-entry=popeye_main -popeye-output=bnf >/output/stdout.txt 2>/output/stderr.txt
