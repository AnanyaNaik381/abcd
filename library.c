#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_PATRONS 100
#define MAX_TRANSACTIONS 100

typedef struct {
    char title[50];
    char author[50];
    char ISBN[13];
    int quantity;
} Book;

typedef struct {
    char name[50];
    int id;
    int booksBorrowed;
} Patron;

typedef struct {
    int patronID;
    char bookISBN[13];
    char borrowingDate[11]; // YYYY-MM-DD
} Transaction;

Book books[MAX_BOOKS];
Patron patrons[MAX_PATRONS];
Transaction transactions[MAX_TRANSACTIONS];

int bookCount = 0;
int patronCount = 0;
int transactionCount = 0;

void addBook() {
    if (bookCount < MAX_BOOKS) {
        printf("Enter book title: ");
        scanf(" %[^\n]s", books[bookCount].title);
        printf("Enter book author: ");
        scanf(" %[^\n]s", books[bookCount].author);
        printf("Enter book ISBN: ");
        scanf(" %s", books[bookCount].ISBN);
        printf("Enter quantity: ");
        scanf("%d", &books[bookCount].quantity);
        bookCount++;
        printf("Book added successfully.\n");
    } else {
        printf("Book inventory is full.\n");
    }
}

void removeBook() {
    char ISBN[13];
    printf("Enter ISBN of the book to remove: ");
    scanf(" %s", ISBN);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, ISBN) == 0) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            printf("Book removed successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void addPatron() {
    if (patronCount < MAX_PATRONS) {
        printf("Enter patron name: ");
        scanf(" %[^\n]s", patrons[patronCount].name);
        patrons[patronCount].id = patronCount + 1;
        patrons[patronCount].booksBorrowed = 0;
        patronCount++;
        printf("Patron added successfully. ID: %d\n", patrons[patronCount - 1].id);
    } else {
        printf("Patron list is full.\n");
    }
}

void removePatron() {
    int id;
    printf("Enter ID of the patron to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < patronCount; i++) {
        if (patrons[i].id == id) {
            for (int j = i; j < patronCount - 1; j++) {
                patrons[j] = patrons[j + 1];
            }
            patronCount--;
            printf("Patron removed successfully.\n");
            return;
        }
    }
    printf("Patron not found.\n");
}

void borrowBook() {
    int patronID;
    char ISBN[13];
    printf("Enter patron ID: ");
    scanf("%d", &patronID);
    printf("Enter book ISBN: ");
    scanf(" %s", ISBN);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, ISBN) == 0) {
            if (books[i].quantity > 0) {
                for (int j = 0; j < patronCount; j++) {
                    if (patrons[j].id == patronID) {
                        books[i].quantity--;
                        patrons[j].booksBorrowed++;
                        printf("Enter borrowing date (YYYY-MM-DD): ");
                        scanf(" %s", transactions[transactionCount].borrowingDate);
                        transactions[transactionCount].patronID = patronID;
                        strcpy(transactions[transactionCount].bookISBN, ISBN);
                        transactionCount++;
                        printf("Book borrowed successfully.\n");
                        return;
                    }
                }
                printf("Patron not found.\n");
                return;
            } else {
                printf("Book out of stock.\n");
                return;
            }
        }
    }
    printf("Book not found.\n");
}

void returnBook() {
    int patronID;
    char ISBN[13];
    printf("Enter patron ID: ");
    scanf("%d", &patronID);
    printf("Enter book ISBN: ");
    scanf(" %s", ISBN);

    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].patronID == patronID && strcmp(transactions[i].bookISBN, ISBN) == 0) {
            for (int j = 0; j < bookCount; j++) {
                if (strcmp(books[j].ISBN, ISBN) == 0) {
                    books[j].quantity++;
                    for (int k = 0; k < patronCount; k++) {
                        if (patrons[k].id == patronID) {
                            patrons[k].booksBorrowed--;
                            for (int l = i; l < transactionCount - 1; l++) {
                                transactions[l] = transactions[l + 1];
                            }
                            transactionCount--;
                            printf("Book returned successfully.\n");
                            return;
                        }
                    }
                }
            }
        }
    }
    printf("Transaction not found.\n");
}

void displayBooks() {
    printf("Books in inventory:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Title: %s, Author: %s, ISBN: %s, Quantity: %d\n",
               books[i].title, books[i].author, books[i].ISBN, books[i].quantity);
    }
}

void displayPatrons() {
    printf("Registered patrons:\n");
    for (int i = 0; i < patronCount; i++) {
        printf("Name: %s, ID: %d, Books borrowed: %d\n",
               patrons[i].name, patrons[i].id, patrons[i].booksBorrowed);
    }
}

void displayBorrowedBooks() {
    int patronID;
    printf("Enter patron ID: ");
    scanf("%d", &patronID);

    printf("Books borrowed by patron ID %d:\n", patronID);
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].patronID == patronID) {
            printf("Book ISBN: %s, Borrowing Date: %s\n",
                   transactions[i].bookISBN, transactions[i].borrowingDate);
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nLibrary System Menu:\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Add Patron\n");
        printf("4. Remove Patron\n");
        printf("5. Borrow Book\n");
        printf("6. Return Book\n");
        printf("7. Display Books\n");
        printf("8. Display Patrons\n");
        printf("9. Display Borrowed Books\n");
        printf("10. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                removeBook();
                break;
            case 3:
                addPatron();
                break;
            case 4:
                removePatron();
                break;
            case 5:
                borrowBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                displayBooks();
                break;
            case 8:
                displayPatrons();
                break;
            case 9:
                displayBorrowedBooks();
                break;
            case 10:
                printf("Exiting the system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}