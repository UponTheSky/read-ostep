# Interlude: Memory API
- the memory allocation interfaces in UNIX systems

## 1. Types of Memory
1. **stack** memory: allocation/deallocation are managed *implicitly* by the compiler
  - live inside the scope of a function
  - allocates memory when a variable is defined in a function scope, and deallocates it when the function ends and is returned
  - short-lived

2. **heap** memory: allocation/deallocation are managed *explicitly** by a programmer

## 2. The malloc() Call
- convention: 
  - not directly passing a certain number as the function argument to the function
  - rather, use macros like `sizeof`(compile-time operator, not a function call at run time)
  - `sizeof`: returning the expected size of an array(not for pointers though)
  - string: `strlen(s) + 1`(for the end-of-string char)

- returning `void*`: just an address, and it is the programmer who will choose what to do with it

## 3. The free() call
- the size of the allocated region is not passed in by the user
- must be tracked by the memory-allocation library itself

## 4. Common Errors
- almost not catchable by the compiler
- **garbage collector**

### forgetting to allocate memory
- example: `strcpy` without `dst` being allocated
- **segmentation fault**

### not allocating enough memory
- **buffer overflow**
- in some cases, it is harmless, but in other cases, it could be very harmful
- could be the source of many security vulnerabilities in systems
- even though it ran correctly once, doesn't mean it's correct

### forgetting to initialize allocated memory
- if you forget to fill in some data, it may cause an **uninitialized read**
  - it reads from the heap some data of unknown value

### forgetting to free memory
- **memory leak**: forgetting to free memory
- even slowly leaking memory eventually leads to running out of memory: a huge problem for long running programs or the OS

### freeing memory before you're done with it
- **dangling pointer**: you free a variable before it is used
- crashing a program or overwriting valid memory

### freeing memory repeatedly
- **double free**: freeing memory more than once
- undefined results: program crash(typically)

### calling free() incorrectly
- **invalid malloc**: `free` expects to be passed to an argument that is returned from `malloc`

### summary
- use valgrind!

## 5. Underlying OS Support
- `malloc` and `free` are library calls, and manages space within a virtual address space
- but inside them are several syscalls related to memory management: `brk`, `sbrk`
- stick to `malloc` and `free` rather than directly calling syscalls like `brk`
- `mmap`: create an anonymous memory region within a program  
  - a region not associated with any particular file but rather with **swap space**
  - can be treated like a heap

## 6. Other Calls
- `calloc`, `realloc`

## HW
1. gets a segmentation fault

2. with the message of segfault, it also shows an address, line in which that crash occured, and also the name of the signal sent to the process to stop it

- I couldn't do more since valgrind is unavailable in macOS and (currently)AWS EC2
