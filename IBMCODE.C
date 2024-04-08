#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char description[100];
    float amount;
    char type; // 'I' for income, 'E' for expense
} FinancialRecord;

void addRecord() {
    FinancialRecord record;
    printf("\nEnter description: ");
    scanf("%99s", record.description); // Using %99s to prevent overflow
    printf("Enter amount: ");
    scanf("%f", &record.amount);
    printf("Enter type (I for Income / E for Expense): ");
    scanf(" %c", &record.type); // Space before %c to consume the newline character left in the input buffer

    FILE *file = fopen("records.txt", "a"); // Append mode
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }
    fprintf(file, "%s %f %c\n", record.description, record.amount, record.type);
    fclose(file);

    printf("Record added successfully!\n");
}

void showSummary() {
    FILE *file = fopen("records.txt", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    FinancialRecord record;
    float totalIncome = 0.0f, totalExpenses = 0.0f;
    while (fscanf(file, "%99s %f %c\n", record.description, &record.amount, &record.type) != EOF) {
        if (record.type == 'I') {
            totalIncome += record.amount;
        } else if (record.type == 'E') {
            totalExpenses += record.amount;
        }
    }
    fclose(file);

    printf("\nTotal Income: $%.2f\n", totalIncome);
    printf("Total Expenses: $%.2f\n", totalExpenses);
    printf("Net Savings: $%.2f\n", totalIncome - totalExpenses);
}

void displayMenu() {
    int choice;
    do {
        printf("\nSimple Budget Tracker\n");
        printf("1. Add Record\n");
        printf("2. Show Summary\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addRecord();
                break;
            case 2:
                showSummary();
                break;
            case 3:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);
}

int main() {
    displayMenu();
    return 0;
}
