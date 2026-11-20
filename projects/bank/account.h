#include <stdbool.h>

#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    int id;
    char name[100];
    long long int balance; // Long long to prevent integer overflow, and to prevent mismatch over OSes since long long is 64bit everywhere
} Account;

typedef enum { TRANSACTION_OK, TRANSACTION_NOT_FOUND, TRANSACTION_INSUFFICIENT_FUNDS, TRANSACTION_INVALID_AMOUNT } Transaction;
typedef enum { SENTINEL_NOT_FOUND_ERR = -1, ACCOUNT_FULL_ERR, ACCOUNT_ADD_OK } AccountStuff;
typedef enum { SAFE, NO_DECIMAL, INVALID_INPUT } FloatConversionStuff;
typedef enum { DEPOSIT = 1, WITHDRAW = 2, TRANSFER = 3, ADD_ACC = 4, PRINT = 5, EXIT = 6 } Choice;

int get_sentinel(Account array[], Account sentinel_acc, int max_size);
Account *find_account(Account array[], int count, int id);
Transaction deposit(Account *account, long long int to_deposit);
Transaction withdraw(Account *account, long long int to_withdraw);
Transaction transfer(Account *donor, Account *receiver, long long int amount);
void print_account(const Account *account);
double cents_to_dollars(long long int cents);
bool is_positive(long long int num);
AccountStuff add_account(const char *name, Account array[], Account sentinel_acc, int max_size);
double get_dollars(const char *prompt);
FloatConversionStuff validate_double(const char *num);
void print_menu(void);
int get_int(const char *prompt);
bool validate_find_account(Account *find_acc_result);
long long int dollars_to_cents(double dollars);

#endif