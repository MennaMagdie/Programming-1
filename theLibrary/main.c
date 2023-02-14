#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define STRING_LENGTH 250

// DATA
typedef struct
{
    int month;
    int year;
} Date;

typedef struct
{
    char isbn[14];
    char title[STRING_LENGTH];
    char author[STRING_LENGTH];
    int quantity;
    float price;
    Date date;
} Book;

// ------------
// GLOBAL VARIABLES
Book books[200];
int numberOfBooks = 0;
//-------------

// ---------------
// HELPER FUNCTIONS
// ----------------

// Validates ISBN format
int checkISBN(char isbn[])
{
    if (strlen(isbn) != 13)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < strlen(isbn); i++)
            if (!isdigit(isbn[i]))
                return 0;
    }
    return 1;
}

// This function returns -1 if the book is not present and the index if it is
int findBook(char isbn[])
{
    // Implement
    int i;
    for (i = 0; i < numberOfBooks; i++)
    {
        if (strcmp(books[i].isbn, isbn) == 0)
            return i;
    }
    return -1;
}

char* monthName(int n)
{
    char* month = malloc( 10 * sizeof(char));

    switch (n)
    {
    case 1:
        strcpy(month, "January");
        break;
    case 2:
        strcpy(month, "February");
        break;
    case 3:
        strcpy(month, "March");
        break;
    case 4:
        strcpy(month, "April");
        break;
    case 5:
        strcpy(month, "May");
        break;
    case 6:
        strcpy(month, "June");
        break;
    case 7:
        strcpy(month, "July");
        break;
    case 8:
        strcpy(month, "August");
        break;
    case 9:
        strcpy(month, "September");
        break;
    case 10:
        strcpy(month, "October");
        break;
    case 11:
        strcpy(month, "November");
        break;
    case 12:
        strcpy(month, "December");
        break;
    }
    return month;
}


// Prints book data
void printBook(int index)
{
    printf("ISBN: %s\n", books[index].isbn);
    printf("Title: %s\n", books[index].title);
    printf("Author: %s\n", books[index].author);
    printf("Quantity: %d\n", books[index].quantity);
    printf("Price: %.2f\n", books[index].price);
    printf("Date: %s %d\n", monthName(books[index].date.month), books[index].date.year);
    printf("\n");
}

// Converting string to lowercase
char *stringToLower(char str[])
{
    int i;
    char *p = malloc(250 * sizeof(char));
    for (i = 0; i <= strlen(str); i++)
    {
        p[i] = tolower(str[i]);
    }

    return p;
}

int checkIntInput(char input[])
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
        {
            return -1;
        }
    }
    return atoi(input);
}

float checkFloatInput(char input[])
{
    int counter = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '.')
        {
            if (counter == 1)
            {
                return -1;
            }
            counter++;
        }

        if (input[i] != '.' && !isdigit(input[i]))
        {
            return -1;
        }
    }
    return atof(input);
}

// Sorting array by Date
void sortByDate()
{
    Book TempBook;
    int pass, i;

    for (pass = 1; pass < numberOfBooks; pass++) // bubble sort algorithm
    {
        for (i = 0; i < (numberOfBooks)-pass; i++)
        {
            if (books[i].date.year < books[i + 1].date.year) // 2008 > 2007, then dont swap books
            {
                TempBook = books[i];
                books[i] = books[i + 1];
                books[i + 1] = TempBook;
            }
            else if ((books[i].date.year == books[i + 1].date.year) && (books[i].date.month < books[i + 1].date.month))
            {
                TempBook = books[i]; // if 7-2008 > 6-2008, then swap books
                books[i] = books[i + 1];
                books[i + 1] = TempBook;
            }
        }
    }
}

// Sorting array by title
void sortByTitle()
{
    Book TempBook;
    // Implement
    int pass, i;
    for (pass = 1; pass < numberOfBooks; pass++) // bubble sort algorithm
    {
        for (i = 0; i < numberOfBooks - pass; i++)
        {
            if (strcmp(books[i].title, books[i + 1].title) > 0) // if title[i]<title[i+1],then swap books
            {
                TempBook = books[i];
                books[i] = books[i + 1];
                books[i + 1] = TempBook;
            }
        }
    }
}

// Sorting array by price
void sortByPrices()
{
    Book TempBook;
    // Implement
    int pass, i;
    for (pass = 1; pass < numberOfBooks; pass++) // bubble sort algorithm
    {
        for (i = 0; i < numberOfBooks - pass; i++)
        {
            if (books[i].price > books[i + 1].price) // if price[i]<price[i+1],then swap books
            {
                TempBook = books[i];
                books[i] = books[i + 1];
                books[i + 1] = TempBook;
            }
        }
    }
}

