#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>

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
void sortStudent();
void serchByname();
void staticStudentList();
void convertCVS();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Sort Student List\n");
        printf("7. Search By Name\n");
        printf("8. Static of Student List\n");
        printf("9. Convert To CVS form\n");
        printf("10. Exit\n");
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
            sortStudent();
            break;
        case 7:
            serchByname();
            break;
        case 8:
            staticStudentList();
            break;
        case 9:
            convertCVS();
            break;
        case 10:
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

void sortStudent()
{
    FILE *fp = fopen("students.txt","r");
    if(!fp)
    {
        printf("Record Not Found\n");
        return;
    }

    //struct Student s;
    int count=0;
    struct Student list[100];
    while(fscanf(fp, "%d %s %d %f", &list[count].id, list[count].name, &list[count].age, &list[count].marks) == 4)
    {
        count++;
    }
    fclose(fp);

    for(int i= 0; i<count-1; i++)
    {
        for(int j=i+1; j<count; j++)
        {
            if(list[i].marks<list[j].marks)
            {
                struct Student temp = list[i];
                list[i]=list[j];
                list[j]=temp;
            }
        }
    }

    printf("\n Sorted By Marks (High to low\n");
    printf("\nID\tName\tAge\tMarks\n");
    printf("----------------------------------");

    for(int i=0; i<count; i++)
    {
        printf("\n%d\t%s\t%d\t%.2f\n",list[i].id,list[i].name,list[i].age,list[i].marks);
    }
}


void serchByname()
{
    FILE *fp = fopen("students.txt","r");
    if(!fp)
    {
        printf("Record not Found\n");
        return;
    }

    struct Student s;
    char name[50];
    printf("Enter a Name for search\n");
    scanf("%s",&name);
    int found = 0;
    int i=1;

    while(fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) == 4)
    {
        if(strstr(s.name,name)!=NULL)
        {
            printf("\nFound %d: %d %s %d %.2f\n",i, s.id, s.name, s.age, s.marks);
            found = 1;
            i++;
        }
    }

    if(!found)
    {
        printf("No Student Found for This Name %s: ",name);
    }

    fclose(fp);
}

void staticStudentList()
{
    FILE *fp = fopen("students.txt","r");
    if(!fp)
    {
        printf("No records Found\n");
        return;
    }  

    struct Student s;
    char topName[50], lowName[50];
    int sum =0;
    int count = 0;
    int max = INT_MIN,min=INT_MAX;
    while(fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) == 4)
    {
        sum += s.marks;
        if(s.marks>max)
        {
            max=s.marks;
            strcpy(topName,s.name);
        }
        if(s.marks<min)
        {
            min=s.marks;
            strcpy(lowName,s.name);
        }
        count++;
    }
    fclose(fp);

    if(count==0)
    {
        printf("Empty List\n");
    }

    printf("Average Marks: %d\n",sum/count);
    printf("Total Number of Student: %d\n",count);
    printf("Top Scorrer scrore and Name: %d %s\n",max,topName);
    printf("Lowest Scorrer Score and Name: %d %s\n",min,lowName);
}

void convertCVS()
{
    FILE *fp = fopen("students.txt","r");
    FILE *dest = fopen("students.csv","w");

    if(!fp || !dest)
    {
        printf("Error Opening File\n");
        return;
    }

    struct Student s;
    while(fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) == 4)
    {
        fprintf(dest,"%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
    }

    fclose(fp);
    fclose(dest);

    printf("\nExported data to students.csv successfully\n");
}
