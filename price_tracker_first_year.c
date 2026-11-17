/*
   PRICE TRACKER - First Year C Version

   Concepts used:
   - printf() and scanf()
   - variables and data types
   - if-else and switch
   - loops
   - arrays and strings
   - structures
   - user-defined functions
   - basic text file handling

   Compile: gcc price_tracker_first_year.c -o price_tracker
   Run:     .\price_tracker.exe   (Windows PowerShell)
*/

#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 50
#define NAME_LENGTH 50
#define STORE_LENGTH 30
#define FILE_NAME "prices.txt"

struct Product {
    int id;
    char name[NAME_LENGTH];
    char store[STORE_LENGTH];
    float price;
    float targetPrice;
};

struct Product products[MAX_PRODUCTS];
int productCount = 0;

/* Function declarations */
void loadProducts(void);
void saveProducts(void);
void addProduct(void);
void viewProducts(void);
void searchProduct(void);
void updatePrice(void);
void checkTargetPrices(void);

int main(void) {
    int choice;

    loadProducts();

    do {
        printf("\n========== PRICE TRACKER ==========\n");
        printf("1. Add product\n");
        printf("2. View all products\n");
        printf("3. Search product by ID\n");
        printf("4. Update product price\n");
        printf("5. Check target prices\n");
        printf("0. Save and exit\n");
        printf("===================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n') {
                /* Clear invalid input */
            }
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updatePrice();
                break;
            case 5:
                checkTargetPrices();
                break;
            case 0:
                saveProducts();
                printf("Data saved. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}

/* Read product records from a text file */
void loadProducts(void) {
    FILE *fp;
    fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        return; /* File is created when the first product is saved */
    }

    productCount = 0;

    while (productCount < MAX_PRODUCTS &&
           fscanf(fp, "%d\n%49[^\n]\n%29[^\n]\n%f\n%f\n",
                  &products[productCount].id,
                  products[productCount].name,
                  products[productCount].store,
                  &products[productCount].price,
                  &products[productCount].targetPrice) == 5) {
        productCount++;
    }

    fclose(fp);
}

/* Save product records to a text file */
void saveProducts(void) {
    FILE *fp;
    int i;

    fp = fopen(FILE_NAME, "w");

    if (fp == NULL) {
        printf("Error: Could not save the file.\n");
        return;
    }

    for (i = 0; i < productCount; i++) {
        fprintf(fp, "%d\n%s\n%s\n%.2f\n%.2f\n",
                products[i].id,
                products[i].name,
                products[i].store,
                products[i].price,
                products[i].targetPrice);
    }

    fclose(fp);
}

/* Add a new product */
void addProduct(void) {
    int i;
    int newId = 1;

    if (productCount >= MAX_PRODUCTS) {
        printf("Product list is full.\n");
        return;
    }

    printf("Enter product ID: ");
    if (scanf("%d", &newId) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n') { }
        return;
    }

    for (i = 0; i < productCount; i++) {
        if (products[i].id == newId) {
            printf("This ID already exists.\n");
            return;
        }
    }

    products[productCount].id = newId;

    printf("Enter product name (use underscores instead of spaces): ");
    scanf("%49s", products[productCount].name);

    printf("Enter store name (use underscores instead of spaces): ");
    scanf("%29s", products[productCount].store);

    printf("Enter current price: ");
    if (scanf("%f", &products[productCount].price) != 1 ||
        products[productCount].price < 0) {
        printf("Invalid price.\n");
        while (getchar() != '\n') { }
        return;
    }

    printf("Enter target price: ");
    if (scanf("%f", &products[productCount].targetPrice) != 1 ||
        products[productCount].targetPrice < 0) {
        printf("Invalid target price.\n");
        while (getchar() != '\n') { }
        return;
    }

    productCount++;
    saveProducts();
    printf("Product added successfully.\n");
}

/* Display all products */
void viewProducts(void) {
    int i;

    if (productCount == 0) {
        printf("No products available.\n");
        return;
    }

    printf("\nID\tProduct\t\tStore\t\tPrice\tTarget\n");
    printf("----------------------------------------------------------\n");

    for (i = 0; i < productCount; i++) {
        printf("%d\t%-15s\t%-12s\t%.2f\t%.2f\n",
               products[i].id,
               products[i].name,
               products[i].store,
               products[i].price,
               products[i].targetPrice);
    }
}

/* Search for a product using its ID */
void searchProduct(void) {
    int id;
    int i;
    int found = 0;

    printf("Enter product ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n') { }
        return;
    }

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("\nProduct found:\n");
            printf("ID: %d\n", products[i].id);
            printf("Name: %s\n", products[i].name);
            printf("Store: %s\n", products[i].store);
            printf("Current price: %.2f\n", products[i].price);
            printf("Target price: %.2f\n", products[i].targetPrice);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Product not found.\n");
    }
}

/* Update the price of an existing product */
void updatePrice(void) {
    int id;
    int i;
    int found = 0;
    float newPrice;

    printf("Enter product ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n') { }
        return;
    }

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            printf("Enter new price: ");
            if (scanf("%f", &newPrice) != 1 || newPrice < 0) {
                printf("Invalid price.\n");
                while (getchar() != '\n') { }
                return;
            }

            products[i].price = newPrice;
            printf("Price updated successfully.\n");
            found = 1;
            saveProducts();
            break;
        }
    }

    if (found == 0) {
        printf("Product not found.\n");
    }
}

/* Show products whose current price is at or below the target */
void checkTargetPrices(void) {
    int i;
    int found = 0;

    printf("\nProducts at or below their target price:\n");

    for (i = 0; i < productCount; i++) {
        if (products[i].price <= products[i].targetPrice) {
            printf("%s: current price = %.2f, target price = %.2f\n",
                   products[i].name,
                   products[i].price,
                   products[i].targetPrice);
            found = 1;
        }
    }

    if (found == 0) {
        printf("No products have reached their target price.\n");
    }
}
