# fm_index
compiling:
```
g++ -std=c++11 -O2 -I/usr/local/include -L/usr/local/lib  bwooc.cpp  -lsdsl -ldivsufsort -ldivsufsort64 -o bwooc
```
running:
```
./bwocc build <input string> <output file>
./bwocc build2 <input file> <output file>
./bwocc query <saved fmindex file> <query patterns file>
```


