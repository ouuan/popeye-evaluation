Evaluation for [qingkaishi/netlifter](https://github.com/qingkaishi/netlifter)[^netlifter] and [zmw12306/ParDiff](https://github.com/zmw12306/ParDiff)[^pardiff].

[^netlifter]: [Lifting Network Protocol Implementation to Precise Format Specification with Security Applications](https://dl.acm.org/doi/10.1145/3576915.3616614)
[^pardiff]: [ParDiff: Practical Static Differential Analysis of Network Protocol Parsers](https://dl.acm.org/doi/10.1145/3649854)

Environment is set up as Docker containers with utility scripts in the [`justfile`](./justfile).

## Get Started

```sh
just build
just popeye tests/test/foo
just pardiff tests/test/foo tests/test/bar
```

See results in the `output` directory.

## Test Case Organization

-   Each test case should be organized in a directory in `tests` that can be built with `make main.o`.
-   Use `$(CC)` and `$(CXX)` instead of `gcc` and `g++` in the Makefile.
-   ParDiff and popeye interfaces are unified so that the same test case code can be used in both tools. Use `popeye_make_*` instead of `pardiff_make_*`. Use `popeye_main` instead of `pardiff_main_message` as entry point.
