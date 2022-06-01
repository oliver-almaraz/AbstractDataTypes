# Abstract Data Types
Header files, source code and examples for abstract datatypes implemented entirely in C.

## How to use these libraries
**You will find most of the information you need in the header files located under `AbstractDataTypes/include` .**

If you're new to C, remember that you must compile and link the source code of the library. It's up to you to write a makefile and/or to make sure that your compiler can find the files and objects you decide to include.

### A simple way of compiling an linking the examples provided in this repository using gcc on a Linux distro:

Compile the lib:
```
$ cd AbstractDataTypes/source
$ gcc -I ../include -c LinkedList.c -o LinkedList.o
```
Compile and link with the example program:
```
$ cd ../examples
$ gcc -I ../include ListExample.c ../source/LinkedList.o -o ListExample

```
Run the program:

```
$ ./ListExample

```

## About
I created these libraries a while ago for learning data structures and their public interfaces.
They had been lying around among other long-forgotten, unfinished projects until I recently started programming again.
Since some of my new projects require the use of some of the abstract datatypes for which I had already written some libs, I committed myself to writing cleaner, simpler and self-explaining versions to make them a lot easier to include and use.

Since these libraries were made for my own personal use, I often **preferred simplicity over abstraction**. You therefore might need to modify these libs to either make them match your specific implementation or to make them more abstract, if you consider it's worth the hassle.
However, I trust they will be adequate for most of the implementations out there.

## References
I used as references for writing these libraries mainly Kyle Loudon's **"Mastering Algorithms with C"** and Richard Reese's **"Understanding and Using C Pointers"**, both published by O'Reilly & Associates.
