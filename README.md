# 🚀 High Performance Computing Lab

This repository contains implementations of **High Performance Computing (HPC) lab experiments** using parallel programming techniques such as **MPI (Message Passing Interface)** and **Pthreads (POSIX Threads)**.

---

## 📚 Experiments Overview

### 🔹 EX1 – Introduction to HPC

* Basic understanding of parallel computing concepts
* Compilation and execution of simple C programs in Linux environment

---

### 🔹 EX2 – MPI Basics

* Introduction to MPI functions
* Programs using:

  * `MPI_Init`
  * `MPI_Comm_rank`
  * `MPI_Comm_size`
* Demonstrates process communication basics

---

### 🔹 EX3 – Parallel Frequency Count (MPI)

* Generates an array of random numbers
* Finds frequency of a given number using parallel processing
* MPI concepts used:

  * `MPI_Bcast`
  * `MPI_Scatter`
  * `MPI_Reduce`

---

### 🔹 EX4 – Student Grade Calculation (MPI)

* Reads student data from file
* Uses **MPI Derived Data Types**
* Distributes data across processes
* Calculates grades in parallel
* Uses:

  * `MPI_Type_create_struct`
  * `MPI_Scatter`
  * `MPI_Gather`

---

### 🔹 EX5 – Matrix Operations (Pthreads)

* Performs:

  * Matrix Addition
  * Matrix Multiplication
* Uses multithreading for parallel computation
* Demonstrates thread creation and synchronization

---

### 🔹 EX6 – Spell Checker (Pthreads)

* Implements **Producer-Consumer problem**
* Uses:

  * Mutex locks
  * Condition variables
* Checks words against a dictionary in parallel

---

### 🔹 EX7 – Producer-Consumer using Semaphores

* Implements producer-consumer problem using **semaphores**
* Uses:

  * `sem_wait`
  * `sem_post`
* Multiple consumer threads process arithmetic tasks

---

## 🛠️ Technologies Used

* **C Programming**
* **MPI (Message Passing Interface)**
* **Pthreads (POSIX Threads)**
* **Linux Environment**

---

## 🎯 Learning Outcomes

* Understand parallel computing concepts
* Gain hands-on experience with MPI and Pthreads
* Learn process communication and synchronization
* Implement real-world parallel programming problems



---

⭐ *This repository is created for academic and learning purposes.*
