#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    int id;
    char title[50];
    char author[50];
    int isIssued;
};
int idExists(int id);
void addBook();
void viewBooks();
void searchBook();
void issueBook();
void returnBook();
void deleteBook();
void menu();

int main(){
    int choice;
    while(1){
        menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        switch(choice){
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void menu() {
    printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("1. Add Book\n");
    printf("2. View All Books\n");
    printf("3. Search Book by ID\n");
    printf("4. Issue Book\n");
    printf("5. Return Book\n");
    printf("6. Delete Book\n");
    printf("7. Exit\n");
}
int idExists(int id) {
    FILE *fp = fopen("library.dat", "rb");
    struct book b;

    if (!fp) return 0;

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id ) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addBook() {
    struct book b;
    FILE *fp = fopen("library.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    if (idExists(b.id)) {
        printf("Book ID already exists.\n");
        fclose(fp);
        return;
    }

    printf("Enter Book ID: ");
    if (scanf("%d", &b.id) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid ID. Aborting add.\n");
        fclose(fp);
        return;
    }
    while (getchar() != '\n');
    printf("Enter Book Title: ");
    if (fgets(b.title, sizeof(b.title), stdin) == NULL) b.title[0] = '\0';
    b.title[strcspn(b.title, "\n")] = '\0';
    printf("Enter Book Author: ");
    if (fgets(b.author, sizeof(b.author), stdin) == NULL) b.author[0] = '\0';
    b.author[strcspn(b.author, "\n")] = '\0';
    printf("Enter Book Issued Status (0 for not issued, 1 for issued): ");
    if (scanf("%d", &b.isIssued) != 1) b.isIssued = 0;
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

void viewBooks() {
    struct book b;
    FILE *fp = fopen("library.dat", "rb");
    if (fp == NULL) {
      printf("Error opening file!\n");
      return;
    }

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("ID: %d\nTitle: %s\nAuthor: %s\nIssued Status: %d\n\n", b.id, b.title, b.author, b.isIssued);
    }
    fclose(fp);
}

void searchBook() {
   struct book b;
   int id, found = 0;
   FILE *fp = fopen("library.dat", "rb");
   if (fp == NULL) {
      printf("Error opening file!\n");
      return;
   }
   printf("Enter Book ID to search: ");
   if (scanf("%d", &id) != 1) {
       int c; while ((c = getchar()) != '\n' && c != EOF);
       printf("Invalid ID.\n");
       fclose(fp);
       return;
   }
   while (fread(&b, sizeof(b), 1, fp) == 1) {
     if (b.id == id) {
           printf("ID: %d\nTitle: %s\nAuthor: %s\nIssued Status: %d\n\n", b.id, b.title, b.author, b.isIssued);
           found = 1;
           break;
     }
   }
   if (!found) {
      printf("Book with ID %d not found.\n", id);
   }
   fclose(fp);
}

void issueBook() {
   FILE *fp;
   struct book b;
   int id;
   fp = fopen("library.dat", "rb+");
   if (fp == NULL) {
       printf("Error opening file!\n");
       return;
   }
   printf("Enter Book ID to issue: ");
   if (scanf("%d", &id) != 1) { fclose(fp); return; }
   while (fread(&b, sizeof(b), 1, fp) == 1) {
       if (b.id == id && b.isIssued == 0) {
          b.isIssued = 1;
          fseek(fp, -sizeof(b), SEEK_CUR);
          fwrite(&b, sizeof(b), 1, fp);
          printf("Book issued successfully\n");
          fclose(fp);
          return;
       }
    }
    printf("Book not available\n");
    fclose(fp);
}

void returnBook() {
     FILE *fp;
     struct book b;
     int id;
     fp = fopen("library.dat", "rb+");
     if (fp == NULL) { printf("Error opening file!\n"); return; }
     printf("Enter Book ID to return: ");
     if (scanf("%d", &id) != 1) { fclose(fp); return; }
     while (fread(&b, sizeof(b), 1, fp) == 1) {
          if (b.id == id && b.isIssued == 1) {
              b.isIssued = 0;
              fseek(fp, -sizeof(b), SEEK_CUR);
              fwrite(&b, sizeof(b), 1, fp);
              printf("Book returned successfully\n");
              fclose(fp);
              return;
          }
      }
      printf("Book not found or not issued\n");
      fclose(fp);
}

void deleteBook() {
     struct book b;
     int id, found = 0;
     FILE *fp = fopen("library.dat", "rb");
     FILE *temp = fopen("temp.dat", "wb");
     if (fp == NULL || temp == NULL) {
         printf("Error opening file!\n");
         if (fp) fclose(fp);
         if (temp) fclose(temp);
         return;
     }
     printf("Enter Book ID to delete: ");
     if (scanf("%d", &id) != 1) { fclose(fp); fclose(temp); return; }
     while (fread(&b, sizeof(b), 1, fp) == 1) {
         if (b.id == id) {
             found = 1;
             continue;
         }
         fwrite(&b, sizeof(b), 1, temp);
     }
     fclose(fp);
     fclose(temp);
     remove("library.dat");
     rename("temp.dat", "library.dat");
     if (found) {
         printf("Book deleted successfully\n");
     } else {
         printf("Book with ID %d not found.\n", id);
     }
}







