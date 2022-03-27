#include <stdio.h>
// ? #include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "address_book.h"
//#include "address_book_fops.h"
//#include "address_book_menu.h"

#include "address_book_fops.c"
#include "address_book_menu.c"



int main()
{
    printf("============= Project 3, Group 2 =============\n");
    AddressBook address_book;
    // address_book = (AddressBook*) malloc((sizeof(int) + sizeof(FILE *) + sizeof(ContactInfo *)) * 100);
    Status ret;

    /* Load the file from .csv file if any */
    ret = load_file(&address_book);


    if (ret == e_success)
    {
        printf("\n----- Calling menu() function in main to show all the available menu. -----\n");

        /* Show all the available menu */
        // ret = edit_contact(&address_book);
        ret = menu(&address_book);

        if (ret == e_success)
        {
            printf("\n----- Calling save_prompt() function in main to save the entries. -----\n");
            /* Save the entries */
            save_prompt(&address_book);
        }

    }


    free(address_book.list);

    printf("\n============= END of Project 3, Group 2 =============\n");
    return 0;
}