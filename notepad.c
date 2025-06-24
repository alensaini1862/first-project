#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 1000

void createNewFile();
void openFile();
void saveFile();
void displayMenu();

char text[MAX_LINES][MAX_LENGTH];
int lineCount = 0;

int main() {
    int choice;
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character
        
        switch(choice) {
            case 1:
                createNewFile();
                break;
            case 2:
                openFile();
                break;
            case 3:
                saveFile();
                break;
            case 4:
                printf("Exiting Notepad...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 4);
    
    return 0;
}

void displayMenu() {
    printf("\n===== C Notepad =====\n");
    printf("1. Create New File\n");
    printf("2. Open File\n");
    printf("3. Save File\n");
    printf("4. Exit\n");
}

void createNewFile() {
    lineCount = 0;
    printf("\nEnter your text (Enter an empty line to finish):\n");
    
    while(lineCount < MAX_LINES) {
        printf("%d: ", lineCount + 1);
        fgets(text[lineCount], MAX_LENGTH, stdin);
        
        // Remove newline character
        text[lineCount][strcspn(text[lineCount], "\n")] = '\0';
        
        // Check for empty line to stop input
        if(strlen(text[lineCount]) == 0) {
            break;
        }
        
        lineCount++;
    }
    
    printf("\nFile created in memory. Don't forget to save!\n");
}

void openFile() {
    char filename[100];
    FILE *file;
    
    printf("Enter filename to open: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    
    file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    lineCount = 0;
    printf("\nFile content:\n");
    while(fgets(text[lineCount], MAX_LENGTH, file) != NULL && lineCount < MAX_LINES) {
        // Remove newline character if present
        text[lineCount][strcspn(text[lineCount], "\n")] = '\0';
        printf("%d: %s\n", lineCount + 1, text[lineCount]);
        lineCount++;
    }
    
    fclose(file);
    printf("\nFile loaded successfully!\n");
}

void saveFile() {
    char filename[100];
    FILE *file;
    
    if(lineCount == 0) {
        printf("No content to save!\n");
        return;
    }
    
    printf("Enter filename to save: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    
    file = fopen(filename, "w");
    if(file == NULL) {
        printf("Error creating file!\n");
        return;
    }
    
    for(int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", text[i]);
    }
    
    fclose(file);
    printf("File saved successfully!\n");
}