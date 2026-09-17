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





