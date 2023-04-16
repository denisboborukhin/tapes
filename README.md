Tape
===
Tape data is stored as a byte file containing a set of items.


To sort tapes with limited memory usage, temporary sorted tapes are created first, and then they are merged into a sorted tape. 

Requirements
===
The following applications have to be installed:
- CMake 3.16.2 version (or higher)
- GTest
- clang++

How to build
===
To compile you need to use сmake in the directory build:
```
mkdir build
cd build
сmake ..
```
To compile tests:
```
make tapes_tests
```
To compile main program:
```
make sort_tapes
```
To compile all:
```
make
```

Running
===
To run tests:
```
make run_tapes_tests
```

To run main programm:
```
make run_sort_tapes
```
