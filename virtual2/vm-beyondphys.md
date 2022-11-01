# Beyond Physical Memory: Mechanisms
- we want to support
  - many concurrently running large address spaces
  - a single large address space

- the OS need extra space to stash away portions of address spaces that currently aren't in gread demand
- **hard disk drive**: more capacity than memory, but generally slower

## 1. Swap Space
- **swap space**: reserved space on the disk for moving pages back and forth
  - the OS needs to remember the **disk address** of a given page

- note that swap space is not the only on-disk location for swapping traffic
  - for example, a binary code page is usually initially found on disk
  - when the program runs using that binary code, now the code is loaded into memory

## 2. The Present Bit
- when the HW looks in the PTE, it is notified that the page is not present in physical memory via
its **present bit** in the PTE
  - if is set to zero, the page is not in memory but rather on disk somewhere
  - **page fault** and **page fault handler**

## 3. The Page Fault
- the OS is in charge of page faults
  - now the OS needs to swap the page into memory in order to service the page fault
  - how does the OS know where to find the desired page?: use the bits in the PTE to find the address
  - then it issues the request to disk to fetch the page into memory

- while the request is in flight, the process will be in the **blocked** state

- when the request is made, then the OS update the page table to mark the page as present and its PFN
- retrying instruction => another TLB miss => TLB update => TLB hit

## 4. What If Memory Is Full?
- memory may be full or close to be full
- the OS needs to first **page out** one or more pages to make room for the new pages the OS is about to bring in
- **page-replacement policy**

## 5. Page Fault Control Flow
- HW: if a TLB cache miss occurs
1. not valid(no such page): segfault
2. valid, but protected: protection fault
3. valid, accessible, but not present: page fault
4. valid, accessible, and present: update TLB

- SW: when a page needs to be swapped in
1. find a physical frame for the soon-to-be-faulted-in page to reside with
  - if there is no such page, we run a replacement algorithm to evict some frames out of memory
2. now the page fault handler issues the I/O request to read in the page from swap space
3. after the request is fulfilled, the OS updates the page table, retrying the instruction

## 6. When Replacements Really Occur
- in reality, the OS keeps a small portion of memory free more proactively
- **HW(high watermark), LW(low watermark)**
  - when the OS notices that there are fewer than LW pages available, a background thread(**swap, page daemon**)
  runs to free memory by evicting pages, until there are HW pages available

- why do we do this?: performance issue
  - performing a number of replacements at once
  - **clustering, grouping** a number of pages and write them out at once, increasing the efficiency of the disk

- so instead of performing a replacement directly, the algorithm simply checks whether there are free memory available first
  - if not, then it informs the deamon to free some pages
  - after then, the deamon rewaken the original thread to resume what it needs to do

## HW
1. not much significantly visible changes; only the number of interrupts increased

2. `swpd` doesn't show much difference; however, the change in `free` column was noticeable, and the numbers almost return to 
their previous states when we killed the process

3. as the number gets close to the limit, both `si/so` significantly increase / compared to the first loop, the number dramatically increases

4. `swpd` - increases / `free` - significantly decreases / `buff/cache` fluctuating, but generally decreasing

5. usually, the first loops are around 3 times slower than the subsequent loops
- the bandwidth almost never changes until we get really close to the limit(almost 10 times lower)

6. the swap space gets diminished
