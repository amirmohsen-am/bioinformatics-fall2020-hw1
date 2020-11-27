# select_support
rank_support class is implemented in header `rank_support.hpp`  
compiling and running:
```
g++ -std=c++11 -DNDEBUG -O3 -I/usr/local/include -L/usr/local/lib \
run_select.cpp -lsdsl -ldivsufsort -ldivsufsort64 && ./a.out
```
`run_select.cpp` takes one string consisting of '0' and '1's as input. And then constructs the tables needed. Then it will test all the possible queries to see if rank is working properly.  
Then in each line it will get a query x and print `select1(x)` (0 based index)

sample input:
```
1001011101001010
1
2
3   

```
sample output:
```
testing select_support on bitvector size: 16
test passed
overhead: 40
select1(1) = 0
select1(2) = 3
select1(3) = 5
```


some changes to function parameter format:
```
select_support.save(ofstream& fout);
select_support.load(ofstream& fout);
```
