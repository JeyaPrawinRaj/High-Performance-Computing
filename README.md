# High Performance Computing Lab

This repository contains implementations of High Performance Computing (HPC) lab experiments using parallel programming techniques such as MPI (Message Passing Interface), Pthreads (POSIX Threads), and OpenMP.

---

## 📚 Experiments Overview

### 🔹 EX1 – Introduction to HPC
- Basic understanding of parallel computing concepts  
- Compilation and execution of simple C programs in Linux environment  

---

### 🔹 EX2 – MPI Basics
Introduction to MPI functions  

Programs using:
- `MPI_Init`  
- `MPI_Comm_rank`  
- `MPI_Comm_size`  

Demonstrates process communication basics  

---

### 🔹 EX3 – Parallel Frequency Count (MPI)
- Generates an array of random numbers  
- Finds frequency of a given number using parallel processing  

MPI concepts used:
- `MPI_Bcast`  
- `MPI_Scatter`  
- `MPI_Reduce`  

---

### 🔹 EX4 – Student Grade Calculation (MPI)
- Reads student data from file  
- Uses MPI Derived Data Types  
- Distributes data across processes  
- Calculates grades in parallel  

Uses:
- `MPI_Type_create_struct`  
- `MPI_Scatter`  
- `MPI_Gather`  

---

### 🔹 EX5 – Matrix Operations (Pthreads)
Performs:
- Matrix Addition  
- Matrix Multiplication  

Features:
- Uses multithreading for parallel computation  
- Demonstrates thread creation and synchronization  

---

### 🔹 EX6 – Spell Checker (Pthreads)
Implements Producer-Consumer problem  

Uses:
- Mutex locks  
- Condition variables  

Features:
- Checks words against a dictionary in parallel  

---

### 🔹 EX7 – Producer-Consumer using Semaphores
Implements producer-consumer problem using semaphores  

Uses:
- `sem_wait`  
- `sem_post`  

Features:
- Multiple consumer threads process arithmetic tasks  

---

### 🔹 EX8 – Array Operations (OpenMP)
Implements parallel array computations using OpenMP  

Programs include:
- Vector Addition (A + B = C)  
- Adding constant value to array  

Features:
- Uses `#pragma omp parallel for`  
- Measures execution time using `omp_get_wtime()`  
- Demonstrates workload distribution among threads  

Concepts used:
- Shared memory parallelism  
- Thread management  
- Critical sections for safe file writing  

---

### 🔹 EX9 – Numerical Integration (OpenMP)
Implements Trapezoidal Rule to approximate definite integral  

Problem:
- Computes integral of a function (example: f(x) = x²)  

Features:
- Divides interval into trapezoids  
- Each thread computes partial area  
- Final result combined using reduction  

Concepts used:
- `reduction(+:variable)`  
- Parallel loop execution  
- Load balancing among threads  

---

### 🔹 EX10 – Producer-Consumer (OpenMP)
Implements Producer-Consumer problem using OpenMP  

Features:
- Multiple producers read data from files  
- Consumers process data concurrently  
- Shared queue for communication  

Concepts used:
- `omp_lock_t` for synchronization  
- Critical sections for safe data access  
- Atomic operations and thread coordination  

---

## 🛠️ Technologies Used
- C Programming  
- MPI (Message Passing Interface)  
- Pthreads (POSIX Threads)  
- OpenMP  
- Linux Environment  

---

## 🎯 Learning Outcomes
- Understand parallel computing concepts  
- Gain hands-on experience with MPI, Pthreads, and OpenMP  
- Learn process communication and synchronization  
- Implement real-world parallel programming problems  
- Analyze performance improvements using parallelism  

---