// Function that waits for
void waitForESC()
{
    printf("\n\nPress ESC to go back to menu: \n");
    while (1)
    {
        char ch = getch();
        if (ch == 27)
            break;
    }
}


// ---------------
// MAIN FUNCTIONS
// ----------------

int start()
{
    char input[20];
    int option;
    system("cls");

    do
    {
        // Prompts for two options
        printf("1 - LOGIN \n2 - QUIT \nChoose option: ");
        scanf("%s", &input);

        option = checkIntInput(input);
        system("cls");
        // Validation
        if (option == -1 || (option != 1 && option != 2))
        {
            printf("Invalid option\n\n");
        }
    }
    while (option == -1 || (option != 1 && option != 2));   // Loops over until the user enters either 1 or 2

    return option;
}

void login()
{
    system("cls");
    // Implement
    char username[STRING_LENGTH], password[STRING_LENGTH];
    char line[STRING_LENGTH];
    int validUsername = 0, validPass = 0, lineIndex = 0;

    // Opening file
    FILE *file = fopen("credentials.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    // Infinite loop till a username that exists is entered
    while (1)
    {
        printf("LOGIN\n");
        printf("Enter username: ");
        scanf("%s", &username);

        // Loops over the whole file comparing each username in file with input
        while (fgets(line, STRING_LENGTH, file) != NULL)
        {
            // Gets line and removes the trailing \n for comparison
            line[strcspn(line, "\n")] = 0;
            lineIndex++;

            // A valid username is entered when strcmp returns 0 and the lineIndex indicates a username line (is odd)
            if (!strcmp(username, line) && (lineIndex % 2 != 0))
            {
                validUsername = 1;
                break;
            }
        }

        if (validUsername)
        {
            break;
        }
        else
        {
            system("cls");
            printf("Username doesn't exist\n\n");
        }
        rewind(file);
    }

    // Get line right after username as it'll be their password
    fgets(line, STRING_LENGTH, file);
    line[strcspn(line, "\n")] = 0;

    // Infinite loop till the right password is entered
    while (1)
    {
        printf("Enter password: ");
        scanf("%s", &password);

        if (!strcmp(password, line))
        {
            break;
        }
        else
        {
            printf("Incorrect password\n");
        }
    }

    fclose(file);
}

int quit()
{
    return 0;
}

int load()
{
    system("cls");
    // Implement
    char c;
    int bookCounter = 0;
    char line[STRING_LENGTH];

    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    while (fgets(line, STRING_LENGTH, file) != NULL)
    {
        Book book;

        // Grabbing ISBN
        char *bookToken = strtok(line, ",");
        strcpy(book.isbn, bookToken);

        // Grabbing Title
        bookToken = strtok(NULL, ",");
        strcpy(book.title, bookToken);

        // Grabbing Author
        bookToken = strtok(NULL, ",");
        strcpy(book.author, bookToken);

        // Grabbing Quantity
        bookToken = strtok(NULL, ",");
        int quantity = atoi(bookToken);
        book.quantity = quantity;

        // Grabbing Price
        bookToken = strtok(NULL, ",");
        double price = atof(bookToken);
        book.price = price;

        // Grabbing Date and creating date object to store date
        Date date;
        bookToken = strtok(NULL, ",");

        // Taking last token and splitting it further on "-" to get month and year
        char *dateToken = strtok(bookToken, "-");
        int month = atoi(dateToken);
        date.month = month;

        dateToken = strtok(NULL, "-");
        int year = atoi(dateToken);
        date.year = year;
        book.date = date;
        books[bookCounter] = book;
        bookCounter++;
    }
    fclose(file);
    numberOfBooks = bookCounter;

    return 0;
}

void add()
{
    Book newBook;
    char input[20];
    char title[250], author[250];
    int i, quantity, month, year;
    float price;

    system("cls");
    // Implement

    printf("\t\tADDING A NEW BOOK\n\n");

    // Taking data from user
    do
    {
        printf("ISBN(13 digits): ");
        scanf("%s",newBook.isbn);

        if (!checkISBN(newBook.isbn))
        {
            system("cls");
            printf("Invalid ISBN\n");
        }

    }
    while (!checkISBN(newBook.isbn));

    if(findBook(newBook.isbn) != -1)
    {
        (books[findBook(newBook.isbn)].quantity)++;  // Quantity incremented
        printf("Book already exists. Quantity incremented.");
        waitForESC();
        return;
    }

    getchar();

    printf("Title: ");
    gets(newBook.title);

    printf("Author: ");
    gets(newBook.author);

    do
    {
        printf("Quantity: ");
        scanf("%s", &input);

        newBook.quantity = checkIntInput(input);
        if (newBook.quantity == -1 || newBook.quantity < 1)
            printf("Invalid quantity\n");

    }
    while (newBook.quantity == -1 || newBook.quantity < 1);


    do
    {
        printf("Price: ");
        // scanf("%f", &newBook.price);
        scanf("%s", &input);
        newBook.price = checkFloatInput(input);


        if ((newBook.price) < 0 || newBook.price == -1)
            printf("Invalid price\n");
    }
    while ((newBook.price) < 0 || newBook.price == -1);

    do
    {
        printf("Month of Publication: ");
        scanf("%s", &input);

        month = checkIntInput(input);
        if (month == -1 || month > 12 || month < 1)
            printf("Invalid month.\n");

    }
    while (month == -1 || month > 12 || month < 1);

    newBook.date.month = month;

    do
    {
        printf("Year of Publication: ");
        scanf("%s", &input);

        year = checkIntInput(input);
        if (year == -1 || year > 2022 || year < 1)
            printf("Invalid year\n");

    }
    while (year == -1 || year > 2022 || year < 1);

    newBook.date.year = year;

    books[numberOfBooks] = newBook;
    numberOfBooks++;

    printf("Book successfully added!");


    waitForESC();
}


void delete()
{
    system("cls");
    // Implement
    printf("\t\t DELETING A BOOK\n\n");

    char isbn[14];
    int j;

    // Loops until a book is found
    do
    {
        printf("Enter the ISBN of the book you wish to delete (13 digits): ");
        scanf("%s", isbn);
        if (!checkISBN(isbn))
        {
            system("cls");
            printf("Invalid ISBN\n");
        }
        else if (findBook(isbn) == -1)
        {
            system("cls");
            printf("Book isn't available\n");
        }

    }
    while (!checkISBN(isbn) || findBook(isbn) == -1);

    // Deletes the book by shifting all the books after it one index closer
    int index = findBook(isbn);
    for (j = index; j < numberOfBooks; j++)
    {
        books[j] = books[j + 1];
    }
    numberOfBooks--;

    printf("Book successfully deleted!");

    waitForESC();
}


void modify()
{
    system("cls");
    char input[20];
    char isbn[14], title[250], author[250];
    int i, quantity, month, year;
    float price;

    printf("\t\t MODIFYING A BOOK\n\n");

    do
    {
        printf("Enter the ISBN of the book you wish to modify (13 digits): ");
        scanf("%s", isbn);
        if (!checkISBN(isbn))
        {
            system("cls");
            printf("Invalid ISBN\n");
        }
        else if (findBook(isbn) == -1)
        {
            system("cls");
            printf("Book isn't available\n");
        }

    }
    while (!checkISBN(isbn) || findBook(isbn) == -1);

    i = findBook(isbn);

    getchar();

    printf("Title: ");
    gets(title);
    strcpy(books[i].title, title);

    printf("Author: ");
    gets(author);
    strcpy(books[i].author, author);

    do
    {
        printf("Quantity: ");
        scanf("%s", &input);
        quantity = checkIntInput(input);

        if (quantity == -1 || quantity < 1)
            printf("Invalid quantity.\n");

    }
    while (quantity == -1 || quantity < 1);

    books[i].quantity = quantity;

    do
    {
        printf("Price: ");
        scanf("%s", &input);
        price = checkFloatInput(input);

        if ((price) < 0 || price == -1)
            printf("Invalid price\n");
    }
    while ((price) < 0 || price == -1);
    books[i].price = price;

    do
    {
        printf("Month of Publication: ");
        scanf("%s", &input);

        month = checkIntInput(input);
        if (month == -1 || month < 1 || month > 12)
            printf("Invalid Month.\n");

    }
    while (month == -1 || month < 1 || month > 12);

    do
    {
        printf("Year of Publication: ");
        scanf("%s", &input);

        year = checkIntInput(input);
        if (year == -1 || year > 2022 || year < 0)
            printf("Invalid Year.\n");

    }
    while (year == -1 || year > 2022 || year < 0);

    books[i].date.month = month;
    books[i].date.year = year;

    printf("\nBook successfully modified!");

    waitForESC();
}

void query()
{
    system("cls");
    // Implement
    char isbn[20];
    int index;

    printf("\t\t SEARCH BY ISBN\n\n");


    // Loop to obtain a valid ISBN and an ISBN that exists
    do
    {
        printf("Enter ISBN (13 digits): ");
        scanf("%s", isbn);
        if (!checkISBN(isbn))
        {
            system("cls");
            printf("Invalid ISBN\n");
        }

    }
    while (!checkISBN(isbn));

    // Prints book thats found
    index = findBook(isbn);
    if(index != -1)
    {
        printf("\n");
        printBook(index);
    }
    else
    {
        printf("Book isn't available");
    }

    waitForESC();
}

void advSearch()
{
    system("cls");
    char userSearch[STRING_LENGTH];
    printf("\t\t SEARCH BY KEYWORD\n\n");

    printf("Keyword to search for: ");

    while (getchar() != '\n');

    fgets(userSearch, 250, stdin);
    userSearch[strlen(userSearch) - 1] = '\0'; // removing \n character from end of string

    int flag = 0;
    char *p;
    char *titlePointer;
    char *userSearchPointer;

    for (int i = 0; i < numberOfBooks; i++)
    {
        titlePointer = stringToLower(books[i].title);  // covert title to lower case
        userSearchPointer = stringToLower(userSearch); // convert search to lowercase

        p = strstr
        (titlePointer, userSearchPointer);
        if (p) // if substring exists
        {
            printBook(i); // print book information
            flag = 1;
        }

        free(titlePointer);
        free(userSearchPointer);
    }

    if (!flag)
        printf("No books found!");

    waitForESC();
}


void print()
{
    system("cls");
    char input[20];
    int sortType;

    // Loops over until a valid type is entered
    do
    {
        printf("How would you like the books sorted?\n");
        printf("1- By Price\n");
        printf("2- By Date\n");
        printf("3- By Title\n");
        printf("Choose Option: ");
        scanf("%s", &input);

        sortType = checkIntInput(input);

        if (sortType == -1 || sortType < 1 || sortType > 3)
        {
            system("cls");
            printf("Invalid Option\n");
        }

    }
    while (sortType == -1 || sortType < 1 || sortType > 3);

    system("cls");

    // Depending on type chosen, the appropriate function will run
    switch (sortType)
    {
    case 1:
        sortByPrices();
        printf("Sorted by Price: \n\n");
        break;

    case 2:
        sortByDate();
        printf("Sorted by Date: \n\n");
        break;

    case 3:
        sortByTitle();
        printf("Sorted by Title: \n\n");
        break;
    }

    // Prints the now sorted array
    for (int i = 0; i < numberOfBooks; i++)
    {
        printBook(i);
    }

    waitForESC();
}

void save()
{
    system("cls");
    // Implement
    FILE *file = fopen("books.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    int size = numberOfBooks, i;
    for (i = 0; i < size; i++)
    {
        fprintf(file, "%s,%s,%s,%d,%.2f,%d-%d", books[i].isbn, books[i].title, books[i].author, books[i].quantity, books[i].price, books[i].date.month, books[i].date.year);
        fprintf(file, "\n");
    }

    fclose(file);

    printf("Books saved!");

    waitForESC();
}

int main()
{
    // Start menu, returns option chosen
    char input[20];
    int option = start();

    if (option == 1)
    {
        // After choosing Login option
        // Running login function and once successful, will load the books
        login();
        load();

        int menuOption;
        // Infinite loop to print menu that breaks only if quit is confirmed
        while (1)
        {
            do
            {
                system("cls");

                printf("1- ADD \n");
                printf("2- DELETE \n");
                printf("3- MODIFY \n");
                printf("4- SEARCH \n");
                printf("5- ADVANCED SEARCH \n");
                printf("6- PRINT \n");
                printf("7- SAVE \n");
                printf("8- QUIT - (All changes will be discarded if chosen before SAVE) \n");

                printf("Choose action: ");
                scanf("%s", &input);

                menuOption = checkIntInput(input);

            }
            while (menuOption == -1 || menuOption < 1 || menuOption > 8);

            switch (menuOption)
            {
            case 1:
                add();
                break;
            case 2:
                delete ();
                break;
            case 3:
                modify();
                break;
            case 4:
                query();
                break;
            case 5:
                advSearch();
                break;
            case 6:
                print();
                break;
            case 7:
                save();
                break;
            case 8:
                // Case 8 is QUIT, program ends
                return 0;
            }
        }
    }
    else
    {
        // After choosing quit, the program ends
        return 0;
    }

    return 0;
}
