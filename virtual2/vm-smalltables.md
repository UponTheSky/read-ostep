# Paging: Smaller Tables
- how to make our page table smaller?

## 1. Simple Solution: Bigger Pages
- leads to waste within each page(**internal fragmentation**)
- most systems use relatively small page sizes

## 2. Hybrid Approach: Paging and Segments
- paging + segmentation: instead of having a single page table for the entire space of the process, 
why not have one per logical segment?
  - the base registers point to the physical addresses of the page tables of the segments
  - the bound registers indicate the end of the page tables

- but problems still reside
  - segmentation is not flexible: what if we have a large but sparsely-used heap? => still a lot of page table waste
  - external fragmentation
  - page tables can be of arbitrary sizes

## 3. Multi-level Page Tables
- **multi-level** page table
  - chop up the page table into page-sized units: if an entire page of page-table entries is invalid, don't allocate that page
  - then how do we track the validity of each page?: **page directory**

- **page directory**
  - the page directory either shows where a page of the page table is, or that the entire page of the page table contains no valid pages
  - so it tracks which pages of the page table are allocated with the page directory
  - **page directory entries**: valid bit + page frame number(PFN)
    - if the PDE is valid, at least one of the pages of the page table that the entry points to, is valid

- why do we use this?
  - the multi-level table only allocates page-table space in proportion to the amount of address space you're using
  - if carefully constructed, each portion of the page table fits neatly within a page, making it easier to manage memory
    - if extra space required, the OS just asks another page from the free list
    - **level of indirection**: we don't need to have a contiguous chunk of memory

- any costs?: time-space tradeoff
  - higher cost when a TLB miss occurs
  - complexity added

### A Detailed Multi-Level Example
- read through this part

### More Than Two Levels
- read through this part

### The Translation Process: Remember the TLB
- the HW first checks TLB, and if there is a hit, the page table need not be accessed

## 4. Inverted Page Tables
- instead of having many page tables per process:
  - we keep a single page table that has an entry for each physical page of the system
  - the entry tells us which process is using this page, and
  - which virtual page of that process maps to this physical page

- hash table is often used for speed-up lookups

## 5. Swapping the Page Tables to Disk
- it is still possible that page tables are too big to fit into memory
- some systems place page tables in **kernel virtual memory** instead of kernel-owned physical memory
- allowing the system to **swap** some of these page tables to disk when suffering lack of memory

## HW

1. simple - just one!

3. simply, accessing memory in vicinity will lead to less cache miss, since by our design close pages tend to 
be located in the same page directory page
