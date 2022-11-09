# Beyond Physical Memory: Policies
- **paging out**: lack of memory requires the OS to evict some pages for other pages to be used
- **replacement policy**: which page to evict first?

## 1. Cache Management
- memory can be viewed as a cache for virtual memory pages in the system
  - replacement policy is about minimizing this cache's misses
  - the **average memory access time(AMAT)** for a program
  - you always have to pay the cost of accessing the data in memory
  - so when a cache miss occurs, you pay extra cost of fetching the data from disk

- the cost of disk access is so high in modern systems
  - even a tiny miss rate will quickly dominate the overall AMAT of running programs

## 2. The Optimal Replacement Policy
- idea: evict the page that is needed the furthest from now
- but we don't know about the future: the optimal policy is for theoretical purpose(comparison with 
other possible algorithms)

## 3. A Simple Policy: FIFO
- when a replacement occurs, the page on the tail of the queue is evicted
- simple to implement, but FIFO cannot determine the importance of blocks

## 4. Another Simple Policy: Random
- pick a random page to be evicted  

## 5. Using History: LRU
- how to measure the importance of a page?: use history
  - *frequency*: how many times this page has been accessed
  - *recency*: how recently this page has been accessed

- **principle of locality**: programs tend to access certain code sequences and data structures
quite frequently

- policies: **LFU**(least frequently used), **LRU**(least recently used)

## 6. Workload Examples
- takeaways

1. no locality
- all the policies show the same performance
- cache size does matter
- optimal policy is always the best

2. 80-20 workload
- LRU does better: not a dramatic enhancement though

3. looping sequential workload
- could be disastrous for LRU and FIFO
- random in this case could be a very good option to choose

## 7. Implementing Historical Algorithms
- to implement LRU, we need to keep track of the latest access time of each of the pages
- with a HW support, we may record the timestamp of each page's access time whenever it is referenced
- but still, scanning through all the pages and find the least recently accessed page is burdensome
  - we need approximation of LRU policy

## 8. Approximating LRU
- many systems do approximation of LRU
- **use bit(or reference bit)**
  - per page we have one use bit, and all the use bits reside in memory somewhere
  - when a page is referenced, the use bit is set by HW to 1
  - after then, it is the OS's responsibility to clear the bit

- **clock algorithm**
  - all the pages of the system are arranged in a circular list
  - a **clock hand** points to a page
  - when a replacement must occur, the OS checks whether the currently pointed page has its use bit as 0 or 1
    - if it is 1, then it implies that the page has been used recently => the OS clears the bit to 0
    - otherwise, we evict the page

- although it is not the only way to implement an approximation of LRU using the use bits, the clock algorithm has been successful and has some nice properties 

## 9. Considering Dirty Pages
- one small modification: considering that whether a page has been modified or not while in memory
  - if a page has been modified(=**dirty**), it must be written back to disk when evicted, which costs additional I/O operations and thus quite expensive
  - conversely clean pages don't cost additional I/O

- so we prefer to evict clean pages
  - **dirty bit(=modified bit)**: set by HW when a page is written
  - this bit is incorporated into the page-replacement algorithm

## 10. Other VM Policies
- **page selection** policy: when to bring a page into memory
  - **demand paging**: the OS brings the page into memory when it is accessed
  - **prefetching**: the OS predicts which page would be accessed in the near future

- how the OS writes pages out to disk
  - **clustering(=grouping)** of writes: collecting a number of pending writes together in memory and write them to disk in one write
  - a single large write is more effective than many small ones

## 11. Thrashing
- **trashing**: a condition in which the system constantly pages
  - when memory is oversubscribed
  - so the memory demands of the set of running processes exceeds the available physical memory

- **admission control**: for a set of processes, a system could decide not to run a subset of processes
  - such that the reduced set of processes' **working sets**(=actively used pages) fit in memory

- some version of Linux run an **out-of-memory killer** when memory is oversubscribed

## HW

2. 
- FIFO/LRU: a simulation where we do looping sequential workload
  - each loop has length of 6(= cache size + 1)
  - eg) 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, ...

- MRU: once the cache gets full, iterate between two different values
  - eg) 0, 1, 2, 3, 5, 6, 5, 6, 5, 6, 5, ...
