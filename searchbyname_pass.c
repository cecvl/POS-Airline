#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 100 // Define the maximum number of customers to be found

// Define the structure for holding customer data
struct Customer {
    int age;
    char passport[10];
    char fname[50];
    char lname[50];
    char phone[15];
    char destination[30];
    char time[10];
    int day;
    int month;
    int year;
};

// Function to initialize the customer structure with default values
void initializeCustomer(struct Customer* customer) {
    customer->age = 0;
    strcpy(customer->passport, "");
    strcpy(customer->fname, "");
    strcpy(customer->lname, "");
    strcpy(customer->phone, "");
    strcpy(customer->destination, "");
    strcpy(customer->time, "");
    customer->day = 0;
    customer->month = 0;
    customer->year = 0;
}

// Function to search for customers by first name and return an array of matching structs
int findCustomersByFirstName(const char* csvFileName, const char* firstName, struct Customer* matchingCustomers) {
    int numMatches = 0;

    FILE* file = fopen(csvFileName, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return numMatches;
    }

    char buffer[200]; // Assuming the CSV lines are not longer than 200 characters
    while (fgets(buffer, sizeof(buffer), file)) {
        struct Customer currentCustomer;
        initializeCustomer(&currentCustomer);

        sscanf(buffer, "%d,%9[^,],%49[^,],%49[^,],%14[^,],%29[^,],%9[^,],%d,%d,%d",
            &currentCustomer.age,
            currentCustomer.passport,
            currentCustomer.fname,
            currentCustomer.lname,
            currentCustomer.phone,
            currentCustomer.destination,
            currentCustomer.time,
            &currentCustomer.day,
            &currentCustomer.month,
            &currentCustomer.year
        );

        if (strcmp(currentCustomer.fname, firstName) == 0) {
            matchingCustomers[numMatches++] = currentCustomer;
        }
    }

    fclose(file);
    return numMatches;
}

// Function to search for customers by passport number and return an array of matching structs
int findCustomersByPassport(const char* csvFileName, const char* passportNumber, struct Customer* matchingCustomers) {
    int numMatches = 0;

    FILE* file = fopen(csvFileName, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return numMatches;
    }

    char buffer[200]; // Assuming the CSV lines are not longer than 200 characters
    while (fgets(buffer, sizeof(buffer), file)) {
        struct Customer currentCustomer;
        initializeCustomer(&currentCustomer);

        sscanf(buffer, "%d,%9[^,],%49[^,],%49[^,],%14[^,],%29[^,],%9[^,],%d,%d,%d",
            &currentCustomer.age,
            currentCustomer.passport,
            currentCustomer.fname,
            currentCustomer.lname,
            currentCustomer.phone,
            currentCustomer.destination,
            currentCustomer.time,
            &currentCustomer.day,
            &currentCustomer.month,
            &currentCustomer.year
        );

        if (strcmp(currentCustomer.passport, passportNumber) == 0) {
            matchingCustomers[numMatches++] = currentCustomer;
        }
    }

    fclose(file);
    return numMatches;
}

int main() {
    char csvFileName[] = "mainbooking.csv";
    char searchFirstName[50];
    char searchPassport[10];

    printf("Enter the first name to search: ");
    scanf("%s", searchFirstName);

    printf("Enter the passport number to search: ");
    scanf("%s", searchPassport);

    struct Customer matchingCustomers[MAX_CUSTOMERS];
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        initializeCustomer(&matchingCustomers[i]);
    }

    int numMatchesFirstName = findCustomersByFirstName(csvFileName, searchFirstName, matchingCustomers);
    int numMatchesPassport = findCustomersByPassport(csvFileName, searchPassport, matchingCustomers);

    int totalNumMatches = numMatchesFirstName + numMatchesPassport;

    if (totalNumMatches == 0) {
        printf("\nCustomer with first name '%s' or passport number '%s' not found.\n", searchFirstName, searchPassport);
    } else {
        printf("\n\t\t\t---------------Customer(s) Found-----------------\n");
        for (int i = 0; i < totalNumMatches; i++) {
            struct Customer foundCustomer = matchingCustomers[i];
            if (foundCustomer.age != 0 || strcmp(foundCustomer.fname, "") != 0 || strcmp(foundCustomer.lname, "") != 0) {
                printf("\t\t\tNAME: %s %s\tAGE: %d\n", foundCustomer.fname, foundCustomer.lname, foundCustomer.age);
                printf("\t\t\tPHONE NO: %s\tID/PASSPORT NO: %s\n", foundCustomer.phone, foundCustomer.passport);
                printf("\t\t\tDESTINATION: %s\tDEPARTURE DATE: %d-%d-%d\n\n",foundCustomer.destination, foundCustomer.day, foundCustomer.month, foundCustomer.year);
                printf("\t\t\t------------------------------------------------\n");
                // Print other fields as needed
            }
        }
    }

    return 0;
}
