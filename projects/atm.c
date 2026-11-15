#include <stdio.h>

#define PRODUCT_COUNT (CANDY + 1)

typedef enum { PENNY = 1, NICKEL = 5, DIME = 10, QUARTER = 25 } Coin; // Mapping of coin to value
typedef enum { COKE = 1, CHIPS = 2, CANDY = 3 } Product;
typedef enum { COKE_PRICE = 125, CHIPS_PRICE = 75, CANDY_PRICE = 60 } Price; // Price of items
typedef enum { ON = 1, OFF = 0 } State;

// Function prototypes
void print_instructions(void);
int coin_value(char key);
int try_purchase(int balance, Product x);
int price_of(Product item);
void print_name(Product item);

int stock[PRODUCT_COUNT] = {0, [COKE] = 2, [CHIPS] = 2, [CANDY] = 2}; // Stock

int main(void) {
    char command = '\0'; // The user's choice (x, r, 1, 2)
    char coin_key;       // What coin(q, d, n. p)

    int coin_cents;
    State machine = ON; // So that the while loop runs, you can set this to off and have a do while loop but no point
    Product selected_item;

    int balance = 0;
    int quarters, dimes, nickels, pennies, remainder = 0;

    print_instructions();

    while (machine != OFF) {
        printf("What do you want to do?\n");
        printf("x, r, insert money(1), buy stuff(2)\n");
        scanf(" %c", &command);

        switch (command) {
            case '1':
                printf("What sort of money would you like to deposit(refer to above guide) ");
                scanf(" %c", &coin_key);

                coin_cents = coin_value(coin_key); // Gets the value of q, p, etc.
                balance += coin_cents;             // Adds that value to the balance

                printf("You now have %d¢!\n", balance);

                break;
            case '2':
                printf("What would you like to buy?\n");
                scanf("%u", &selected_item);

                balance = try_purchase(balance, selected_item); // Tries to purchase the items

                printf("You have %d¢ left\n", balance); // Tells how much balance is left
                break;
            case 'x':
                machine = OFF;
                break;
            case 'r':
                // Take an example of 41
                quarters = balance / QUARTER;  // 41 / 25 = 1 so 1 quarters
                remainder = balance % QUARTER; // 41 % 25 = 16

                dimes = remainder / DIME; // 16 / 10 = 1 so 1 dime
                remainder %= DIME;        // 16 % 10 = 6

                nickels = remainder / NICKEL; // 6 / 5 = 1 so nickel
                remainder %= NICKEL;          // 6 % 5 = 1

                pennies = remainder; // 1 so 1 penny, in total 1 quarter, 1 dime, 1 nickel, 1 penny

                printf("Refunded extra change! You now have %d quarters, %d dimes, %d nickels, %d pennies.\nIn total you have %d¢\n",
                        quarters, dimes, nickels, pennies, balance);
                balance = 0;
                break;
        }
    }
}

void print_instructions(void) {
    printf("Welcome to the vending machine!\n");
    printf("Basic functions: \n");
    printf("lowercase x for exit, r for refund\n");
    printf("q for quarter, d for dime, n for nickel, p for penny\n");
    printf("1 for Cola, 2 for Chips, 3 for Candy!\n");
    printf("Prices: \n");
    printf("Cola: 125 cents (5 quarters)\n");
    printf("Chips: 75 cents\n");
    printf("Candy: 60 cents\n");
}

int coin_value(char key) {
    int x = 0;
    switch (key) {
        case 'q':
            x = QUARTER;
            break;
        case 'd':
            x = DIME;
            break;
        case 'n':
            x = NICKEL;
            break;
        case 'p':
            x = PENNY;
            break;
    }

    return x;
}

int try_purchase(int balance, Product x) {
    if (stock[x] == 0) {
        printf("Sold out!\n");
    }
    else if (balance < price_of(x)) {
        printf("Not enough money!\n");
        printf("You need %d more", price_of(x) - balance);
    }
    else {
        balance -= price_of(x);
        stock[x]--;
        printf("Enjoy your ");
        print_name(x);
    }

    return balance;
}

int price_of(Product item) {
    switch (item) {
        case COKE:
            return COKE_PRICE;
        case CHIPS:
            return CHIPS_PRICE;
        case CANDY:
            return CANDY_PRICE;
    }

    return 0;
}

void print_name(Product item) {
    switch (item) {
        case COKE:
            printf("coke\n");
            break;
        case CHIPS:
            printf("chips\n");
            break;
        case CANDY:
            printf("candy\n");
            break;
    }
}
