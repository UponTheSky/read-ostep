# Paging: Introduction
- **segmentation**: chop things up into *variable-sized* pieces
- **paging**: chop up space into *fixed-sized* pieces
  - each piece(fixed-sized unit) is called a **page**
  - so the physical memory is an array of fixed-sized slots called **page frame**s
  - each frame can contain a single virtual-memory page

- so "page" is a concept in virtual memory, whereas "page frame" is the corresponding concept in pyhsical memory

## 1. A Simple Example And Overview
- why paging?
  - *flexibility*: the OS doesn't care how a process deals with its address space
  - *simplicity*: free-space management gets much easier(**free-list**)

- **page table**: records where each virtual page of the address space is placed in physical memory
  - *per-process* data structure
  - stores *already translated* physical addresses
  - translation: (VPN: virtual page number) + (offset) => (PPN: physical page/frame number) + (offset: remains the same)

## 2. Where Are Page Tables Stored?
- page tables are big: even one page table may need to represent the whole physical pages
- we don't do any HW mechanism for keeping such a page table: instead we store the page table for each process
in *memory* somewhere

## 3. What’s Actually In The Page Table?
- data structure?:  
  - simplest: a linear table indexed by a VPN

- contents of a PTE
  - **valid** bit: indicate whether the particular translation is valid
  - **protection** bits: r/w/x
  - **present** bits: indicate whther the current page is in physical memory or on disk(**swapped out**)
  - **dirty** bits: indicate whether the page has been modified since it was brought into memory
  - **reference/access** bits: track whether a page has been acessed
    - useful in determining which pages are popular and thus should be kept in memory
    - **page replacement**

- **remark**: swap
  - to support address spaces that are larger than physical memory
  - moving rarely used pages to disk

## 4. Paging: Also Too Slow
- the process of accessing memory
1. first, fetch the proper PTE from the process's page table
2. looking up the PTE, check the translated PPN from VPN
3. now load the data from physical memory

- so for every memory reference, paging requires performing one extra memory reference in order to
first fetch the translation from the page table => may be too slow

- two real problems of paging
  - too slow a memory access is
  - too big a page table is

## 5. A Memory Trace
- skim through this part

## HW
1. 
- address space: grows proportionally
- page size: diminishes proportionally

2. the number of valid virtual addresses increases

3. the last one is quite unrealistic: too big an address space's limit size
