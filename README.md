# libraries
we need to use a dynamic sized bit vector for our rank/select  
c++ standard libraries are not enough for our case:
- `vector<bool>` doesn't have bitwise operators
- `bitset<SIZE>` needs to have a compile-fixed time size

`boost/dynamic_bitset` is a good substitute. But boost is a big libraries and we only need to use 
