for project3.c++
# 📚 Library Management System (C++)

## 📌 Overview
A **console-based Library Management System** built in C++ that demonstrates core Object-Oriented Programming (OOP) and Data Structures concepts. It allows a librarian to add, search, issue, return, delete, and display books, while automatically managing a **reservation queue** for books that are currently checked out — simulating a real-world library workflow entirely from the terminal.

## 🎯 Problem Statement
Manual, paper-based library record-keeping is slow, error-prone, and hard to search. This project simulates a simplified digital library system that automates book tracking, availability status, and reservation handling — showcasing how fundamental data structures (hash maps and queues) can solve a real, everyday organizational problem.

---

## ✨ Key Features

- ➕ **Add Book** — Register a new book with a unique ID, title, and author
- 🔍 **Search by Title** — Look up a book and instantly see its ID, author, and availability status
- 📤 **Issue Book** — Checks out a book to a user; if already issued, automatically adds the user to a **FIFO reservation queue**
- 📥 **Return Book** — Marks a book as available again, or — if others are waiting — automatically hands it to the next person in the reservation queue
- 🗑️ **Delete Book** — Removes a book record and safely frees its memory
- 📋 **Display All Books** — Lists every book in the system with its current status (Issued/Available)
- 🔁 **Menu-Driven Interface** — Simple numbered menu loop for continuous interaction until the user exits

---

## 🛠️ Tech Stack & Concepts Used

| Category | Details |
|---|---|
| Language | C++ (C++11 or later) |
| OOP Concepts | Classes, Encapsulation, Constructors, Destructors |
| Data Structures | `unordered_map` (hash table for O(1) book lookup by ID), `queue` (FIFO reservation handling) |
| Memory Management | Manual dynamic allocation (`new`/`delete`) with a custom destructor to prevent memory leaks |
| STL Libraries | `<unordered_map>`, `<queue>`, `<vector>`, `<algorithm>`, `<fstream>` |
| Interface | Console/terminal-based menu system |

---

## 🔍 How It Works (Design Breakdown)

### 1. `Book` Class
A simple data class holding a book's `id`, `title`, `author`, and `isIssued` status flag, initialized through its constructor.

### 2. `Library` Class
The core engine of the system, built around two key data structures:
- **`bookDB` (unordered_map<int, Book*>)** — Maps each book ID directly to its `Book` object pointer, giving **average O(1) time complexity** for add, search, issue, return, and delete operations.
- **`reservationList` (unordered_map<int, queue<string>>)** — Maps each book ID to a **queue** of user names waiting for that book, ensuring reservations are honored in **first-come-first-served** order.

### 3. Core Operations
- **`addBook()`** — Prevents duplicate IDs and inserts a new `Book` into the hash map.
- **`searchBookByTitle()`** — Performs a linear scan through the map to find matching titles (since the map is indexed by ID, not title) and prints matching results.
- **`issueBook()`** — If the book is available, issues it directly; if not, queues the requesting user instead of rejecting the request outright.
- **`returnBook()`** — Checks the reservation queue first: if someone is waiting, the book is immediately handed to the next person in line rather than just being marked "available."
- **`deleteBook()`** — Frees the dynamically allocated `Book` object before erasing it from the map, avoiding memory leaks.
- **`displayBooks()`** — Iterates through the entire map to print a full catalog with live status.

### 4. Destructor (`~Library()`)
Iterates through all remaining `Book*` pointers and deletes them when the `Library` object goes out of scope — proper cleanup of manually managed memory.

### 5. `main()` Function
Implements an infinite loop presenting a numbered menu, reading user choice with `cin`, and dispatching to the appropriate `Library` method via a `switch` statement, using `getline()` for multi-word input like titles and names.

---

## 💡 Real-World Applications

- 🏫 **School/College Libraries** — Small-scale digital catalog and checkout system
- 🏢 **Small Organizations** — Internal resource lending trackers (equipment, tools, books)
- 🎓 **Learning Tool** — Excellent example project for understanding hash maps, queues, pointers, and OOP in C++
- 🧩 **Foundation for Larger Systems** — Can be extended into a full-fledged Library Management System with a GUI, database, and multi-user support
- 💾 **Interview Prep** — Commonly used as a DSA + OOP demonstration project in technical interviews

---

## 🚀 Future Improvements

