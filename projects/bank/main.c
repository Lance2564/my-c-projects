#include "account.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    double dollars; // Dollars because people enter dollars, not cents
    int choice;     // User choice(1 - 6)
    int id;         // Account id

    Account dummy = {-1, "dummy", 0};                          // Dummy account
    Account sentinel = {-2, "sentinel", 0};                    // Sentinel account
    Account accounts[10] = {sentinel, dummy};                  // Initialising the accounts array
    Account *user_acc;                                         // The current user account being worked on
    int num_accounts = sizeof(accounts) / sizeof(accounts[0]); // Getting total accounts(10)

    while (1) {
        print_menu();                                          // Prints the menu
        choice = get_int("Please enter your choice(1 - 6): "); // Takes user choice

        // Gets how many live accounts there are(if sentinel is found, that many live accounts, else there are ten)
        int live_accounts = (get_sentinel(accounts, sentinel, num_accounts) != SENTINEL_NOT_FOUND_ERR) ? get_sentinel(accounts, sentinel, num_accounts) : 10;

        // Breaks if user chooses EXIT(6)
        if (choice == EXIT)
            break;

        // Switch-case for all other options
        switch (choice) {
            case DEPOSIT:
                // Gets dollars(to deposit)
                dollars = get_dollars("Please enter how much you want to deposit: ");
                long long int to_deposit = dollars_to_cents(dollars); // Convers dollars(double) to cents(int) for precision
                id = get_int("Please enter your id: ");               // id(to deposit where)

                // Finds the user account and validates it
                user_acc = find_account(accounts, live_accounts, id);
                // If account is valid(exists)
                if (validate_find_account(user_acc)) {
                    int deposit_status = deposit(user_acc, to_deposit);

                    // Checks if the transaction was succesful or not
                    switch (deposit_status) {
                        case TRANSACTION_OK:
                            printf("Successfully deposited!\n");
                            break;
                        case TRANSACTION_INVALID_AMOUNT:
                            printf("Please enter a valid amount!\n");
                            break;
                    }
                }
                // Informs the user if account doesn't exist
                else
                    printf("Account not found!\n");

                break;
            case WITHDRAW:
                // Gets the dollars(almost identical to deposit)
                dollars = get_dollars("Please enter how much you want to withdraw: ");
                long long int to_withdraw = dollars_to_cents(dollars);
                id = get_int("Please enter your id: ");

                // Finds the user account and validates it
                user_acc = find_account(accounts, live_accounts, id);
                if (validate_find_account(user_acc)) {
                    int withdraw_status = withdraw(user_acc, to_withdraw);

                    switch (withdraw_status) {
                        case TRANSACTION_OK:
                            printf("Successfully withdrawn!\n");
                            break;
                        case TRANSACTION_INSUFFICIENT_FUNDS:
                            printf("Not enough money!\n");
                            break;
                        case TRANSACTION_INVALID_AMOUNT:
                            printf("Please enter a valid amount!\n");
                            break;
                    }
                }
                else
                    printf("Account not found!\n");
                break;
            case TRANSFER:
                // Gets account ids, and amount
                int donor_acc_id = get_int("Please enter the id of the donor account: ");
                int receiver_acc_id = get_int("Please enter the id of thr receiver account: ");
                dollars = get_dollars("Please enter the amount: ");
                long long int to_transfer = dollars_to_cents(dollars);

                // Finds the account
                Account *donor_acc = find_account(accounts, live_accounts, donor_acc_id);
                Account *receiver_acc = find_account(accounts, live_accounts, receiver_acc_id);

                // If both accounts exist tries to transfer
                if (validate_find_account(donor_acc) && validate_find_account(receiver_acc)) {
                    int transfer_status = transfer(donor_acc, receiver_acc, to_transfer);
                    switch (transfer_status) {
                        case TRANSACTION_OK:
                            printf("Successfully transferred!\n");
                            break;
                        case TRANSACTION_INVALID_AMOUNT:
                            printf("Please enter a valid number!\n");
                            break;
                        case TRANSACTION_INSUFFICIENT_FUNDS:
                            printf("Donor doesn't have enough money!\n");
                            break;
                    }
                }
                // Informs user if neither accounts exist
                else if (!validate_find_account(donor_acc) && !validate_find_account(receiver_acc)) {
                    printf("Neither accounts exist!\n");
                }
                else if (!validate_find_account(donor_acc) && validate_find_account(receiver_acc))
                    printf("Donor account doesn't exist!\n");
                else
                    printf("Receiver account doesn't exist!\n");
                break;
            case ADD_ACC:
                // Gets the name and strips the newline
                char name[100];
                printf("Please enter your name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                int add_account_status = add_account(name, accounts, sentinel, num_accounts);

                switch (add_account_status) {
                    case ACCOUNT_ADD_OK:
                        printf("Successfully added!\n");
                        printf("Your id is: %d\n", get_sentinel(accounts, sentinel, num_accounts) - 1);
                        break;
                    case ACCOUNT_FULL_ERR:
                        printf("Sorry, there are no more account slots!\n");
                        break;
                }
                break;
            case PRINT:
                // Gets the id of the account and finds the account
                id = get_int("Please enter your id: ");
                user_acc = find_account(accounts, live_accounts, id);

                // If account exists, prints it else informs the user
                if (validate_find_account(user_acc))
                    print_account(user_acc);
                else
                    printf("Invalid id or account doesn't exist.\n");
                break;
        }
    }

    return 0;
}
