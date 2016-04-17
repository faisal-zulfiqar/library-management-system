// header files
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

// function prototypes
void welcome();
void add_a_book();
void delete_a_book();
void search_a_book();
void search_by_author();
void search_by_name();
void search_by_isbn();
void modify_a_book();
void display_all_books();
void issue_a_book();

// structure
struct book
{
    char serialno[6];
    char isbn[14];
    char name[31];
    char edition[3];
    char author[31];
    char reserved[4];
};

// structure variable
struct book b;

// global file pointer
FILE *fp;

int main(void)
{
    system("cls");

    welcome();

    char choice = 'x';

    // sentinel value controlled loop to stay in menu until exit is function is used
    while (choice != 'g' || choice != 'G')
    {
        system("cls");

        printf("\n\n\t\t\t\t\t\tLibrary Management System.\n\n\n");

        printf("\n\ta): Add a Book.");
        printf("\n\tb): Delete a Book.");
        printf("\n\tc): Search a Book.");
        printf("\n\td): Modify a Book Record.");
        printf("\n\te): Display all Books.");
        printf("\n\tf): Issue a Book.");
        printf("\n\tg): Exit.");

        printf("\n\n\tEnter your choice (a, b, c, d, e, f, g) = ");
        fflush(stdin);
        choice = getche();

        /*Switch statement is used as there are 7 comparisons to be made.
        Switch here is faster than if/else statement in computation speed*/
        switch (choice)
        {
        case 'a':
        case 'A':
            {
                add_a_book();
                break;
            }
        case 'b':
        case 'B':
            {
                delete_a_book();
                break;
            }
        case 'c':
        case 'C':
            {
                search_a_book();
                break;
            }
        case 'd':
        case 'D':
            {
                modify_a_book();
                break;
            }
        case 'e':
        case 'E':
            {
                display_all_books();
                break;
            }
        case 'f':
        case 'F':
            {
                issue_a_book();
                break;
            }
        case 'g':
        case 'G':
            {
                printf("\n\n");
                exit(0);
            }
        default:
            {
                system("cls");
                printf("\n\t\t\t\t\t\t     Invalid Choice.");
                printf("\n\n\t\t\t\t\t   Please enter a valid choice again.");
                Sleep(1300);
            }
        }
    }

    return 0;
}

/*This function shows animated output.
It prints one character at a time using
a timer which pauses the flow for 0.3 seconds*/
void welcome()
{
    char array[] = {"Library Management System"};

    printf("\n\n\t\t\t\t\t\t");

    int a;
    for (a = 0; a < 25; a++)
    {
        Sleep(30);
        printf("%c", array[a]);
    }
}

void add_a_book()
{
    start:

    system("cls");

    printf("\n\t\t\t\t\t\t   Book Addition Menu:");
    printf("\n\n\tThis will add the contents to Books_DB database.\n");

    fp = fopen("Books_DB.txt", "a");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    printf("\n\n\tEnter Book name = ");

    // gets() function is used to get spaced inputs
    gets(b.name);

    printf("\n\tEnter Author's name = ");
    gets(b.author);

    printf("\n\tEnter Book Serial number = ");
    gets(b.serialno);

    printf("\n\tEnter ISBN = ");
    gets(b.isbn);

    printf("\n\tEnter Book Edition = ");
    gets(b.edition);

    strcpy(b.reserved, "No");

    // writing all structure to the file at once
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    fflush(stdin);

    char choice;
    printf("\n\n\tEnter another record : ");
    printf("\n\n\tPress 'y' to enter another record.\n\tPress any other key to return to main menu.\n\n");
    printf("\tChoice = ");
    choice = getche();

    if (choice == 'y' || choice == 'Y')
    {
        goto start;
    }
}

