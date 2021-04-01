# XOREncryptor

Sample workload for the "[Examining Problematic Memory with BPF, Perf, and Memcheck](https://doordash.engineering/2021/04/01/examining-problematic-memory-with-bpf-perf-and-memcheck/)" article.

### Instructions
```
make
make data
./XOREncryptor
```

### Dependencies
[Boost](https://www.boost.org/), available as a package:
```
sudo apt-get install libboost-all-dev
```
or, by [compiling from source](https://www.boost.org/doc/libs/1_75_0/).
