# Intro to OS
- what happens when a program runs? - the **Von Neumann model of computing**
- the processor 
  - fetches an instruction from memory
  - decodes it, figuring out which instruction this is
  - executes it
- then it moves on to the next instruction until the program ends
- we need a SW that makes this running program easy

- OS: a body of SW that makes running programs easy
  1. CPU: running programs concurrently
  2. memory: allowing programs to share memory
  3. device: enabling programs to interact with devices
  
- **virtualization**
  - **virtual machine**: the OS takes a physical resource(CPU, memory, disk) and transforms it into a more general, powerful, and easy-to-use virtual form of itself
  - **system calls**: the APIs that user applications can use to run programs, using computer resources, etc.
  - **resource manager**: virtualization allows many programs to 
    - run(sharing the CPU) 
    - concurrently access their own instructions and data(sharing memory) and 
    - access devices(sharing devices like disks)

- **crux**: how to virtualize resources?

## 1. Virtualizing the CPU
- a few processors, but make an illusion that the system has a very large number of virtual CPUs
- **policy**: which of two programs should be run(or run first)?

## 2. Virtualizing Memory
- **physical memory model**
  - memory is just an array of bytes
  - read: specify an address / write: specify an address with the data to be written
  - remark: instructions of programs are in memory as well

- illusion: each running program has its own private memory
  - each process accesses its own private virtual address space, not affecting each other
  - OS maps this virtual address onto the physical memory of the machine
  - reality: physical memory is a shared source, managed by the OS

## 3. Concurrency
- **crux**: how to build correct concurrent programs?

## 4. Persistence
- storing data persistently: need HW & SW
- HW: I/O devices - hard drive, SSD
- SW: **file system** - the SW in the OS managing the disk
  - the OS does not create a private, virtualized disk for each application
  - it is assumed that users will share the data in files

- how to read/write a file?: issuing I/O requests to the storage device to do the followings
  - figuring out the location on disk
  - keeping track of the location in various structures the FS maintians
  - need to know: the low-level device interface and its exact semantics
  - the OS provides a standard and simple way to access devices through the syscalls  

- detailed issues:
  - performance: delaying writes for a while, batching them into larger groups
  - handling crashes during writes: write protocol such as journaling or COW
  - efficient operations: data structures from simple lists to complex b-trees

- **crux**: how to store data persistently?

## 5. Design Goals
- so what does the OS do?: three easy pieces
  - **virtualization**: virtualizes physical resources such as CPUs, memory, and disk
  - **concurrency**: handles many programs to be run at the same time
  - **persistence**: stores data over the long-term

- several goals for the OS desgin
  - **abstraction**: for making the system convenient and easy to use
  - **performance**: minimizing the overheads of the OS(extra time, extra space)
  - **protection**: btw applications themselves, and the applications and the OS(**isolation**)
  - **reliability**: non-stopping applications
  - other goals: security, energy efficiency, mobility

## 6. Some History
- skim through this section
