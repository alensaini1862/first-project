#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student1
{
    int rollNo;
    char name[50];
    int age;
    float marks;
};
void addstudent(){
    FILE *fp = fopen("student1.txt","ab");
    struct student1 s;
    printf("Enter Roll No: ");
    scanf("%d",&s.rollNo);
    getchar();

    printf("Enter Name: ");
    fgets(s.name,sizeof(s.name), stdin);
    s.name[strcspn(s.name,"\n")] ='\0';

    printf("Enter Age: ");
    scanf("%d",&s.age);
    printf("Enter Marks: ");
    scanf("%f",&s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully.\n");
    
}
void displayAll(){
    FILE *fp = fopen("student1.txt","rb");
    struct student1 s;

    while (fread(&s, sizeof(s), 1, fp)){
        printf("\nRoll No: %d \nName: %s \nAge: %d \nMarks: %.2f" ,s.rollNo ,s.name ,s.age ,s.marks);
    }
    
    fclose(fp);
}
void searchstudent(){
    FILE *fp = fopen("student1.txt","rb");
    struct student1 s;
    int roll ,choice,found =0;
    char name[50];

     printf("Search by:\n1. Roll No\n2. Name\nChoice: ");
    scanf("%d", &choice);
    getchar();
    if (choice==1){
        printf("Enter Roll no: ");
        scanf("%d",&roll);
    }else{
        printf("Enter Name: ");
        fgets(name,sizeof(name), stdin);
        name[strcspn(name,"\n")] ='\0';
    }
    while ((fread(&s, sizeof(s), 1, fp))){
        if ((choice==1 && s.rollNo==roll)||(choice==2 && s.name == name))
        {
            printf("\nRoll No: %d \nName: %s \nAge: %d \nMarks: %.2f" ,s.rollNo ,s.name ,s.age ,s.marks);
            found = 1;
        } 
    }
    if (!found) {
        printf("Student not found.\n");
    }

    fclose(fp);  
}
void editstudent(){
    FILE *fp = fopen("student1.txt","rb+");
    struct student1 s;
    int roll ,found = 0;

    printf("Enter Roll no: ");
    scanf("%d",&roll);
    while ((fread(&s, sizeof(s), 1, fp))){
        if (s.rollNo==roll)
        {
            printf("Current details:\n");
            printf("\nRoll No: %d \nName: %s \nAge: %d \nMarks: %.2f" ,s.rollNo ,s.name ,s.age ,s.marks);
            printf("\nEnter new details:\n");

            printf("Enter Name: ");
            getchar();
            fgets(s.name,sizeof(s.name),stdin);
            s.name[strcspn(s.name,"\n")] ='0';

            printf("Enter Age: ");
            scanf("%d",&s.age);
            printf("Enter Marks: ");
            scanf("%f",&s.marks);

            fwrite(&s, sizeof(s), 1, fp);
            fseek(fp, -sizeof(s), SEEK_CUR);
            printf("Record updated.\n");
            found = 1;
            break;
        }
        if (!found) {
        printf("Student not found.\n");
        }

      fclose(fp);
        
    } 
}
void deletestudent(){
    FILE *fp = fopen("student1.txt","rb");
    FILE *temp =fopen("temp.txt","wb");
    struct student1 s;
    int roll ,found = 0;

    printf("Enter Roll No to delete: ");
    scanf("%d", &roll);
    while (((fread(&s, sizeof(s), 1, fp))))
    {
        if (s.rollNo != roll)
        {
            fwrite(&s,sizeof(s),1, temp);
        }else {
            found = 1;
        }        
    }
    fclose(fp);
    fclose(temp);

    remove("student1.txt");
    rename("temp.txt", "student1.txt");
    if (found)
    {
         printf("Record deleted.\n");
    } else {
        printf("Student not found.\n");
    
    }
      
}
int main(){
    int choice ;
    do
    {
        printf("\n--- Student Record Management System ---\n");
        printf("1. AddStudent\n");
        printf("2. DisplayStudent\n");
        printf("3. SearchStudent\n");
        printf("4. EditStudent\n");
        printf("5. DeleteStudent\n");
        printf("6. Exxit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            addstudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchstudent();
            break;
        case 4:
            editstudent();
            break;
        case 5:
            deletestudent();
            break;
        case 6:
            printf("Exiting......");
            break;
        default:
            printf("Invalid Choice");
            break;
        }
    } while (choice !=6);
    return 0;
}