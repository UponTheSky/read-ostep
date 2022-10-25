# Segmentation
- problems of the simple approach of base-bounds pair address translation
  - waste of free spaces
  - hard to run a program, when the entire address space doesn't fit into memory

- how to support a large address space flexibly?

## 1. Segmentation: Generalized Base/Bounds
- idea: why not having a base and bounds pair per logical segment of the address space?
  - a **segment** is just a contiguous portion of the address space of a particular length
  - our three logical segments: code, stack, and heap
  - now the OS places each one of these logical segments in different parts of physical memory, *independently*
  - so we can avoid filling physical memory with unsued virtual address space

- HW support: each MMU has a set of three base and bounds register pairs

- when translating, we need to extract the offset of our virtual address from each segment of interest, rather than the actual virtual address itself

- `segmentation fault`

## 2. Which Segment Are We Referring To?
- how does the HW know the offset into a segment, and to which segment an address refers?

- **explicit** approach: chop up the address space into segments based on the top few bits of the virtual address
  - top bits for segments / bottom bits for offset
  - now we simply checks whether offset < bounds
  - issue with using many top bits: limits the size of each segment in the virtual address space

- **implicit** approach: the HW determines the segment by noticing how the address was formed

## 3. What About The Stack?
- stack grows backward so it needs special care when it comes to address translations
  - need extra HW support(telling whether a segment is growing positive or negative)
  - another way of translating a virtual address

## 4. Support for Sharing
- to save memory, sharing certain memory segments btw address spaces is useful
- **code sharing** is common and still used in modern systems

- however, for sharing segments, we need a extra support from the HW: **protection bits**
  - read/write/execute, or read/write/execute only
  - if set read-only, the same code can be shared across multiple processes, without worry of harming isolation
  - now the HW also has to check if an access is permissible

## 5. Fine-grained vs. Coarse-grained Segmentation
- coarse-grained: a few segments, large chunks
- fine-grained: a large number of smaller segments
  - need a HW support: segment table(stored in memory)

## 6. OS Support
- segmentation issues?
1. what should the OS do on a context switch? 
  - the segment registers must be saved and restored

2. OS interaction when segments grow/shrink?
  - the memory-allocation library will perform a syscall to grow the segment of interest(`sbrk`, for example)

3. managing free space in physical memory
  - when a new address space is created, the OS has to be able to find space in physical memory for its segments
  - each segment might be of different size, and we have many segments now per process
  - **external** fragmentation:
    - btw processes
    - the physical memory is full of little holes of free space: difficult to allocate new segments or to grow existing ones

  - **compact** physical memory: rearranging the existing segments
    - copying is costly
    - segment growing request may require furthur rearranging

  - free-list management algorithms: best-fit/worst-fit/first-fit/buddy algorithm

## 7. Summary
- segmentation isn't flex enough to support generalized sparse address space
  - for example, what if we have a large but sparsely-used heap all in one logical segment?
  - the entire heap must still reside in memory in order to be accessed

## HW

1. for example, for the first run:
- 0: 492 / 1: segfault(1) / 2: segfault(0) / 3: segfault(0) / 4: segfault(1)

2. 
- legal: seg0: 0 + limit size = 19 / seg1: addr space size - limit size = 108
- illegal: lowest - 20 / highest - 107
- command: `-A 19,108,20,107`

3. `0,2,16,2`

4. set the two limits as big as possible, so that the tow segments covers the entire address space

5. conversly, set the limits `0`


