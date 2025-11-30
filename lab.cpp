#include <iostream>
#include <string>
using namespace std;
class LibraryItem {
private:
    string title;
    string author;
    string dueDate;

public:
   
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getDueDate() { return dueDate; }


    LibraryItem(string t, string a, string d) : title(t), author(a), dueDate(d) {}

    
    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;

    virtual ~LibraryItem() {} 
};


class Book : public LibraryItem {
private:
    string ISBN;

public:
    Book(string t, string a, string d, string isbn) : LibraryItem(t,a,d) {
        if(isbn.length() != 13) {
            throw invalid_argument("ISBN must be 13 digits!");
        }
        ISBN = isbn;
    }

    void checkOut() override {
        cout << "Book Checked Out: " << getTitle() << endl;
    }

    void returnItem() override {
        cout << "Book Returned: " << getTitle() << endl;
    }

    void displayDetails() const override {
        cout << "\n--- Book Details ---" << endl;
        cout << "Title: " << getTitle() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "Due Date: " << getDueDate() << endl;
    }
};


class DVD : public LibraryItem {
private:
    int duration;

public:
    DVD(string t, string a, string d, int dur) : LibraryItem(t,a,d) {
        if(dur < 0) throw invalid_argument("Duration cannot be negative!");
        duration = dur;
    }

    void checkOut() override {
        cout << "DVD Checked Out: " << getTitle() << endl;
    }

    void returnItem() override {
        cout << "DVD Returned: " << getTitle() << endl;
    }

    void displayDetails() const override {
        cout << "\n--- DVD Details ---" << endl;
        cout << "Title: " << getTitle() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "Due Date: " << getDueDate() << endl;
        cout << "Duration: " << duration << " minutes" << endl;
    }
};


int main() {
    LibraryItem* libraryItems[MAX_ITEMS];
    int count = 0;
    int choice;

    try {
        while(true) {
            cout << "\n====== LIBRARY MANAGEMENT SYSTEM ======" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. Add DVD" << endl;
            cout << "3. Display All Items" << endl;
            cout << "4. Check Out Item" << endl;
            cout << "5. Return Item" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            if(choice == 6) break;

            switch(choice) {
                case 1: {
                    string t,a,d,isbn;
                    cout << "Enter title: ";
                    cin >> t;
                    cout << "Enter author: ";
                    cin >> a;
                    cout << "Enter due date: ";
                    cin >> d;
                    cout << "Enter ISBN (13 digits): ";
                    cin >> isbn;

                    libraryItems[count++] = new Book(t,a,d,isbn);
                    cout << "Book Added Successfully!" << endl;
                }
                break;

                case 2: {
                    string t,a,d;
                    int dur;
                    cout << "Enter title: ";
                    cin >> t;
                    cout << "Enter author: ";
                    cin >> a;
                    cout << "Enter due date: ";
                    cin >> d;
                    cout << "Enter duration: ";
                    cin >> dur;

                    libraryItems[count++] = new DVD(t,a,d,dur);
                    cout << "DVD Added Successfully!" << endl;
                }
                break;

                case 3:
                    for(int i=0; i<count; i++) {
                        libraryItems[i]->displayDetails();
                    }
                    break;

                case 4:
                case 5:
                    int index;
                    cout << "Enter item index (0 - " << count-1 << "): ";
                    cin >> index;
                    if(index < 0 || index >= count) throw out_of_range("Invalid Index!");

                    if(choice == 4) libraryItems[index]->checkOut();
                    else libraryItems[index]->returnItem();
                    break;

                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }
    catch(exception &e) {
        cout << "Error: " << e.what() << endl;
    }

   
    

    return 0;
}
