# Homework
Course: Algorithms, Data Structures and Inference for High-Throughput Genomics
Fall 2020 - UMD

CMSC858D Homework 1 : Implementing some succinct primitives and FM-index search


https://rob-p.github.io/CMSC858D_F20/assignments/02_homework_01
# libraries
we need to use a dynamic sized bit vector for our rank/select  
c++ standard libraries are not enough for our case:
- `vector<bool>` doesn't have bitwise operators
- `bitset<SIZE>` needs to have a compile-fixed time size

`boost/dynamic_bitset` is a good substitute. But boost is a big libraries and we only need to use 

installing boost:
```
sudo apt-get install libboost-all-dev
```
getting header files for `dynamic_bitset`
```
bcp dynamic_bitset.hpp lib/ --boost=/usr/include/
```

*sdsl* `bit_vector` and `csa_wt.bwt` has been used in implementing the clasess  
We need to install `sdsl` library:
```
git clone https://github.com/simongog/sdsl-lite.git
cd sdsl-lite
sudo ./install.sh /usr/local/
```
## data
Magneto (Magnetospirillum) bacteria genome has been downloaded from NCBI RefSeq

## bit vector
bit vector is implemented in `bit_vector.hpp` using `sdsl/bit_vector`