void delete_a_book()
{
    system("cls");

    char input[50], choice;

    int flag = 0, i = 0, size = 0;

    struct book delete_book[35];

    printf("\n\t\t\t\t\t\t    Book Deletion Menu:");
    printf("\n\n\tThis will permanently delete the contents of Books_DB database.\n");

    printf("\n\n\tEnter Book Name : ");
    gets(input);

    fp = fopen("Books_DB.txt", "r");

    // reading all records in array of structures
    while(1)
    {
        fread(&delete_book[i], sizeof(delete_book[i]), 1, fp);

        if (feof(fp))
        {
            break;
        }

        if((strcmp(delete_book[i].name, input) == 0))
        {
            flag++;
        }

        i++;
        size++;
    }

    fclose(fp);

    // in-case the book is not found
    if (flag == 0)
    {
        system("cls");

        printf("\n\t\t\t\t\t\t    Book Deletion Menu:");
        printf("\n\n\tThis will permanently delete the contents of Books_DB database.\n");

        printf("\n\n\tEnter Book Name : %s", input);

        printf("\n\n\t'%s' was not found in Book_DB database.\n\n\t", input);
        system("pause");
        return;
    }

    fp = fopen("Books_DB.txt", "w");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    flag = 0;

    // looping till the total no. of books is reached
    for (i = 0; i < size; i++)
    {
        if((strcmp(delete_book[i].name, input) == 0))
        {
            Sleep(30);
            printf("\n\tSerial No. = %s", delete_book[i].serialno);
            Sleep(30);
            printf("\n\tName       = %s", delete_book[i].name);
            Sleep(30);
            printf("\n\tAuthor     = %s", delete_book[i].author);
            Sleep(30);
            printf("\n\tISBN       = %s", delete_book[i].isbn);
            Sleep(30);
            printf("\n\tEdition    = %s", delete_book[i].edition);
            Sleep(30);
            printf("\n\tReserved   = %s\n\n\t", delete_book[i].reserved);
            Sleep(30);

            printf("\n\tDelete this record : ");
            printf("\n\n\tPress 'y' to delete this record.\n\tPress any other key to return to main menu.\n\n");
            printf("\tChoice = ");
            fflush(stdin);
            choice = getche();

            // the specified book is skipped on confirmation
            if(choice == 'y' || choice == 'Y')
            {
                flag++;
                continue;
            }

            // else written in the file
            else
            {
                fwrite(&delete_book[i], sizeof(delete_book[i]), 1, fp);
            }
        }

        else
        {
            fwrite(&delete_book[i], sizeof(delete_book[i]), 1, fp);
        }
    }

    if (flag == 0)
    {
        fclose(fp);
        return;
    }

    system("cls");

    printf("\n\t\t\t\t\t\t    Book Deletion Menu:");
    printf("\n\n\tThis will permanently delete the contents of Books_DB database.\n");

    printf("\n\tThe Record has been deleted.\n\n\t");
    system("pause");

    fclose(fp);
}

void search_a_book()
{
    start:
        ;

    char choice;

    system("cls");

    printf("\n\t\t\t\t\t\t   Book Searching Menu :\n\n\n");

    printf("\n\ta): Search by Author.");
    printf("\n\tb): Search by Title.");
    printf("\n\tc): Search by ISBN.");
    printf("\n\td): Goto Main Menu.");

    printf("\n\n\tEnter your choice (a, b, c, d) = ");
    fflush(stdin);
    choice = getche();

    switch (choice)
    {
    case 'a':
    case 'A':
        {
            search_by_author();
            system("pause");
            break;
        }
    case 'b':
    case 'B':
        {
            search_by_name();
            system("pause");
            break;
        }
    case 'c':
    case 'C':
        {
            search_by_isbn();
            system("pause");
            break;
        }
    case 'd':
    case 'D':
        {
            return;
        }
    default:
        {
            system("cls");
            printf("\n\t\t\t\t\t\t     Invalid Choice.");
            printf("\n\n\t\t\t\t\t   Please enter a valid choice again.");
            Sleep(1300);
        }
    }
    goto start;
}

