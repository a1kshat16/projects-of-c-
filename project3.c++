#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Book class
class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int _id, string _title, string _author) {
        id = _id;
        title = _title;
        author = _author;
        isIssued = false;
    }
};

// Library class
class Library {
    unordered_map<int, Book*> bookDB;     // Hash table for books
    unordered_map<int, queue<string>> reservationList; // Book ID to names of people who reserved

public:
    // Add a new book
    void addBook(int id, string title, string author) {
        if (bookDB.find(id) != bookDB.end()) {
            cout << "Book with this ID already exists.\n";
            return;
        }
        bookDB[id] = new Book(id, title, author);
        cout << "Book added successfully!\n";
    }

    // Search a book by title
    void searchBookByTitle(string title) {
        bool found = false;
        for (auto &pair : bookDB) {
            if (pair.second->title == title) {
                cout << "Book Found -> ID: " << pair.second->id << ", Author: " << pair.second->author << ", Status: " 
                     << (pair.second->isIssued ? "Issued" : "Available") << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Book not found!\n";
        }
    }

    // Issue a book
    void issueBook(int id, string userName) {
        if (bookDB.find(id) != bookDB.end()) {
            if (!bookDB[id]->isIssued) {
                bookDB[id]->isIssued = true;
                cout << "Book issued to " << userName << " successfully.\n";
            } else {
                cout << "Book is currently issued. Adding " << userName << " to reservation queue.\n";
                reservationList[id].push(userName);
            }
        } else {
            cout << "Book ID not found!\n";
        }
    }

    // Return a book
    void returnBook(int id) {
        if (bookDB.find(id) != bookDB.end()) {
            if (reservationList[id].empty()) {
                bookDB[id]->isIssued = false;
                cout << "Book returned successfully and is now available.\n";
            } else {
                string nextUser = reservationList[id].front();
                reservationList[id].pop();
                cout << "Book issued to next user in queue: " << nextUser << endl;
            }
        } else {
            cout << "Book ID not found!\n";
        }
    }

    // Delete a book
    void deleteBook(int id) {
        if (bookDB.find(id) != bookDB.end()) {
            delete bookDB[id];
            bookDB.erase(id);
            cout << "Book deleted successfully!\n";
        } else {
            cout << "Book ID not found!\n";
        }
    }

    // Display all books
    void displayBooks() {
        if (bookDB.empty()) {
            cout << "No books in the library!\n";
            return;
        }
        cout << "\nList of Books:\n";
        for (auto &pair : bookDB) {
            cout << "ID: " << pair.second->id 
                 << ", Title: " << pair.second->title 
                 << ", Author: " << pair.second->author 
                 << ", Status: " << (pair.second->isIssued ? "Issued" : "Available") << endl;
        }
    }

    // Destructor to free memory
    ~Library() {
        for (auto &pair : bookDB) {
            delete pair.second;
        }
    }
};

// Main Function
int main() {
    Library lib;
    int choice, id;
    string title, author, userName;

    while (true) {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by Title\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Delete Book\n";
        cout << "6. Display All Books\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // to ignore '\n' left in the input buffer

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Author Name: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;

            case 2:
                cout << "Enter Book Title to Search: ";
                getline(cin, title);
                lib.searchBookByTitle(title);
                break;

            case 3:
                cout << "Enter Book ID to Issue: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Your Name: ";
                getline(cin, userName);
                lib.issueBook(id, userName);
                break;

            case 4:
                cout << "Enter Book ID to Return: ";
                cin >> id;
                lib.returnBook(id);
                break;

            case 5:
                cout << "Enter Book ID to Delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;

            case 6:
                lib.displayBooks();
                break;

            case 7:
                cout << "Exiting the system. Thank you!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

