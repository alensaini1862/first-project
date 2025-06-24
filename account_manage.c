#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FILENAME "accounts.dat"

typedef struct{
    int accNo;
    char name[50];
    float balance;
}Account;
void createAccount(){
    FILE *fp = fopen(FILENAME,"ab");
    if (fp == NULL){
        printf("File open error\n");
        return;
    }

    Account acc;
    printf("Enter Account Number: ");
    scanf("%d",&acc.accNo);
    getchar();

    printf("Enter Name: ");
    fgets(acc.name ,sizeof(acc.name),stdin);
    acc.name[strcspn(acc.name,"\n")]='\0';

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc),1 ,fp);
    fclose(fp);
    printf("Account created successfully!\n");
}
void depositwithdraw(int type){
    FILE *fp = fopen(FILENAME,"rb+");
    if (fp == NULL){
        printf("File open error\n");
        return;
    }
    int accNo, found =0;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    Account acc;
    while (fread(&acc, sizeof(acc),1 ,fp)){
        if (acc.accNo == accNo){
            found = 1;
            printf("Current Balance: %.2f\n", acc.balance);
            printf("Enter Amount: ");
            scanf("%f", &amount);

            if (type==1){
                acc.balance += amount;
                printf("Deposited Successfully!\n");
            }else{
                if (amount > acc.balance)
                {
                    printf("Insufficient Balance!\n");
                    fclose(fp);
                    return;
                }
                acc.balance -= amount;
                printf("Withdraw Successfully!\n");
                
            }
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            break;            
        }
    }
    if (! found)
    {
        printf("Account not found!\n");
    }
    fclose(fp);
    
}
void cheakbalance(){
    FILE *fp = fopen(FILENAME,"rb");
    if (fp == NULL){
        printf("File open error\n");
        return;
    }
    int accNo ,found=0;
    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    Account acc;
    while (fread(&acc, sizeof(acc),1 ,fp)){
        if (acc.accNo == accNo){
            found = 1;
            printf("Account Number: %d\n", acc.accNo);
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            break;
        }
    }
    if (! found)
    {
        printf("Account not found!\n");
    }
    
    
    fclose(fp);
}
void ViewallAccount(){
     FILE *fp = fopen(FILENAME,"rb");
    if (fp == NULL){
        printf("File open error\n");
        return;
    }

    Account acc;
    printf("\n----- All Accounts -----\n");
    while (fread(&acc, sizeof(acc),1 ,fp)){
        printf("Account No: %d |Custmor Name: %s | Balance: %.2f\n" ,acc.accNo ,acc.name ,acc.balance);
    } 

    fclose(fp);

}
void deleteaccount(){
    FILE *fp = fopen(FILENAME,"rb");
    FILE *temp =fopen("temp.txt","wb");
    if (fp == NULL){
        printf("File open error\n");
        return;
    }
    int accNo ,found=0;
    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    Account acc;
    while ((fread(&acc, sizeof(acc),1 ,fp))){
        if (accNo != acc.accNo)
        {
            fwrite(&acc,sizeof(acc),1, temp);
        }else {
            found = 1;
        } 
    }
    fclose(fp);
    fclose(temp);


    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
    {
         printf("Account deleted.\n");
    } else {
        printf("Account not found.\n");
    
    }
}
int main(){
    int choice;
    do
    {
        printf("\n---- Bank Management System ----\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. View All Accounts\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            depositwithdraw(1);
            break;
        case 3:
            depositwithdraw(0);
            break;
        case 4:
            cheakbalance();
            break;
        case 5:
            ViewallAccount();
            break;
        case 6:
            deleteaccount();
            break;
        case 7:
           printf("Exiting.....");
           break; 
        default:
            break;
        }
    } while (choice != 7);


    return 0;  
}
