#include <stdio.h>
#include <stdlib.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

/* Function Declarations */
void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

/* Main Function */
int main() {
    int choice;

    while (1) {
        printf("\n===== BANK ACCOUNT MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Amount\n");
        printf("3. Withdraw Amount\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                balanceEnquiry();
                break;
            case 5:
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }
    return 0;
}

/* Create Account */
void createAccount() {
    FILE *fp;
    struct Account acc;

    fp = fopen("account.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

/* Deposit Function */
void deposit() {
    FILE *fp;
    struct Account acc;
    int accNo, found = 0;
    float amount;

    fp = fopen("account.dat", "rb+");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);
            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("\nAmount Deposited Successfully!\n");
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\nAccount not found!\n");
}

/* Withdraw Function */
void withdraw() {
    FILE *fp;
    struct Account acc;
    int accNo, found = 0;
    float amount;

    fp = fopen("account.dat", "rb+");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter Withdrawal Amount: ");
            scanf("%f", &amount);

            if (amount > acc.balance) {
                printf("\nInsufficient Balance!\n");
            } else {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("\nWithdrawal Successful!\n");
            }
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\nAccount not found!\n");
}

/* Balance Enquiry */
void balanceEnquiry() {
    FILE *fp;
    struct Account acc;
    int accNo, found = 0;

    fp = fopen("account.dat", "rb");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("\nAccount Holder: %s", acc.name);
            printf("\nCurrent Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\nAccount not found!\n");
}