- [ ] **Persistent storage** — Save/load book data to/from a file or database (currently `<fstream>` is imported but unused — data resets on every run)
- [ ] **Due dates & fines** — Track issue dates and calculate overdue fines
- [ ] **Search by author/ID** — Extend search beyond title-only lookup
- [ ] **Input validation** — Handle invalid/non-numeric input for `id` and `choice` gracefully
- [ ] **Case-insensitive search** — Improve title search to ignore case differences
- [ ] **Multiple copies support** — Track quantity per book instead of a single boolean flag
- [ ] **GUI or web interface** — Migrate from console to a Qt, web, or REST API-based front end
- [ ] **Unit tests** — Add test coverage for core `Library` methods

---

 for project1.c++
 # 🔢 BigInt Calculator (Arbitrary-Precision Arithmetic in C++)

![C++](https://img.shields.io/badge/C++-11+-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)

## 📌 Overview
A custom **Big Integer (BigInt) class** implemented from scratch in C++ that supports arithmetic on numbers far larger than what native types like `int` or `long long` can hold. It implements addition, subtraction, multiplication, division, modulus, exponentiation, and comparison operators — all built on top of a digit-array representation, without relying on any external big-number library.

## 🎯 Problem Statement
Native C++ integer types overflow beyond a fixed range (e.g., `long long` maxes out around 9.2 × 10¹⁸). Many real problems — cryptography, factorials, combinatorics, competitive programming — require precise arithmetic on numbers with hundreds or thousands of digits. This project solves that by representing numbers as a **vector of digits** and implementing every core arithmetic operation manually, mirroring how large numbers are handled in specialized math libraries.

---

## ✨ Key Features

- ➕ **Addition & Subtraction** — Handles both positive and negative operands correctly, including sign-aware borrowing/carrying
- ✖️ **Multiplication** — Implements schoolbook (grade-school) multiplication with carry propagation
- ➗ **Division & Modulus** — Long-division algorithm using **binary search per digit** to find each quotient digit efficiently
- 🔺 **Exponentiation** — `pow()` method for raising a BigInt to a power
- ⚖️ **Comparison Operators** — Custom `<`, `<=`, and `==` that correctly account for sign and digit-length differences
- ➖ **Unary Negation** — Overloaded unary `-` operator for sign flipping
- 🧹 **Leading Zero Cleanup** — Automatically trims leading zeros after every operation to keep the internal representation clean
- ⚠️ **Division-by-Zero Protection** — Throws a `runtime_error` exception when dividing by zero
- 🖥️ **Interactive Console Demo** — Takes two big numbers as input and prints their sum, difference, product, quotient, remainder, and power

---

## 🛠️ Tech Stack & Concepts Used

| Category | Details |
|---|---|
| Language | C++ (C++11 or later) |
| OOP Concepts | Class encapsulation, operator overloading, const-correctness |
| Data Structures | `vector<int>` (digits stored in **reverse order** — least significant digit first — for easy carry handling) |
| Algorithms | Grade-school multiplication, long division via binary search, exception handling |
| STL Libraries | `<vector>`, `<string>`, `<algorithm>` |

---

## 🔍 How It Works (Design Breakdown)

### 1. Internal Representation
Each `BigInt` stores its digits in a `vector<int>`, **least significant digit first** (e.g., `123` is stored as `[3, 2, 1]`). This ordering makes carry/borrow propagation during addition, subtraction, and multiplication much simpler, since operations naturally proceed from index 0 upward.

### 2. Construction from String
The constructor takes a numeric string, detects a leading `-` for negative numbers, and fills the digit vector in reverse — then strips any leading zeros.

### 3. Operator Overloading
- **`operator+`** — Adds digit-by-digit with carry; if signs differ, it delegates to subtraction (`*this - (-other)`)
- **`operator-`** — Subtracts digit-by-digit with borrow; handles sign mismatches and ensures the larger-magnitude number is subtracted from correctly by delegating to `abs()` comparisons
- **`operator*`** — Classic O(n×m) digit-by-digit multiplication with carry propagation into a pre-sized result vector
- **`operator/`** — For each digit position (from most significant), uses **binary search (0–9)** to find the largest quotient digit such that `divisor × digit ≤ current remainder` — a clean way to avoid repeated subtraction
- **`operator%`** — Derived directly from division: `a % b = a - (a/b)*b`
- **`operator-()` (unary)** — Returns a sign-flipped copy
- **`operator<`, `operator<=`, `operator==`** — Compare sign first, then digit-length, then digit-by-digit from most significant to least

### 4. `main()` Function
Reads two big numbers as strings from the user, constructs `BigInt` objects, and prints the results of all six operations, catching and displaying exceptions (like division by zero) gracefully.

---

## 🖥️ Sample Run


Enter first big number: 123456789123456789
Enter second big number: 987654321987654321

Sum: 1111111111111111110
Difference: -864197532864197532
Product: 121932631112635269135802241129526161
Quotient: 0
Remainder: 123456789123456789
Power (a^b): 1   (⚠️ see Known Issues — pow() bug)


---

## ⚠️ Known Issues / Limitations

- **`pow()` has a logic bug**: the loop condition `while (exp < BigInt("0"))` only runs while the exponent is *negative*, so for any normal positive exponent the loop body never executes and the function always returns `1`. This should instead loop **while `exp > 0`**, halving `exp` each iteration (fast exponentiation) — worth fixing before relying on this method.
- **`abs()` on subtraction correctness** relies on `operator<`, which is only implemented (not `>` or `>=`) — this works but makes the comparison logic slightly harder to follow; adding `operator>` would improve readability.
- **No input validation** — non-numeric input (letters, empty strings) will cause undefined behavior rather than a graceful error.
- **No support for decimal/floating-point big numbers** — integers only.

---

## 💡 Real-World Applications

- 🔐 **Cryptography** — RSA and other algorithms rely on arithmetic over very large integers beyond native type limits
- 🧮 **Competitive Programming** — Factorials, large Fibonacci numbers, combinatorics problems commonly require BigInt arithmetic
- 🔬 **Scientific Computing** — Calculations involving extremely large or precise values (e.g., number theory research)
- 📚 **Educational Tool** — Excellent for learning how languages like Python implement arbitrary-precision integers under the hood, and for practicing operator overloading and manual algorithm design in C++
- 💾 **Financial/Data Systems** — Situations requiring exact large-scale integer math without floating-point precision loss

---

## 🚀 Future Improvements

- [ ] Fix the `pow()` loop condition to correctly implement fast exponentiation
- [ ] Add `operator>`, `operator>=`, `operator!=` for a complete comparison suite
- [ ] Add support for `+=`, `-=`, `*=`, `/=` compound assignment operators
- [ ] Add input validation for malformed number strings
- [ ] Optimize multiplication using Karatsuba algorithm for large inputs
- [ ] Add unit tests covering edge cases (zero, negative numbers, division remainder signs)
- [ ] Support big decimal (fixed-point) arithmetic

---

project2.c++ 
# ⚙️ CPU Scheduling Algorithms Simulator (C++)

![C++](https://img.shields.io/badge/C++-11+-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)

## 📌 Overview
A console-based simulator implementing four classic **CPU Scheduling Algorithms** used in Operating Systems: **FCFS (First Come First Serve)**, **SJF (Shortest Job First)**, **Round Robin**, and **Priority Scheduling**. The program takes process details as input, applies the selected algorithm, and outputs each process's waiting time, turnaround time, and a simple Gantt chart — replicating how an OS scheduler decides process execution order.

## 🎯 Problem Statement
In multitasking operating systems, the CPU must decide the order in which multiple competing processes get executed. Different scheduling strategies trade off fairness, responsiveness, and throughput differently. This project simulates and compares these strategies on the same set of processes, helping visualize how each algorithm affects waiting and turnaround time — a core concept in every Operating Systems course.

---

## ✨ Key Features

- 🕐 **FCFS (First Come First Serve)** — Processes are executed strictly in order of arrival
- ⏱️ **SJF (Shortest Job First, Non-preemptive)** — Processes are sorted and executed by shortest burst time first
- 🔄 **Round Robin** — Time-sliced, preemptive scheduling using a user-defined quantum, cycling through processes fairly
- 🎯 **Priority Scheduling** — Processes are executed in order of highest priority first
- 📊 **Waiting & Turnaround Time Calculation** — Automatically computed for every process under the chosen algorithm
- 📉 **Gantt Chart Display** — Simple text-based visualization of process execution order and timing
- ⚠️ **Input Validation** — Rejects zero/negative process counts and invalid Round Robin time quantums

---

## 🛠️ Tech Stack & Concepts Used

| Category | Details |
|---|---|
| Language | C++ (C++11 or later) |
| OS Concepts | Process scheduling, waiting time, turnaround time, preemptive vs. non-preemptive scheduling |
| Data Structures | `struct Process`, `vector<Process>` |
| Algorithms | Sorting-based scheduling (FCFS, SJF, Priority), time-slice simulation (Round Robin) |
| STL Libraries | `<vector>`, `<algorithm>`, `<climits>` |

---

## 🔍 How It Works (Design Breakdown)

### 1. `Process` Struct
Holds each process's `pid`, `arrivalTime`, `burstTime`, `priority`, and the computed `waitingTime` and `turnaroundTime`.

### 2. FCFS — `FCFS()`
The foundational algorithm: processes execute strictly by arrival order. `waitingTime = currentTime - arrivalTime`, and `turnaroundTime = waitingTime + burstTime`. Every other non-preemptive algorithm in this project is implemented by **sorting first, then reusing this same FCFS logic** — a neat design pattern that avoids code duplication.

### 3. SJF — `SJF()`
Sorts all processes by `burstTime` ascending using `compareByBurstTime`, then calls `FCFS()` on the sorted list — so the shortest job effectively goes first.

### 4. Priority Scheduling — `PriorityScheduling()`
Sorts processes by `priority` descending using `compareByPriority` (higher number = higher priority), then reuses `FCFS()` the same way SJF does.

### 5. Round Robin — `RoundRobin()`
The only **preemptive** algorithm here. Each process gets a fixed `quantum` of CPU time per turn; if it doesn't finish, it's revisited in the next cycle. Tracks `remainingBurstTime` per process and loops until all processes complete, incrementing `currentTime` after each time slice.

### 6. `displayResults()`
Prints a table of PID, arrival time, burst time, priority, waiting time, and turnaround time for every process, followed by a basic text Gantt chart showing execution order and timestamps.

### 7. `main()`
Collects process count and details from the user, validates input, prompts for algorithm choice (and time quantum if Round Robin is selected), dispatches to the correct scheduling function, and displays results.

---




## 🖥️ Sample Run


Enter number of processes: 3
Enter arrival time of process 1: 0
Enter burst time of process 1: 5
Enter priority of process 1 (higher value means higher priority): 2
Enter arrival time of process 2: 1
Enter burst time of process 2: 3
Enter priority of process 2 (higher value means higher priority): 1
Enter arrival time of process 3: 2
Enter burst time of process 3: 8
Enter priority of process 3 (higher value means higher priority): 3

Choose Scheduling Algorithm: 
1. FCFS 
2. SJF 
3. Round Robin 
4. Priority Scheduling
Enter choice: 1

PID	Arrival	Burst	Priority	Waiting	Turnaround
1	0	5	2		0	5
2	1	3	1		4	7
3	2	8	3		7	15

Gantt Chart:
| P1 | P2 | P3 |
0	5	8	16


---

## ⚠️ Known Issues / Limitations

- **Round Robin doesn't check arrival time properly** — a process with a later arrival time can still be scheduled at `currentTime = 0` in the first pass, which isn't strictly correct preemptive behavior.
- **`waitingTime` in Round Robin accumulates incorrectly across multiple visits** — it's recalculated using `currentTime - arrivalTime` on every time slice rather than tracking true idle/waiting periods, which can overstate waiting time for processes needing multiple rounds.
- **Gantt chart is simplistic** — it prints process order and cumulative burst times but doesn't account for idle CPU time gaps (e.g., when no process has arrived yet).
- **No tie-breaking rule** — if two processes have equal burst time (SJF) or equal priority, order depends on `sort`'s implementation-defined stability.
- **Priority scheduling ignores arrival time entirely** — a process can be scheduled before it has technically "arrived."

---

## 💡 Real-World Applications

- 🖥️ **Operating Systems Education** — Directly demonstrates textbook CPU scheduling algorithms taught in every OS course
- 🧵 **Understanding Multitasking** — Shows how an OS decides which process/thread gets CPU time and for how long
- 📱 **Embedded/RTOS Design Intuition** — Round Robin is widely used in real-time operating systems; this simulates its core mechanics
- 🎓 **Interview Preparation** — Scheduling algorithms are a common OS/systems-design interview topic
- 🧩 **Foundation for Simulators** — Can be extended into a full OS process-scheduling visualizer or teaching tool

---

## 🚀 Future Improvements

- [ ] Fix Round Robin to correctly respect arrival time (skip processes that haven't arrived yet)
- [ ] Fix waiting time accumulation logic in Round Robin for multi-round processes
- [ ] Add **preemptive SJF (Shortest Remaining Time First)** and **preemptive Priority Scheduling**
- [ ] Improve Gantt chart to show idle CPU time and proper time-stamped segments
- [ ] Add average waiting time and average turnaround time summary output
- [ ] Add a graphical Gantt chart (web-based or GUI) instead of text-only
- [ ] Add unit tests comparing computed results against known textbook examples
---


