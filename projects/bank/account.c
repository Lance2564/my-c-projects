#include "account.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_sentinel(Account array[], Account sentinel, int max_size) {
    int i = 0;
    while (i < max_size && array[i].id != sentinel.id)
        i++;

    return (i < max_size) ? i : SENTINEL_NOT_FOUND_ERR;
}

Account *find_account(Account array[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (array[i].id == id) {
            return &(array[i]);
        }
    }

    return NULL;
}

Transaction deposit(Account *account, long long int to_deposit) {
    if (is_positive(to_deposit)) {
        account->balance += to_deposit;
        return TRANSACTION_OK;
    }
    else {
        return TRANSACTION_INVALID_AMOUNT;
    }
}

Transaction withdraw(Account *account, long long int to_withdraw) {
    if (is_positive(to_withdraw) && account->balance >= to_withdraw) {
        account->balance -= to_withdraw;
        return TRANSACTION_OK;
    }
    else if (!(is_positive(to_withdraw))) {
        return TRANSACTION_INVALID_AMOUNT;
    }
    else {
        return TRANSACTION_INSUFFICIENT_FUNDS;
    }
}

Transaction transfer(Account *donor, Account *receiver, long long int amount) {
    if (is_positive(amount) && donor->balance >= amount) {
        donor->balance -= amount;
        receiver->balance += amount;
        return TRANSACTION_OK;
    }
    else if (!(is_positive(amount))) {
        return TRANSACTION_INVALID_AMOUNT;
    }
    else {
        return TRANSACTION_INSUFFICIENT_FUNDS;
    }
}

void print_account(const Account *account) { printf("Id: %d, Name: %s, Balance: %.2lf \n", account->id, account->name, cents_to_dollars(account->balance)); }

double cents_to_dollars(long long int cents) { return cents / 100.0; }

long long int dollars_to_cents(double dollars) { return (long long int)round(dollars * 100.0); }

AccountStuff add_account(const char *name, Account array[], Account sentinel_acc, int max_size) {
    // Gets the sentinel index(which is after the last active account)
    int sentinel_index = get_sentinel(array, sentinel_acc, max_size);

    // If sentinel index doesn't exist or sentinel index
    if (sentinel_index == SENTINEL_NOT_FOUND_ERR) {
        return ACCOUNT_FULL_ERR;
    }

    // Initialises the account
    Account account;
    account.id = (sentinel_index != 0) ? (array[sentinel_index - 1].id + 1) : 0; // Sets id one higher than the previous one
    account.balance = 0;                                                         // Sets balance to 0
    snprintf(account.name, sizeof(account.name), "%s", name);

    // taking max size as 10(last account would be index 0), makes sure sentinel_index is less than 9
    if (sentinel_index < (max_size - 1)) {
        (array)[sentinel_index] = account;          // Sets the account to sentinel index(let's take it as 0), now acc_index is 0
        (array)[sentinel_index + 1] = sentinel_acc; // Now increases the sentinel index by 1, replacing a dummy account
        return ACCOUNT_ADD_OK;
    }
    // If sentinel index is 9
    else if (sentinel_index == (max_size - 1)) {
        (array)[sentinel_index] = account; // Simply replaces the sentinel
        return ACCOUNT_ADD_OK;
    }

    return ACCOUNT_FULL_ERR;
}

bool is_positive(long long int num) { return num > 0; }

double get_dollars(const char *prompt) {
    char dollar_str[50];
    int verdict;

    while (1) {
        printf("%s", prompt);
        fgets(dollar_str, sizeof(dollar_str), stdin);

        dollar_str[strcspn(dollar_str, "\n")] = '\0';

        verdict = validate_double(dollar_str);

        switch (verdict) {
            case SAFE:
                return (strtod(dollar_str, NULL));
                break;
            case NO_DECIMAL:
                return (strtod(dollar_str, NULL));
                break;
            case INVALID_INPUT:
                continue;
        }
    }
}

FloatConversionStuff validate_double(const char *num) {
    int str_length = strlen(num);
    int decimal_index = strcspn(num, ".");

    if ((str_length == decimal_index) && (isdigit(num[0]))) {
        return NO_DECIMAL;
    }
    else if (isdigit(num[0])) {
        return SAFE;
    }
    else {
        return INVALID_INPUT;
    }
}

void print_menu(void) {
    printf("\nWelcome to Lance Bank!\n");
    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Transfer Money\n");
    printf("4. Add Account\n");
    printf("5. Print Account Details\n");
    printf("6. Exit\n");
    printf("\n");
}

int get_int(const char *prompt) {
    char input[50];

    while (1) {
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (isdigit(input[0])) {
            return atoi(input);
        }
        else {
            continue;
        }
    }
}

bool validate_find_account(Account *find_acc_result) { return (find_acc_result != NULL); }
