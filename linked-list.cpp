#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    Book *next;

public:
    Book(int i, string name, string au) {
        id = i;
        title = name;
        author = au;
        this->next = NULL;
    }

    void setID(int i) {
        id = i;
    }

    void setTitle(string name) {
        title = name;
    }

    void setAuthor(string au) {
        author = au;
    }

    void setNext(Book *n) {
        next = n;
    }

    int getID() {
        return id;
    }

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    Book *getNext() {
        return next;
    }
};


class BookList {
private:
    Book *head;
    int size;

public:
    BookList() {
        this->head = NULL;
        size = 0;
    }

    void add(string input) {
        int tempPos1 = input.find(":");
        int tempPos2 = input.find(" ");
        int pos = stoi(input.substr(tempPos1 + 1, tempPos2));
        input.erase(0, tempPos2);
    
        string values[3];
        int idx = 0;
        while (input.find("book_") != -1) {
            int tempPos1 = input.find(":");
            int tempPos2 = input.find(", book_");
            values[idx] = input.substr(tempPos1 + 1, tempPos2 - tempPos1 - 1);
            input.erase(0, tempPos2 + 2);
            idx++;
        }

        Book *newBook = new Book(stoi(values[0]), values[1], values[2]);
        Book *currentBook = head;
        int place = 0;
        bool exists = false;

        while (currentBook != NULL && exists == false) {
            if (currentBook->getID() == newBook->getID())
                exists = true;
            currentBook = currentBook->getNext();
        }

        currentBook = head;
        if (exists) {
            return;
        }

        if (pos == 0 || size == 0) {
            newBook->setNext(head);
            head = newBook;
        }
        
        else if (pos >= size || pos < 0) {
            while (currentBook->getNext() != NULL) {
                currentBook = currentBook->getNext();
            }
            currentBook->setNext(newBook);
        }

        else {
            while (place < (pos - 1)) {
                currentBook = currentBook->getNext();
                place++;
            }

            newBook->setNext(currentBook->getNext());
            currentBook->setNext(newBook);
        }

        size++;
    }

    void remove(string input) {
        int tempPos = input.find(":");
        string command = input.substr(0, tempPos);
        input.erase(0, tempPos + 1);

        Book *currentBook = head;
        if (command == "pos") {
            int pos = stoi(input);
            if (pos >= size) {
                return;
            }

            int idx = 0;
            while (currentBook != NULL && idx < (pos - 1)) {
                currentBook = currentBook->getNext();
                idx++;
            }

            Book *temp = currentBook->getNext();
            currentBook->setNext(temp->getNext());
            delete temp;
            size--;
        }

        else if (command == "book_id") {
            int tempPos = input.find(":");
            input.erase(0, tempPos + 1);
            int book_id = stoi(input);
            
            while (currentBook != NULL and currentBook->getID() == book_id) {
                head = currentBook->getNext();
                currentBook = head;
                size--;
            }

            while (currentBook != NULL) {
                if (currentBook->getNext() != NULL) {
                    if (currentBook->getNext()->getID() == book_id) {
                        Book *temp = currentBook->getNext();
                        currentBook->setNext(temp->getNext());
                        delete temp;
                        size--;;
                    }
                    else {
                        currentBook = currentBook->getNext();
                    }
                }

                else if (currentBook->getID() == book_id) {
                    Book *temp = currentBook;
                    delete temp;
                    currentBook = NULL;
                    size--;
                }
                else {
                    currentBook = currentBook->getNext();
                }
            }
        }

        else if (command == "book_name") {
            input.erase(0, input.find(":") + 1);

            while (currentBook != NULL and currentBook->getTitle() == input) {
                head = currentBook->getNext();
                currentBook = head;
                size--;
            }

            while (currentBook != NULL) {
                if (currentBook->getNext() != NULL) {
                    if (currentBook->getNext()->getTitle() == input) {
                        Book *tempBook = currentBook->getNext();
                        currentBook->setNext(tempBook->getNext());
                        delete tempBook;
                        size--;
                    }

                    else {
                        currentBook = currentBook->getNext();
                    }
                }

                else if (currentBook->getTitle() == input) {
                    currentBook = NULL;
                    size--;
                }
                else {
                    currentBook = currentBook->getNext();
                }
            }
        }

        else if (command == "book_author") {
            input.erase(0, input.find(":") + 1);

            while (currentBook != NULL and currentBook->getAuthor() == input) {
                head = currentBook->getNext();
                currentBook = head;
                size--;
            }

            while (currentBook != NULL) {
                if (currentBook->getNext() != NULL) {
                    if (currentBook->getNext()->getAuthor() == input) {
                        Book *tempBook = currentBook->getNext();
                        currentBook->setNext(tempBook->getNext());
                        delete tempBook;
                        size--;
                    }

                    else {
                        currentBook = currentBook->getNext();
                    }
                }

                else if (currentBook->getAuthor() == input) {
                    currentBook = NULL;
                    size--;
                }
                else {
                    currentBook = currentBook->getNext();
                }
            }
        }
    }

