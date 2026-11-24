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

    // If sentinel index is less than the size of the array, returns the index, else sentinel not found
    return (i < max_size) ? i : SENTINEL_NOT_FOUND_ERR;
}

Account *find_account(Account array[], int count, int id) {
    // for loop to find an account with matching id
    for (int i = 0; i < count; i++) {
        if (array[i].id == id) {
            return &(array[i]);
        }
    }

    // if none found, returns NULL
    return NULL;
}

Transaction deposit(Account *account, long long int to_deposit) {
    // Checks if the number is positive, if it is, deposits the money and returns TRANSACTION_OK
    if (is_positive(to_deposit)) {
        account->balance += to_deposit;
        return TRANSACTION_OK;
    }
    else {
        return TRANSACTION_INVALID_AMOUNT; // else TRANSACTION_INVALID_AMOUNT since negative deposits shouldn't be allowed
    }
}

Transaction withdraw(Account *account, long long int to_withdraw) {
    // Checks if the number is positive, and there is enough balance, if yes, withdraws and returns TRANSACTION_OK
    if (is_positive(to_withdraw) && account->balance >= to_withdraw) {
        account->balance -= to_withdraw;
        return TRANSACTION_OK;
    }
    // if withdraw amount is negative, returns TRANSACTION_INVALID_AMOUNT
    else if (!(is_positive(to_withdraw))) {
        return TRANSACTION_INVALID_AMOUNT;
    }
    // else, the only possibility is not enough money.
    else {
        return TRANSACTION_INSUFFICIENT_FUNDS;
    }
}

Transaction transfer(Account *donor, Account *receiver, long long int amount) {
    // Checks if amount is positive and donor has enough money
    if (is_positive(amount) && donor->balance >= amount) {
        donor->balance -= amount;    // cuts balance from donor
        receiver->balance += amount; // adds balance to receiver
        return TRANSACTION_OK;
    }
    else if (!(is_positive(amount))) {
        return TRANSACTION_INVALID_AMOUNT; // negative amount is invalid
    }
    else {
        return TRANSACTION_INSUFFICIENT_FUNDS; // donor doesn't have enough money.
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

    /* returns account full error even on stuff like {user1, user2, sentinel}
    instead of replacing sentinel because sentinel isn't meant to be replaced,
    doing so would break a bunch of code. */

    return ACCOUNT_FULL_ERR;
}

bool is_positive(long long int num) { return num > 0; }

double get_dollars(const char *prompt) {
    char dollar_str[50];
    int verdict;

    while (1) {
        printf("%s", prompt);
        fgets(dollar_str, sizeof(dollar_str), stdin);

        dollar_str[strcspn(dollar_str, "\n")] = '\0'; // removes newline

        verdict = validate_double(dollar_str); // check if safe to convert or not

        switch (verdict) {
            case SAFE:
                return (strtod(dollar_str, NULL));
                break;
            case NO_DECIMAL:
                return (strtod(dollar_str, NULL));
                break;
            case INVALID_INPUT:
                // since not safe to convert, the loop is repeated again, till it becomes safe to convert and return
                continue;
        }
    }
}

FloatConversionStuff validate_double(const char *num) {
    // This function checks if a double is valid, and ready to be converted from string into double

    int str_length = strlen(num);
    int decimal_index = strcspn(num, ".");

    // Checks if there is a . in the string and that the first digit, is well, a digit.
    if ((str_length == decimal_index) && (isdigit(num[0]))) {
        return NO_DECIMAL;
    }
    // if it does, and it's first digit is a number, safe to convert (1.a becomes 1.0)
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
        printf("%s", prompt);               // Prints the prompt
        fgets(input, sizeof(input), stdin); // Gets user input and stores it in input

        input[strcspn(input, "\n")] = '\0'; // Removes newline

        if (isdigit(input[0])) { // If the first digit is a number
            return atoi(input);  // returns the integer after converting the string into an int
        }
        else {
            continue;
        }
    }
}

bool validate_find_account(Account *find_acc_result) {
    // Checks if find account returned NULL
    return (find_acc_result != NULL);
}

Account *increase_array_capacity(Account *array, int *max_size) {
    // Doubles the array capacity
    int new_capacity = *max_size * 2;
    Account *temp = realloc(array, new_capacity * sizeof(Account));

    // If for some reason memory allocation fails, program exits with error code 1
    if (temp == NULL) {
        printf("Something went terribly wrong\n");
        printf("Our IT team will probably not look into this\n");
        free(array);
        exit(1);
    }

    // Changes max size to new capacity here, so as not to have to do it in main
    *max_size = new_capacity;

    // Returns the array
    return temp;
}