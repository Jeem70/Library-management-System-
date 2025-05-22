
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
};

void addBook() {
    struct Book b;
    FILE *fp = fopen("library.txt", "a");
    if (!fp) {
        printf("File error!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar(); // consume newline
    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0;
    printf("Enter Book Author: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    fprintf(fp, "%d,%s,%s\n", b.id, b.title, b.author);
    fclose(fp);
    printf("Book added successfully.\n");
}

void viewBooks() {
    struct Book b;
    FILE *fp = fopen("library.txt", "r");
    if (!fp) {
        printf("No books found.\n");
        return;
    }

    printf("\n%-10s%-30s%-30s\n", "ID", "Title", "Author");
    printf("-----------------------------------------------------------\n");
    while (fscanf(fp, "%d,%[^,],%[^\n]\n", &b.id, b.title, b.author) != EOF) {
        printf("%-10d%-30s%-30s\n", b.id, b.title, b.author);
    }
    fclose(fp);
}

void searchBook() {
    struct Book b;
    int id, found = 0;
    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen("library.txt", "r");
    if (!fp) {
        printf("No books found.\n");
        return;
    }

    while (fscanf(fp, "%d,%[^,],%[^\n]\n", &b.id, b.title, b.author) != EOF) {
        if (b.id == id) {
            printf("\nBook Found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\n", b.id, b.title, b.author);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found.\n");

    fclose(fp);
}

void deleteBook() {
    struct Book b;
    int id, found = 0;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    while (fscanf(fp, "%d,%[^,],%[^\n]\n", &b.id, b.title, b.author) != EOF) {
        if (b.id != id) {
            fprintf(temp, "%d,%s,%s\n", b.id, b.title, b.author);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("Book deleted successfully.\n");
    else
        printf("Book not found.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n2. View Books\n3. Search Book\n4. Delete Book\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
