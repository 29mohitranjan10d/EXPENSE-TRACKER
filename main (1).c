#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 500
#define FILE_NAME "expenses.txt"

// ─── STRUCT ───────────────────────────────────────────────
typedef struct {
    char date[12];       // Format: YYYY-MM-DD
    char category[30];   // Food, Travel, Medical, etc.
    float amount;
    char note[100];
} Expense;

// ─── GLOBAL DATA ──────────────────────────────────────────
Expense expenses[MAX_EXPENSES];
int expenseCount = 0;
float monthlyBudget = 0.0;

// ─── FUNCTION DECLARATIONS ────────────────────────────────
void addExpense();
void viewMonthlyExpenses();
void viewCategoryTotals();
void searchExpenses();
void setBudget();
void saveToFile();
void loadFromFile();
void showMenu();
int  validateDate(char *date);

// ─── MAIN ─────────────────────────────────────────────────
int main() {
    loadFromFile();
    int choice;

    printf("===========================================\n");
    printf("   EXPENSE & BUDGET TRACKER - DA1 Project  \n");
    printf("===========================================\n");

    do {
        showMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("[!] Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear buffer
            choice = 0;
            continue;
        }
        getchar(); // consume newline

        switch (choice) {
            case 1: addExpense();           break;
            case 2: viewMonthlyExpenses();  break;
            case 3: viewCategoryTotals();   break;
            case 4: searchExpenses();       break;
            case 5: setBudget();            break;
            case 6:
                saveToFile();
                printf("\n[✓] Data saved. Goodbye!\n");
                break;
            default:
                printf("[!] Invalid choice. Please enter 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}

// ─── FUNCTION 1: Show Menu ────────────────────────────────
void showMenu() {
    printf("\n-------------------------------------------\n");
    printf("  MENU\n");
    printf("-------------------------------------------\n");
    printf("  1. Add Expense\n");
    printf("  2. View Monthly Total\n");
    printf("  3. View Category-wise Totals\n");
    printf("  4. Search Expenses\n");
    printf("  5. Set Monthly Budget\n");
    printf("  6. Save & Exit\n");
    printf("-------------------------------------------\n");
}

// ─── FUNCTION 2: Add Expense ──────────────────────────────
void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("[!] Storage full. Cannot add more expenses.\n");
        return;
    }

    Expense e;

    // Date input with validation
    while (1) {
        printf("Enter date (YYYY-MM-DD): ");
        fgets(e.date, sizeof(e.date), stdin);
        e.date[strcspn(e.date, "\n")] = '\0'; // remove newline
        if (validateDate(e.date)) break;
        printf("[!] Invalid date format. Use YYYY-MM-DD (e.g. 2026-03-23)\n");
    }

    // Category
    printf("Enter category (Food/Travel/Medical/Shopping/Other): ");
    fgets(e.category, sizeof(e.category), stdin);
    e.category[strcspn(e.category, "\n")] = '\0';
    if (strlen(e.category) == 0) strcpy(e.category, "Other");

    // Amount with validation
    while (1) {
        printf("Enter amount (in Rs): ");
        if (scanf("%f", &e.amount) == 1 && e.amount > 0) {
            getchar();
            break;
        }
        printf("[!] Invalid amount. Enter a positive number.\n");
        while (getchar() != '\n');
    }

    // Note
    printf("Enter a short note (or press Enter to skip): ");
    fgets(e.note, sizeof(e.note), stdin);
    e.note[strcspn(e.note, "\n")] = '\0';
    if (strlen(e.note) == 0) strcpy(e.note, "-");

    expenses[expenseCount++] = e;
    saveToFile();
    printf("[✓] Expense added successfully!\n");
}

// ─── FUNCTION 3: View Monthly Total ──────────────────────
void viewMonthlyExpenses() {
    char month[8]; // YYYY-MM
    printf("Enter month to view (YYYY-MM): ");
    fgets(month, sizeof(month), stdin);
    month[strcspn(month, "\n")] = '\0';

    if (strlen(month) != 7) {
        printf("[!] Invalid format. Use YYYY-MM (e.g. 2026-03)\n");
        return;
    }

    float total = 0.0;
    int found = 0;

    printf("\n--- Expenses for %s ---\n", month);
    printf("%-12s %-15s %-10s %s\n", "Date", "Category", "Amount", "Note");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < expenseCount; i++) {
        if (strncmp(expenses[i].date, month, 7) == 0) {
            printf("%-12s %-15s %-10.2f %s\n",
                expenses[i].date,
                expenses[i].category,
                expenses[i].amount,
                expenses[i].note);
            total += expenses[i].amount;
            found++;
        }
    }

    if (!found) {
        printf("  No expenses found for this month.\n");
        return;
    }

    printf("------------------------------------------------------------\n");
    printf("  TOTAL for %s: Rs %.2f\n", month, total);

    // Budget warning
    if (monthlyBudget > 0) {
        printf("  Budget Limit : Rs %.2f\n", monthlyBudget);
        if (total > monthlyBudget) {
            printf("  [⚠ WARNING] You have EXCEEDED your budget by Rs %.2f!\n",
                total - monthlyBudget);
        } else {
            printf("  [✓] You are within budget. Rs %.2f remaining.\n",
                monthlyBudget - total);
        }
    }
}

// ─── FUNCTION 4: Category-wise Totals ────────────────────
void viewCategoryTotals() {
    char month[8];
    printf("Enter month (YYYY-MM): ");
    fgets(month, sizeof(month), stdin);
    month[strcspn(month, "\n")] = '\0';

    char categories[MAX_EXPENSES][30];
    float catTotals[MAX_EXPENSES];
    int catCount = 0;

    for (int i = 0; i < expenseCount; i++) {
        if (strncmp(expenses[i].date, month, 7) != 0) continue;

        int found = 0;
        for (int j = 0; j < catCount; j++) {
            if (strcmp(categories[j], expenses[i].category) == 0) {
                catTotals[j] += expenses[i].amount;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(categories[catCount], expenses[i].category);
            catTotals[catCount] = expenses[i].amount;
            catCount++;
        }
    }

    if (catCount == 0) {
        printf("  No expenses found for %s.\n", month);
        return;
    }

    printf("\n--- Category Totals for %s ---\n", month);
    printf("%-20s %s\n", "Category", "Total (Rs)");
    printf("--------------------------------\n");
    float grandTotal = 0;
    for (int i = 0; i < catCount; i++) {
        printf("%-20s %.2f\n", categories[i], catTotals[i]);
        grandTotal += catTotals[i];
    }
    printf("--------------------------------\n");
    printf("%-20s %.2f\n", "GRAND TOTAL", grandTotal);
}

// ─── FUNCTION 5: Search Expenses ─────────────────────────
void searchExpenses() {
    int searchType;
    printf("\nSearch by:\n");
    printf("  1. Date (exact: YYYY-MM-DD)\n");
    printf("  2. Category\n");
    printf("Enter choice: ");
    if (scanf("%d", &searchType) != 1 || (searchType != 1 && searchType != 2)) {
        printf("[!] Invalid choice.\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    char keyword[50];
    if (searchType == 1) {
        printf("Enter date (YYYY-MM-DD): ");
    } else {
        printf("Enter category keyword: ");
    }
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    printf("\n%-12s %-15s %-10s %s\n", "Date", "Category", "Amount", "Note");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < expenseCount; i++) {
        int match = 0;
        if (searchType == 1 && strcmp(expenses[i].date, keyword) == 0) match = 1;
        if (searchType == 2 && strstr(expenses[i].category, keyword) != NULL) match = 1;

        if (match) {
            printf("%-12s %-15s %-10.2f %s\n",
                expenses[i].date, expenses[i].category,
                expenses[i].amount, expenses[i].note);
            found++;
        }
    }

    if (!found) printf("  No matching expenses found.\n");
    else printf("------------------------------------------------------------\n");
    printf("  %d result(s) found.\n", found);
}

// ─── FUNCTION 6: Set Budget ───────────────────────────────
void setBudget() {
    printf("Enter your monthly budget limit (Rs): ");
    if (scanf("%f", &monthlyBudget) != 1 || monthlyBudget <= 0) {
        printf("[!] Invalid budget. Enter a positive number.\n");
        monthlyBudget = 0;
        while (getchar() != '\n');
        return;
    }
    getchar();
    printf("[✓] Monthly budget set to Rs %.2f\n", monthlyBudget);
}

// ─── FUNCTION 7: Save to File ─────────────────────────────
void saveToFile() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        printf("[!] Could not save data to file.\n");
        return;
    }
    fprintf(fp, "BUDGET:%.2f\n", monthlyBudget);
    for (int i = 0; i < expenseCount; i++) {
        fprintf(fp, "%s|%s|%.2f|%s\n",
            expenses[i].date,
            expenses[i].category,
            expenses[i].amount,
            expenses[i].note);
    }
    fclose(fp);
}

// ─── FUNCTION 8: Load from File ───────────────────────────
void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return; // file doesn't exist yet, that's fine

    char line[200];
    expenseCount = 0;

    if (fgets(line, sizeof(line), fp)) {
        sscanf(line, "BUDGET:%f", &monthlyBudget);
    }

    while (fgets(line, sizeof(line), fp) && expenseCount < MAX_EXPENSES) {
        line[strcspn(line, "\n")] = '\0';
        Expense e;
        char *token = strtok(line, "|");
        if (!token) continue; strcpy(e.date, token);
        token = strtok(NULL, "|");
        if (!token) continue; strcpy(e.category, token);
        token = strtok(NULL, "|");
        if (!token) continue; e.amount = atof(token);
        token = strtok(NULL, "|");
        if (!token) continue; strcpy(e.note, token);
        expenses[expenseCount++] = e;
    }
    fclose(fp);
}

// ─── FUNCTION 9: Validate Date Format ────────────────────
int validateDate(char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return 0;
    }
    int month = atoi(date + 5);
    int day   = atoi(date + 8);
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    return 1;
}
