//
//  main.cpp
//  library
//
// write a program for a library
// in which books that are given by a file are initialized on the heap
// they are able to be borrowed
// books when returned need to be sorted back into the library in an orderly fashion, use this by doing sort with the pointer
// books need to be found using pointers
//  Created by Jensine Sultana on 10/22/18.
//  Copyright © 2018 Jensine. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Book {
    friend ostream& operator<<(ostream& os, const Book& rhs) {
        os << "Title: " << rhs.title << " Author: " << rhs.author;
        return os;
    }
public:
    Book(const string& title, const string& author) : title(title), author(author) {}
    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    void bookBorrowed() {
        available = false;
    }
    void bookReturned() {
        available = true;
    }
    bool status() const {
        return available;
    }
private:
    string title;
    string author;
    bool available = true;
};

class Constituent {
    // return name of constituent and the books borrowed
    friend ostream& operator<<(ostream& os, const Constituent& rhs) {
        os << rhs.name << " has borrowed: ";
        if (rhs.borrowedBooks.size() == 0) {
            os << "Nothing" << endl;
        }
        else {
            for (size_t i = 0; i < rhs.borrowedBooks.size(); ++i) {
                os << rhs.borrowedBooks[i]->getTitle() << "; ";
            }
        }
        return os;
    }
public:
    Constituent(const string& name) : name(name) {}
    
    const string& getName() const { return name; }
    
    void borrowBook(Book* borrowed) {
        // add borrowed to borrowedBooks
        borrowedBooks.push_back(borrowed);
    }
    
    // return a book
private:
    string name;
    vector<Book*> borrowedBooks;
};

class Library {
    // ostream class to get all the information of library
    friend ostream& operator<<(ostream& os, const Library& rhs) {
        os << rhs.location << " Library: " << endl;
        os << "Total Collection: " << endl;
        for (size_t i = 0; i < rhs.collection.size(); ++i) {
            os << *(rhs.collection[i]) << endl;
        }
        os << "Constituents:" << endl;
        for (size_t i = 0; i < rhs.constituents.size(); ++i) {
            os << *(rhs.constituents[i]) << endl;
        }
        return os;
    }
public:
    Library(const string& location) : location(location) {}
    
    // destructor
    ~Library() {
        cout << "entered destructor" << endl;
        for (size_t i = 0; i < collection.size(); ++i) {
            delete collection[i];
        }
        collection.clear();
        for (size_t i = 0; i < constituents.size(); ++i) {
            delete constituents[i];
        }
        constituents.clear();
    }
    // copy constructor
    Library(const Library& rhs) : location(rhs.location) {
        cout << "entered copy constructor" << endl;
        // fill in collection vector with rhs.collection
        for (size_t i = 0; i < rhs.collection.size(); ++i) {
            collection.push_back(new Book(*rhs.collection[i]));
        }
        for (size_t i = 0; i < rhs.constituents.size(); ++i) {
        // fill in constituents vector with rhs.constituent
            constituents.push_back(new Constituent(*rhs.constituents[i]));
        }
    }
    
    // assignment operator
    Library& operator=(const Library& rhs) { // remember that when writing the assignment operator (it is the same as the class with a reference + operator and then the = sign with the parametrs of the class passed by constant reference)
        cout << "entered the assignment operator" << endl;
        if (this != &rhs) {
            for (size_t i = 0; i < collection.size(); ++i) {
                delete collection[i];
            }
            collection.clear();
            for (size_t i = 0; i < constituents.size(); ++i) {
                delete constituents[i];
            }
            constituents.clear();
            location = rhs.location;
            for (size_t i = 0; i < rhs.collection.size(); ++i) {
                collection.push_back(new Book(*rhs.collection[i]));
            }
            for (size_t i = 0; i < rhs.constituents.size(); ++i) {
                // fill in constituents vector with rhs.constituent
                constituents.push_back(new Constituent(*rhs.constituents[i]));
            }
        }
        return *this;
    }
    
    void addBook(const string& title, const string& author) {
        // add new book on the heap
        // add it to the registry
        collection.push_back(new Book(title, author));
    }
    void addConstituent(const string& name) {
        // add new constituent on the heap
        // add it to the registry
        constituents.push_back(new Constituent(name));
    }
    
    // book lend to constituent
    bool borrow(const string& title, const string& name) {
        // check if the book is lent out or not
        for (size_t i = 0; i < collection.size(); ++i) {
            if (collection[i]->getTitle() == title) {
                if (!collection[i]->status()) {
                    return false;
                }
                else {
                    for (size_t j = 0; j < constituents.size(); ++j) {
                        if (constituents[j]->getName() == name) {
                            // add the book to the vector of book pointers
                            constituents[j]->borrowBook(collection[i]);
                            return true;
                        }
                    }
                }
            }
        }
        return false; // if book is not found
    }
    
    // return a book

private:
    vector<Constituent*> constituents;
    vector<Book*> collection;
    string location;
};

int main() {
    Library queens("Queens");
//    openFile(queens);
//
//    cout << queens << endl;
    queens.addBook("Black Marxism", "Cedric Robinson");
    queens.addBook("The Communist Manifesto", "Karl Marx");
    queens.addBook("State and Revolution", "V.I. Lenin");
    queens.addBook("Why Foucault Was Wrong", "Jensine Raihan");
    queens.addConstituent("Jensine");
    queens.addConstituent("Bitul");
    queens.addConstituent("Anshu");
    queens.borrow("Black Marxism", "Jensine");
    queens.borrow("The Communist Manifesto", "Jensine");
    queens.borrow("Why Foucault Was Wrong", "Bitul");
    queens.addBook("Post Modernism: Is it Intellectual Masurbation?", "Jensine Raihan");
    queens.borrow("Post Modernism: Is it Intellectual Masurbation?", "Bitul");
    cout << queens << endl;
    Library queensBackUp = queens;
    cout << "printing backup" << endl;
    cout << queensBackUp << endl;
    queensBackUp.addConstituent("Mahira");
    queensBackUp.addBook("Art by the BPP", "E. Douglas");
    queensBackUp.borrow("Art by the BPP", "Mahira");
    cout << queensBackUp << endl;
    cout << queens << endl;
    queens = queensBackUp;
    cout << queens << endl;
}
