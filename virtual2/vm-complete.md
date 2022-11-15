# Complete Virtual Memory Systems
- elements of vm: pagetable, TLB, eviction policy
- other elements for performance, functionality, and security
- VAX/VMS system
- Linux

## 1. VAX/VMS Virtual Memory
- an example of SW innovations used to hide some of the inherent flaws of the architecture
  - sometimes the HW designers don't quite get everything right

### Memory Management Hardware
- a hybrid of paging and segmentation
- process space(code, heap, stack) + system space(kernel code, data)
- problem: excessively large linear pagetable due to the small size of a page(512 bytes)
  - solution 1: segmenting the process space into two => no need to care for the unused space between the stack and the hep
  - solution 2: placing user page tables in kernel virtual memory + swapping pages for those page tables when necessary
  : system page table => user page table => translation(with some help from TLB)

### A Real Address Space
- page 0: inaccessible, providing some support for detecting *null-pointer* accesses
- the kernel virtual address space is a part of each user address space
  - on context switch, the same kernel structures are mapped into each user address space
  - for easy page swapping, data communication btw user space and kernel

- protection: the HW must support different protection levels for pages to enable r/w/x by a user

### Page Replacement
- page eviction problem:
  - no use(reference) bit for eviction policy 
  - memory hog(a program consuming too much memory)

- solution: *segmented FIFO* replacement policy
  - performs similar to LRU

- optimization: clustering for disk i/o

### Other Neat Tricks
- lazy optimizations: demanding zeroing / COW

- **demand zeroing** of pages
  - a page could be demanded by a process, with zeroing the page
  - but it is costly if that page will not be used
  - so instead, OS does the following
    - when a page is demanded, the OS puts an entry in the page table that marks the page inaccessible
    - if the process then reads or writes the page, a trap occurs
    - then the OS does the work of finding a physical page, zeroing it, and mapping it into the process's address space

- **copy on write(COW)**
  - when the OS needs to copy a page from one address space to another, it just maps the physical address of that page
  into the target address space, and mark it read-only in both address spaces
  - when one of the address spaces tries to write to the page, then a trap occurs
  - the OS then allocate a new page copying the data, and map this new page into the address space of the faulting process
  - so now each process has its own private page 

  - in UNIX COW is even more important
    - `fork`: creates an exact copy of the address space of the caller
    - `exec`: overwrites address space of the caller

## 2. The Linux Virtual Memory System

### The Linux Address Space
- a virtual address space = user portion + kernel portion
- on a context switch: only current process's user portion changes
- a user mode program cannot access kernel virtual pages

- kernel virtual address types
1. **kernel logical address space**
  - normal virtual address space of the kernel
    - kernel data structures - page tables, per-process kernel stacks, etc.
  - cannot be swapped to disk
  - a direct mapping btw kernel logical address and the first portion of physical memory
    - simple to translate back and forth btw those two spaces
    - memory allocated in this part of the kernel's address space suitable for operations which need
    contiguous physical memory to work correctly(I/O to and from devices via **direct memory access**(DMA))

2. **kernel virtual address space**
  - not contiguous
  - but easier to allocate: used for large buffers where finding a contiguous large chunk of physical memory is difficult
  - the kernel can address more than 1GB(in 32-bit Linux) => not much issue in 64-bit

### Page Table Structure
- x86 provides a HW-managed, multi-level page table structure, with one page table per process
- currently 64-bit systems use four-level tables

### Large Page Support
- intel x86 allows for the use of multipe page sizes: huge pages => why?
  - reducing the number of mappings required in the page table
  - better TLB behavior
    - quickily fills up the TLB(using fewer slots in the TLB): less cache misses
    - shorter TLB-miss path: even if a miss occurs, the page is served more quickly
  - allocation could be faster

- downsides 
  - increased internal fragmentations
  - swapping burden could be heavy
  - overhead allocations

### The Page Cache
- keeps pages in memory from 3 different primary sources in a **page cache hash table** for quick lookup
  - **memory-mapped files**: https://en.wikipedia.org/wiki/Memory-mapped_file
  - file data and meta data from devices
  - heap and stack pages of processes(**anonymous memory**)

- dirty data is periodically written to the backing store by background threads
  - ensures that modified data eventually is written back to persistent storage

- a modified form of 2Q replacement policy for page eviction
  - handles the case: where a cyclic large-file access occurs
    - LRU in this case will evict other pages out of memory
    - moreover, what if this big file is never re-referenced before kicked out?

  - keeps two lists(**inactive, active**) and dividing memory btw them
    - when accessed for the first time, a page is pushed into the inactive list
    - when eviction takes place, it occurs in the inactive list
    - overall, the eviction policy follows approximated LRU

### Security And Buffer Overflows
- **buffer overflow**: lets the attacker inject code into the target's address space
  - usually happens when the programmer didnt' expect the length of a possible input
  - used for taking over the system and accessing private data(**privilege escalation**)
  - solution: preventing execution of any code found in certain regions of an address space(**NX bit**)

- **return-oriented programming(ROP)**: overwriting the stack such that the return address in the current executing function
points to a malicious instruction
  - solution: **address space layout randomization(ASLR)**(the OS randomizes addresses of code, stack, and heap)

### Other Security Problems: Meltdown And Spectre
- **meltdown** and **spectre**
- CPU **speculative execution** leaves traces of execution in various parts of the system
  - such state can make vulnerable the contents of memory
  - (not a perfect)solution: **kernel pagetable isolation**
    - remove as much of the kernel address space from each user process
    - instead, have a separate kernel page table for most kernel data
    - now a switch to the kernel pagetable is required: at the expense of performance
