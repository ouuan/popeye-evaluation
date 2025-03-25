#!/bin/bash

set -euo pipefail

if [[ $# != 2 ]]; then
    echo "Usage: $0 <path-to-test1> <path-to-test2>"
    exit 1
fi

export CC=wllvm
export CXX=wllvm++
export LLVM_COMPILER=clang
export PATH="/usr/lib/llvm-12/bin:$PATH"

bitcodes=()

for t in "/$1" "/$2"; do
    pushd "$t"
    echo "Building $t"
    if ! make main.a.bc; then
        if [[ -f Cargo.toml ]]; then
            RUSTFLAGS="--emit=llvm-bc" cargo build --release
            llvm-link target/release/deps/*.bc > main.a.bc
        else
            make main.a
            extract-bc -b main.a
        fi
    fi
    bitcodes+=("$(realpath main.a.bc)")
    popd
done

echo "Running ParDiff"
pardiff "${bitcodes[@]}" -pardiff-entry=popeye_main >/output/stdout.txt 2>/output/stderr.txt
