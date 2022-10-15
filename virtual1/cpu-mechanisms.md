# Mechanism: Limited Direct Execution
- time sharing and scheduling
- challenges(**crux**)
  - *performance*: virtualizing CPU without excessive overhead to the system
  - *control*: running processes efficiently while retaining control over the CPU

## 1. Basic Technique: Limited Direct Execution
- for performance: **limited direct execution**
- direct execution: just run the program directly on the CPU
- questions:
  1. running a process without any unexpected execution and with efficiency
  2. stopping a process and switching to another process(**time sharing**)

## 2. Promblem 1: Restricted Operations
- **crux**: how to perform restricted operations
  - what if a process wants issuing an I/O request to a disk, or gaining access to more system resources?

- **user** vs **kernel** mode
  - user mode: process / restricted in what a process can do
  - kernel mode: kernel / can run any privileged operations

- **system call**: how does a process in user mode do in order to execute some privileged operations
  - provided by kernel
  - accessing the FS, creating/destroying processes, communicating with other proceses / allocating more memory
  - **system-call number**: to specify the exact syscall
    - It is the user code's responsibiliy to place the wanted syscall number in a register or at a specified location on the stack
    - indirection for protection: user code cannot jump directly into privileged operation code

- **trap**: how to execute a syscall?
  - a program execute a special trap instruction
  - then the pc jumps into the kernel, and raises the privilege level to kernel mode
  - when finishing privileged works, the OS call special **return-from-trap** instruction
  - then pc returns to the calling user process, with reduced privilege level back to user mode

  - the HW needs to save enough of the caller's registers to be able to return correctly when the OS
  issues the return-from-trap instruction
    - it could be the kernel stack where those register values are stored
    - each process has its own kernel stack

- **trap table**
  - how does the trap know which code to run inside the OS?
  - at boot time, the kernel in privileged mode configures the HW such that what code(**trap handlers**) is run for which exception

## 3. Problem 2: Switching Between Processes
- there is no way for the OS to take an action if it is not running on the CPU
- **crux**: how can the OS regain control of the CPU(so that it can switch between processes)?

### a cooperative approach: wait for syscalls
- in this style, the OS trusts the processes to behave reasonably 
  - processes transfer control of the CPU to the OS frequently by making syscalls 
  - **yield** syscall: does nothing except to transfer control to the OS so that it can run other processes
  - also, applications transfer control to the OS when they do something illegal(generate a trap to the OS)

### a non-cooperative approach: the OS takes control
- what if a process is malicious and refuses to transfer control?
- **timer interrupt**
  - a timer device raises an interrupt every so many milliseconds
  - then the currently running process is halted and a pre-configured **interrupt handler** in the OS runs
  - now the OS has regained control over the CPU and do **time sharing**

- how does a timer initiate?
  - at boot time, the OS inform the HW the location of timer interrupt handler code
  - during the boot time, the OS starts the timer(privileged instruction)

- timer can be turned off: concurrency issue

- here the HW also has some responsibility when a timer interrupt occurs, for saving enough of the state of the program that was running when the interrupt occurred

### saving and restoring context
- decision: continue running the currently running process vs switching to another => **scheduler**
- **context switch**: a low-level(asm) piece of code for saving a few register values for the currently running process(onto its kernel stack) and restoring a few for the soon-to-be-run process(from its kernel stack)
  - registers: some general purpose registers, PC, the kernel stack pointer of the current process

- then how exactly does a context switch occur?
  - in the time interrupt handler, the OS decides switching
  - calls `switch()` routine
  - saves current register values(into the process structure of the current process)
  - restores next register values(from its process structure entry)
  - switching context: changing the stack pointer to use the next process's kernel stack

- two types of regsiter saves/restores
  - user registers of the current process:
    - implicitly saved by the HW, using the kernel stack of the process
    - when the time interrupt occurs
  - the kernel registers
    - explicitly saved by the SW, using the process structure
    - when OS calls `switch` to do context switching

## 4. Worried About Concurrency?
- questions
  - what if another interrupt occurs during an interrupt or trap handling

- disabling interrupts
- locking
