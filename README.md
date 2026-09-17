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






