# Scheduling: Introduction
- the high-level **policies** that an OS scheduler employs: **scheduling policies**?

## 1. Workload Assumptions
- some jargons: **job**, **workload** - basically the same as "running process"
- basic workload assumptions(but not much realistic at the moment): skim through this part

## 2. Scheduling Metrics
- which scheduling policies to choose?: we need a **scheduling metric**
- example: turnaround time of a job = time of completion - time of arrival
- **performance** metric vs **fairness** metric

## 3. First In, First Out(FIFO)
- FIFO(or first come, first served fcfs) scheduling
- simple so that easy to implement
- downside: **convoy effect**
  - when we have different completion time jobs
  - a number of relatively-short potential consumptions of a resource get queued behind a heavyweight
  resource consumer

## 4. Shortest Job First(SJF)
- SJF: runs the shortest job first, then the next shortest one, and so on
- an optimal scheduling algorithm for the current assumption about jobs, all ariving at the same time
- downside: what if arrival time of each job differs?
  - suffers the same convoy problem: if a job of long running time arrives first

## 5. Shortest Time-to-Completion First(STCF)
- what if a scheduler can do something else when new jobs arrive?
  - **preempts** the currently running job and decides to run another job, continuing the current job later

- STCF: add preemption to SJF
  - any time a new job enters the system, the STCF scheduler dtermines which of the remaining jobs(including the new job) has the least time left, and schedules that one
  - currently an optimal solution

## 6. A New Metric: Response Time
- users demand interactive performance from the system
- **response time** = (first scheduled run time) - (arrival time)

- STCF and related disciplines are not particularly good for response time
  - later jobs must wait for the previous jobs to run in their entirety before being scheduled
  - bad for response time and interactivity

## 7. Round Robin
- **Round Robin(RR)**(=time slicing) scheduling: instead of running jobs to completion, RR runs a job for a **time slice**(= **scheduling quantum**) and then switches to the next job in the run queue
  - the length of a time slice must be a multiple of the time-interrupt period

- deciding the length of the time slice: trade-off
  - shorter: better response
  - longer: less cost for context switching

- cost of context switching
  - a program's state info is in: CPU caches, TLBs, branch predictors, and other on-chip HW
  - switching context means dealing with these segments of info, which is costly

- also not good for the turnaround time metric: even worse than FIFO
  - inherent trade-off btw fairness and performance: any fair policy like RR suffers some poor performance in terms of some metrics like the trunaround time metric

## 8. Incorporating I/O
- what if a process makes an I/O request?
  - the scheduler should schedule another job on the CPU while the current process is blocked
  - it also needs to make a decision when the I/O completes

- a common approach: treat each CPU burst of a process doing I/O as a job(kind of subdividing the process into independent jobs)
  - allows overlap - one process uses CPU while the other waits for the I/O to complete

## 9. No More Oracle
- the OS usually knows very little about the length of each job
- what is good for SJF, STCF, or RR?