void search_by_author()
{
    system("cls");

    printf("\n\t\t\t\t\t\t    Book Searching Menu :");
    printf("\n\n\t\t\t\t\t        Search Book by Author Name :");

    char input[40];
    int i = 0;

    /*Flags are used to detect whether the specific book is present or not.
    The initial value is '0'. And if a book is detected then then at each iteration
    the value of flag is incremented. So a value greater then '0' shows that book is there.*/
    int flag = 0;

    printf("\n\n\tAuthor Name = ");
    gets(input);

    fp = fopen("Books_DB.txt", "r");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    while(1)
    {
        fread(&b, sizeof(b), 1, fp);

        if(feof(fp))
        {
            break;
        }

        if (strcmp(input, b.author) == 0)
        {
            Sleep(30);
            printf("\n\t%c Book#%d : \n", 254, ++i);
            Sleep(30);
            printf("\n\tSerial No. = %s", b.serialno);
            Sleep(30);
            printf("\n\tName       = %s", b.name);
            Sleep(30);
            printf("\n\tAuthor     = %s", b.author);
            Sleep(30);
            printf("\n\tISBN       = %s", b.isbn);
            Sleep(30);
            printf("\n\tEdition    = %s", b.edition);
            Sleep(30);
            printf("\n\tReserved   = %s\n\n\t", b.reserved);
            Sleep(30);

            // increments value of flag
            ++flag;
        }
    }

    if (flag == 0)
    {
        printf("\n\tBooks written by Author '%s' are not present in Book_DB database.\n\n\t", input);
        return;
    }
}

void search_by_name()
{
    system("cls");

    printf("\n\t\t\t\t\t\t    Book Searching Menu :");
    printf("\n\n\t\t\t\t\t         Search Book by its Title :");

    char input[40];
    int i = 0, flag = 0; // just like search_by_author

    printf("\n\n\tBook Name = ");
    gets(input);

    fp = fopen("Books_DB.txt", "r");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    while(1)
    {
        fread(&b, sizeof(b), 1, fp);

        if(feof(fp))
        {
            break;
        }

        if (strcmp(input, b.name) == 0)
        {
            Sleep(30);
            printf("\n\t%c Book#%d : \n", 254, ++i);
            Sleep(30);
            printf("\n\tSerial No. = %s", b.serialno);
            Sleep(30);
            printf("\n\tName       = %s", b.name);
            Sleep(30);
            printf("\n\tAuthor     = %s", b.author);
            Sleep(30);
            printf("\n\tISBN       = %s", b.isbn);
            Sleep(30);
            printf("\n\tEdition    = %s", b.edition);
            Sleep(30);
            printf("\n\tReserved   = %s\n\n\t", b.reserved);
            Sleep(30);

            ++flag;
        }
    }

    if (flag == 0)
    {
        printf("\n\tBook '%s' was not found in Book_DB database.\n\n\t", input);
        return;
    }
}

void search_by_isbn()
{
    system("cls");

    printf("\n\t\t\t\t\t\t    Book Searching Menu :");
    printf("\n\n\t\t\t\t\t          Search Book by its ISBN :");

    char input[40];
    int i = 0, flag = 0; // just like search_by_author

    printf("\n\n\tISBN of the Book = ");
    gets(input);

    fp = fopen("Books_DB.txt", "r");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    while(1)
    {
        fread(&b, sizeof(b), 1, fp);

        if(feof(fp))
        {
            break;
        }

        if (strcmp(input, b.isbn) == 0)
        {
            Sleep(30);
            printf("\n\t%c Book#%d : \n", 254, ++i);
            Sleep(30);
            printf("\n\tSerial No. = %s", b.serialno);
            Sleep(30);
            printf("\n\tName       = %s", b.name);
            Sleep(30);
            printf("\n\tAuthor     = %s", b.author);
            Sleep(30);
            printf("\n\tISBN       = %s", b.isbn);
            Sleep(30);
            printf("\n\tEdition    = %s", b.edition);
            Sleep(30);
            printf("\n\tReserved   = %s\n\n\t", b.reserved);
            Sleep(30);

            ++flag;
        }
    }

    if (flag == 0)
    {
        printf("\n\tThere is no book with '%s' ISBN.\n\n\t", input);
        return;
    }
}

