# Scheduling: The Multi-Level Feedback Queue
- we'd like to minimize both *turnaround time* and *response time* measures
- however, we have no prior knowledge about processes: how can the scheduler learn about the jobs it is running so that it can improve its sheduling decisions?

## 1. MLFQ: Basic Rules
- basic settings
  - there are many queues, each assigned a different priority level
  - at any given time, a job that is ready to run is on one of the queues

- how MLFQ runs:
  - a job with higher priority is chosen to run
  - if more than one job are on a given queue(having the same priority): then MLFQ uses RR scheduling

- how MLFQ sets priorities:
  - MLFQ varies the priority of a job based on its *observed behavior*
  - MLFQ will try to learn about process as they run, and thus use the history of the job to predict its future behavior
  - job priorities change over time: how?

## 2. Attempt 1: How to Change Priority
- rules:
  - rule 3: when a job enters the system, it is placed at the highest priority(the topmost queue)
  - rule 4a, 4b: higher priorites for less-CPU-occupying jobs

### example 1: a single long-running job

### example 2: along came a short job
- MLFQ approximates SJF: since it doesn't know whether a job will be short or long-running, it first assumes that it might be a short job(giving high priority)

### example 3: what about I/O?
- rules 4a, 4b suggests that an interactive job doing lots of I/O remains in high priority
- the goal is to run interactive jobs quickly

### problems with our current MLFQ
1. **starvation**: too many interactive jobs will consume all CPU time, so that long-running jobs cannot get any CPU time
2. gaming the scheduler by a malicious user: using a trick of sending I/O requests, a process remains in high priority and monopolize the CPU
3. a program may change its behavior over time

## 3. Attempt 2: The Priorty Boost
- rule 5: after some time period S, move all the jobs in the system to the topmost queue
- this rule solves the two problems at once
  - starvation: again being at the higest priority queue, a job will share the CPU time again(RR scheduling)
  - even if a CPU-bound job has become interactive, the scheduler treats it properly once it has received the priority boost

- setting the time period S:
  - too low: interactive jobs may not get a proper share of the CPU
  - too high: long-running jobs could starve

## 4. Attempt 3: Better Accounting
- revising the rule 4: once a job uses up its time allotment at a given level(regardless of how many times it has given up the CPU), its priority is reduced

## 5. Turning MLFQ And Other Issues
- how to parameterize an MLFQ scheduler?(e.g. # of queues, boost period, etc.)
- skim through this part

## HW
1. `./python3 mlfq.py -n 2 --jlist 0,10,0:0,20:0`

2. 
- 8.2: `-n 3 --jlist 0,200,0 -q 10`
- 8.3: `-n 3 --jlist 0,180,0:100,10,0:110,10,0 -q 10`
- 8.4: `-n 3 --jlist 0,175,0:50,25,1 -i 1 -q 10`
- 8.5(right): `-n 3 --jlist 0,130,0:100,30,0:101,30,0 -B 100 -q 1`
- 8.6(right): `-n 3 --jlist 0,150,0:70,100,10 -i 1 -q 1 -a 5`
- 8.7: uses `Q`

3. `-n 1 --jlist 0,100,0:0,100,0 -q 10`

4. `-n 3 --jlist 0,1000,9:0,1000,0 -q 10 -S -i 1`

5. set `-B` as 1/20 of the total running time of the process

6. ...