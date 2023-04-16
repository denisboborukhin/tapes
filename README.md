Tape
===
This project is a task on course "Uses and applications of C++ language" by K.I.Vladimirov. The task was to implement a class representing matrix.
My matrix calculate determinant with partial and full pivoting.

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