void modify_a_book()
{
    int i = 0, size = 0, flag = 0;

    char input[30], choice;

    struct book update[35];

    system("cls");

    printf("\n\t\t\t\t\t\t    Modify a Record :");
    printf("\n\n\tThis will modify the contents of the record\n\tin Book_DB Database.\n\n");

    printf("\n\tName of the Book = ");
    gets(input);

    fp = fopen("Books_DB.txt", "r");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    // records are read in array of structures
    while(1)
    {
        fread(&update[i], sizeof(update[i]), 1, fp);

        if (feof(fp))
        {
            break;
        }

        if((strcmp(update[i].name, input) == 0))
        {
            flag++;
        }

        i++;
        size++;
    }

    if(flag == 0)
    {
        printf("\n\tBook '%s' is not present in Book_DB database.\n\n\t", input);
        system("pause");
        return;
    }

    fclose(fp);

    fp = fopen("Books_DB.txt", "w");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    flag = 0;

    for(i = 0; i < size; i++)
    {
        // specified record is selected
        if((strcmp(update[i].name, input) == 0))
        {
            Sleep(30);
            printf("\n\t%c Book#%d : \n", 254, ++i);
            Sleep(30);
            printf("\n\tSerial No. = %s", b.serialno);
            Sleep(30);
            printf("\n\tName       = %s", b.name);
            Sleep(30);
            printf("\n\tAuthor     = %s", b.author);
            Sleep(30);
            printf("\n\tISBN       = %s", b.isbn);
            Sleep(30);
            printf("\n\tEdition    = %s", b.edition);
            Sleep(30);
            printf("\n\tReserved   = %s\n\n", b.reserved);
            Sleep(30);

            printf("\n\tModify this record : ");
            printf("\n\n\tPress 'y' to modify this record.\n\tPress any other key to return to main menu.\n\n");
            printf("\tChoice = ");
            choice = getche();

            // new data is received on approval
            if(choice == 'y' || choice == 'Y')
            {
                system("cls");

                printf("\n\t\t\t\t\t\t\t\t\t    Modify a Record :");
                printf("\n\n\tThis will alter the contents of Books_DB database.\n");
                printf("\n\n\tBook Name : %s\n", input);

                printf("\n\tEnter the Updated Info:\n");

                printf("\n\tSerial No. = ");
                gets(update[i].serialno);

                printf("\n\tName = ");
                gets(update[i].name);

                printf("\n\tAuthor = ");
                gets(update[i].author);

                printf("\n\tISBN = ");
                gets(update[i].isbn);

                printf("\n\tEdition = ");
                gets(update[i].edition);

                printf("\n\tReserved ('Yes'/'No') = ");
                gets(update[i].reserved);
            }
        }

        fwrite(&update[i], sizeof(update[i]), 1, fp);
    }

    fclose(fp);
}

void display_all_books()
{
    system("cls");

    int i = 0;

    fp = fopen("Books_DB.txt", "r");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    printf("\n\t\t\t\t\t\t    Display all Books : \n\n");

    while (1)
    {
        fread(&b, sizeof(b), 1, fp);

        if(feof(fp))
        {
            break;
        }

        /*Displaying records like this is better because in tabular format
        things get jumbled up if the string length is violated*/
        Sleep(30);
        printf("\n\t%c Book#%d : \n", 254, ++i);
        Sleep(30);
        printf("\n\tSerial No. = %s", b.serialno);
        Sleep(30);
        printf("\n\tName       = %s", b.name);
        Sleep(30);
        printf("\n\tAuthor     = %s", b.author);
        Sleep(30);
        printf("\n\tISBN       = %s", b.isbn);
        Sleep(30);
        printf("\n\tEdition    = %s", b.edition);
        Sleep(30);
        printf("\n\tReserved   = %s\n\n", b.reserved);
        Sleep(30);
    }

    printf("\t");
    system("pause");
    fclose(fp);
}

