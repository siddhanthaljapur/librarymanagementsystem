#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int id;
    char author[100];
    char title[100];
    int is_checked_out;
    struct Book *next;
} Book;

void addBook(Book **head, int id, const char *author, const char *title) {
    Book *newbook = (Book *)malloc(sizeof(Book));
    newbook->id = id;
    strcpy(newbook->title, title);
    strcpy(newbook->author, author);
    newbook->is_checked_out = 0;
    newbook->next = NULL;

    if (*head == NULL) {
        *head = newbook;
    } else {
        Book *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newbook;
    }
}

void deleteBook(Book **head, int id) {
    if (*head == NULL) return;

    Book *temp = *head;
    Book *prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

Book* searchBook(int id, Book *head) {
    Book *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void checkoutBook(Book *head, int id) {
    Book *book = searchBook(id, head);
    if (book != NULL && book->is_checked_out == 0) {
        book->is_checked_out = 1;
        printf("This book is now checked out.\n");
    } else {
        printf("This book is not available.\n");
    }
}

void returnBook(Book *head, int id) {
    Book *book = searchBook(id, head);
    if (book != NULL && book->is_checked_out == 1) {
        book->is_checked_out = 0;
        printf("Book returned successfully.\n");
    } else {
        printf("This book was not checked out.\n");
    }
}

void displayBooks(Book *head) {
    Book *temp = head;
    while (temp != NULL) {
        printf("ID = %d, Title = %s, Author = %s, Checked Out = %d\n",
               temp->id, temp->title, temp->author, temp->is_checked_out);
        temp = temp->next;
    }
}

int main() {
    Book *library = NULL;
    int choice, id;
    char title[100], author[100];

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add a Book\n");
        printf("2. Remove a Book\n");
        printf("3. Check Out a Book\n");
        printf("4. Return a Book\n");
        printf("5. Display All Books\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter book ID: ");
                scanf("%d", &id);
                printf("Enter book title: ");
                getchar();
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter book author: ");
                fgets(author, 100, stdin);
                author[strcspn(author, "\n")] = 0;
                addBook(&library, id, author, title);
                break;

            case 2:
                printf("Enter book ID to remove: ");
                scanf("%d", &id);
                deleteBook(&library, id);
                break;

            case 3:
                printf("Enter book ID to check out: ");
                scanf("%d", &id);
                checkoutBook(library, id);
                break;

            case 4:
                printf("Enter book ID to return: ");
                scanf("%d", &id);
                returnBook(library, id);
                break;

            case 5:
                displayBooks(library);
                break;

            case 6:
                printf("Exiting...\n");
                while (library != NULL) {
                    Book *temp = library;
                    library = library->next;
                    free(temp);
                }
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
