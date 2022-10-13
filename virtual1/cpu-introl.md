# The Abstraction: The Process
- **process**: a running program(informally)
  - program?: a collection of instructions on disk with some static data

- running several programs at the same time?
  - *crux*: since we're having only a few CPU, the OS needs to provide the illusion that we have many CPUs
  - *solution*: virtualizing the CPU
  - **time sharing** of the CPU: keep switching currently running processes for a single CPU
  - performance issue

- low-level machinery(=mechanisms)
  - *remark*: mechanisms are low-level methods or protocols that implement a needed piece of functionality
  - **context switch**: the mechanism of time sharing

- high-level policies
  - *remark*: policies are algorithms for making some kind of decision within the OS
  - **scheduling policy** in the OS

## 1. the abstraction: a process
- process?: a running program but in an abstracted way by the OS
- machine state: what a program can read or update when it is running
  - memory: instructions, data to be read/written
    - **address space**: the memory that the process can address
  - registers: pc, sp, fp
  - I/O information: a list of the files the process currently has open

## 2. process API
- an overview of process API implemented in most of the OSs
- create / kill / wait / control(sleep/awake) / get status

## 3. process creation: a little more detail
- how does the OS get a program up and running?
1. loding the code and the static data into memory
  - load the code into memory from disk(in an executable format)
  - load the static data(e.g. initialized variables) into the address space of the process from disk

  - lazy performing: modern OSes perform the process lazily, by loading code or data as they are needed during program execution

2. some memory is allocated for the program's run-time stack and heap
  - stack: local vars, function parameters, return address, etc.
    - the OS also likely initializes the stack with arguments(`argc`, `argv` in C's `main`)

  - heap: in C, the heap is used for explicitly requested dynamically-allocated data

3. initialization tasks related to I/O
  - e.g. the default three open file descriptors in UNIX systems

4. jumping to the `main` routine, the OS then transfers control of the CPU to the newly created process
  - now the program begins execution

## 4. process states
- possible different states a process can be at a given time
  - **running**: a process is running on a processor, executing instructions
  - **ready**: a process is ready to run but not yet chosen to be run by the OS
  - **blocked**: until some events happen, this process will not run at all

- state transition
  - scheduled: ready => running
  - descheduled: running => ready
  - running => (I/O initiate) => blocked => (I/O complete) => ready

## 5. data structures
- how to track the state of each process?
- **process list**: which process is ready to run? or already running?
- what kind of information does it track?
  - **register context**
    - when a process is stopped, the contents of its registers will be saved
    - so when they are restored, the OS can resume the process(**context switching**)

- other states than ready, running, and block
  - initial state / final(zombie) state

## HWs
- https://github.com/remzi-arpacidusseau/ostep-homework/

1. during the whole time 10, only the CPU was running(100%) while IO was never running

2. out of the total 11 clocks, the proc0 took 6 clocks whereas the proc1 took 5 clocks

3. the same for each process but the total clock got down to 7: the order really matters, since while the first process is making an I/O and gets blocked, the second process uses the CPU, whereas in the previous question the second I/O was blocked during which non of processes were working

4. It now becomes the same as the question 2

5. It now becomes the same as the question 3

6. not really - since the processes 1 ~ 3 finish earlier than the first process, later on
the process 0 runs I/O and get blocked while no other processes are running on the CPU

7. the total time decreases from 31 to 21 and CPU is busy all the time(100%): this because since the I/O process immediately resumes its I/O works and gets blocked, the other processes could occupy the CPU in the meantime

8. I chose the seed 1
- `IO_RUN_IMMEDIATE`: 15 clocks vs `IO_RUN_LATER`: 15 clocks => in this case the order matters
- `SWITCH_ON_IO`: 15 clocks vs `SWITCH_ON_END`: 18 clocks