void issue_a_book()
{
    system("cls");

    char input[30], choice;

    int i = 0, size = 0, flag = 0;

    struct book reserve[30];

    printf("\n\t\t\t\t\t\t    Book Issuing Menu :");
    printf("\n\n\tThis will change the 'Reserved' status of the given record\n\tin Book_DB Database.\n\n");

    printf("\n\tName of the Book = ");
    gets(input);

    fp = fopen("Books_DB.txt", "r");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    while(1)
    {
        fread(&reserve[i], sizeof(reserve[i]), 1, fp);

        if (feof(fp))
        {
            break;
        }

        /*Reading records and checking whether mentioned
        book is already reserved or not. If already reserved
        then return to main menu after telling the user.*/
        if((strcmp(reserve[i].name, input) == 0))
        {
            if (strcmp(reserve[i].reserved, "Yes") == 0)
            {
                system("cls");

                printf("\n\t\t\t\t\t\t    Book Issuing Menu :");
                printf("\n\n\tThis will change the 'Reserved' status of the given record\n\tin Book_DB Database.\n\n");

                printf("\n\tEnter Book Name : %s", input);

                printf("\n\n\tBook Name '%s' is already reserved.", input);

                printf("\n\n\t");
                system("pause");
                return;
            }
            flag++;
        }

        i++;
        size++;
    }

    if(flag == 0)
    {
        printf("\n\tBook '%s' is not present in Book_DB database.\n\n\t", input);
        system("pause");
        return;
    }

    fclose(fp);

    fp = fopen("Books_DB.txt", "w");

    if (fp == NULL)
    {
        puts("\nFile inaccessible\n\n");
        system("pause");
        return;
    }

    for(i = 0; i < size; i++)
    {
        /*On user's approval the record is searched
        and the specified record's reserved status is altered.*/
        if((strcmp(reserve[i].name, input) == 0))
        {
            Sleep(30);
            printf("\n\tSerial No. = %s", b.serialno);
            Sleep(30);
            printf("\n\tName       = %s", b.name);
            Sleep(30);
            printf("\n\tAuthor     = %s", b.author);
            Sleep(30);
            printf("\n\tISBN       = %s", b.isbn);
            Sleep(30);
            printf("\n\tEdition    = %s", b.edition);
            Sleep(30);
            printf("\n\tReserved   = %s %c %s\n\n\t", b.reserved, 175, "Yes");
            Sleep(30);

            printf("\n\tReserve this Book : ");
            printf("\n\n\tPress 'y' to reserve this book.\n\tPress any other key to return to main menu.\n\n");
            printf("\tChoice = ");
            choice = getche();

            if(choice == 'y' || choice == 'Y')
            {
                strcpy(reserve[i].reserved, "Yes");

                system("cls");

                printf("\n\t\t\t\t\t\t    Book Issuing Menu :");
                printf("\n\n\t'Reserved' status of the following book has been altered to 'Yes'\n\tin Book_DB Database.\n\n");

                Sleep(30);
                printf("\n\tSerial No. = %s", reserve[i].serialno);
                Sleep(30);
                printf("\n\tName       = %s", reserve[i].name);
                Sleep(30);
                printf("\n\tAuthor     = %s", reserve[i].author);
                Sleep(30);
                printf("\n\tISBN       = %s", reserve[i].isbn);
                Sleep(30);
                printf("\n\tEdition    = %s", reserve[i].edition);
                Sleep(30);
                printf("\n\tReserved   = %s\n\n\t", reserve[i].reserved);
                Sleep(30);

                system("pause");
            }
        }

        fwrite(&reserve[i], sizeof(reserve[i]), 1, fp);
    }

    fclose(fp);
}
