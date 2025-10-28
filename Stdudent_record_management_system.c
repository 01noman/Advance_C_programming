#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

void addStudent();
void viewStudent();
void searchStudent();
void deleteStudent();
void updateStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudent();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            updateStudent();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid Choice!\n");
        }
    }
}

void addStudent() {
    FILE *fp = fopen("students.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
    fclose(fp);
    printf("Student added successfully!\n");
}

void viewStudent() {
    FILE *fp = fopen("students.txt", "r");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    struct Student s;
    printf("\nID\tName\tAge\tMarks\n");
    printf("------------------------------------\n");

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) == 4) {
        printf("%d\t%s\t%d\t%.2f\n", s.id, s.name, s.age, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.txt", "r");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    struct Student s;
    int id, found = 0;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) == 4) {
        if (s.id == id) {
            printf("\nFound: %d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) == 4) {
        if (s.id != id) {
            fprintf(temp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found!\n");
}

void updateStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) == 4) {
        if (s.id == id) {
            found = 1;
            printf("Enter new Name: ");
            scanf("%s", s.name);
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
    }

    fclose(fp);
    fclose(temp);
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Student updated successfully!\n");
    else
        printf("Student not found!\n");
}
