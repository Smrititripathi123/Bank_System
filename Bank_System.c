#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[100];
    float balance;
};

void createAccount() {
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "ab");

    printf("Enter account number: ");
    scanf("%d", &acc.accountNumber);
    printf("Enter account holder name: ");
    getchar();
    fgets(acc.name, 100, stdin);
    acc.name[strcspn(acc.name, "\n")] = 0;
    printf("Enter initial balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
    printf("Account created successfully!\n");
}

void displayAccount() {
    struct Account acc;
    int accountNumber;
    FILE *fp = fopen("accounts.dat", "rb");

    if (fp == NULL) {
        printf("No account data found.\n");
        return;
    }

    printf("Enter account number to view: ");
    scanf("%d", &accountNumber);
    int found = 0;

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accountNumber) {
            printf("Account Number: %d\n", acc.accountNumber);
            printf("Account Holder: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Account not found.\n");
    }
}

void deposit() {
    struct Account acc;
    int accountNumber;
    float amount;
    FILE *fp = fopen("accounts.dat", "rb+");

    printf("Enter account number to deposit into: ");
    scanf("%d", &accountNumber);
    int found = 0;

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accountNumber) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("Deposit successful. New balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Account not found.\n");
    }
}

void withdraw() {
    struct Account acc;
    int accountNumber;
    float amount;
    FILE *fp = fopen("accounts.dat", "rb+");

    printf("Enter account number to withdraw from: ");
    scanf("%d", &accountNumber);
    int found = 0;

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accountNumber) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount <= acc.balance) {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("Withdrawal successful. New balance: %.2f\n", acc.balance);
            } else {
                printf("Insufficient balance.\n");
            }
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Account not found.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create Account\n");
        printf("2. Display Account\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: displayAccount(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: printf("Thank you for using the system.\n"); break;
            default: printf("Invalid choice.\n"); break;
        }
    } while (choice != 5);

    return 0;
}
