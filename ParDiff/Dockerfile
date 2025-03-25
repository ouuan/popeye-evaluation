FROM debian:11-slim AS llvm

RUN apt-get update
RUN apt-get install -y wget gnupg
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN echo 'deb https://apt.llvm.org/bullseye llvm-toolchain-bullseye-12 main' >> /etc/apt/sources.list
RUN apt-get update
RUN apt-get install -y llvm-12

FROM llvm AS build-z3

RUN apt-get install -y g++ make cmake git zlib1g-dev

ENV CC=/usr/bin/gcc
ENV CXX=/usr/bin/g++

RUN git clone https://github.com/zmw12306/z3 /z3
RUN cmake -S /z3 -B /z3/build
RUN cmake --build /z3/build -j$(nproc)
RUN cmake --install /z3/build --prefix /usr/local

FROM build-z3 AS build

WORKDIR /src
COPY include include
COPY lib lib
COPY tools tools
COPY CMakeLists.txt .
RUN cmake -S . -B build
RUN cmake --build build -j$(nproc)

FROM llvm

RUN apt-get install -y python3 python3-pip clang-12 file
RUN pip install wllvm

# 1.55.0 is the last version with LLVM 12
RUN wget -qO- https://sh.rustup.rs | sh -s -- -y --default-toolchain 1.55.0 --profile minimal

COPY --from=build-z3 /usr/local/lib/libz3.so.4.8 /usr/local/lib
COPY --from=build /src/build/bin/* /usr/local/bin/

COPY --chmod=0755 entrypoint.sh /

ENTRYPOINT [ "/entrypoint.sh" ]