    void swap(Book *a, Book *b) {
        string tempTitle, tempAuthor;
        int tempID;
        tempID = a->getID();
        tempTitle = a->getTitle();
        tempAuthor = a->getAuthor();

        a->setID(b->getID());
        a->setTitle(b->getTitle());
        a->setAuthor(b->getAuthor());

        b->setID(tempID);
        b->setTitle(tempTitle);
        b->setAuthor(tempAuthor);
    }
        
    void sort(string commandLine) {
        if (head == NULL) {
            return;
        }
        Book *current1;
        Book *current2 = NULL;
        bool swapped = false;

        if (commandLine == "book_id") {
            do {
                swapped = false;
                current1 = head;

                while (current1->getNext() != current2) {
                    if (current1->getNext() != NULL && current1->getID() > current1->getNext()->getID()) {
                        swap(current1, current1->getNext());
                        swapped = true;
                    }

                    current1 = current1->getNext();
                }

                current2 = current1;
            } while (swapped);
        }
        
        else if (commandLine == "book_name") {
            do {
                swapped = false;
                current1 = head;

                while (current1->getNext() != current2) {
                    if (current1->getNext() != NULL && current1->getTitle().compare(current1->getNext()->getTitle()) < 0) {
                        swap(current1, current1->getNext());
                        swapped = true;
                    }

                    current1 = current1->getNext();
                }

                current2 = current1;
            } while (swapped);
        }
        
        else if (commandLine == "book_author") {
            do {
                swapped = false;
                current1 = head;

                while (current1->getNext() != current2) {
                    if (current1->getNext() != NULL && current1->getAuthor().compare(current1->getNext()->getAuthor()) > 0) {
                        swap(current1, current1->getNext());
                        swapped = true;
                    }

                    current1 = current1->getNext();
                }

                current2 = current1;
            } while (swapped);
        }

        else {
            cout << "Command not recognized." << endl;
        }
    }
        
    void writeFile(string fileName) {
        ofstream out(fileName);
        Book *currentBook = head;
        while (currentBook != NULL) {
            out << "book_id:" << setfill('0') << setw(5) << currentBook->getID();
            out << ", book_name:" << currentBook->getTitle() << ", book_author:" << currentBook->getAuthor() << endl;
            currentBook = currentBook->getNext();
        }

        out.close();
    }
};


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Not enough arguments" << endl;
        return -1;
    }

    ArgumentManager am(argc, argv);
    string inFile = am.get("input");
    string commandFile = am.get("command");
    string outFile = am.get("output");

    ifstream in1(inFile);
    BookList list;

    while (!in1.eof()) {
        string str;
        string values[3];
        int count = 0;
        getline(in1, str);
        if (str.find("book_") < string::npos) {
            list.add("pos: -1 " + str);
        }
    }
    in1.close();
        
    ifstream in2(commandFile);
    while (!in2.eof()) {
        string str;
        getline(in2, str);
        if (str.find("book_") < string::npos) {
            cout << str << endl;
            string input = str.substr(0, str.find(" "));
            str.erase(0, input.length() + 1);

            if (input == "add") {
                list.add(str);
            }
            else if (input == "remove") {
                list.remove(str);
            }
            else if (input == "sort") {
                list.sort(str);
            }
            else {
                return -2;
            }
        }

        else if (str.find("pos") < string::npos) {
            cout << str << endl;
            string input = str.substr(0, str.find(" "));
            str.erase(0, input.length() + 1);

            if (input == "add") {
                list.add(str);
            }
            else if (input == "remove") {
                list.remove(str);
            }
            else if (input == "sort") {
                list.sort(str);
            }
            else {
                return -2;
            }
        }
    }

    list.writeFile(outFile);

    return 0;
}
