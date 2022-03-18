#include <stdio.h>
// ? #include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book_fops.c"
#include "address_book_menu.c"
#include "panda_work.c"


int main(void)
{
     printf("============= Project 3, Group 2 =============\n");
     AddressBook address_book;
     Status ret;

    /* Load the file from .csv file if any */
    ret = load_file(&address_book);

    if (ret == e_success)
    {
        printf("\n----- Calling menu() function in main to show all the available menu. -----\n");
        
        /* Show all the available menu */
        // ret = menu(&address_book);

        if (ret == e_success)
        {
            printf("\n----- Calling save_prompt() function in main to save the entries. -----\n");
            /* Save the entries */
         //   save_prompt(&address_book);
        }

        
    }

   
    printf("\n============= END of Project 3, Group 2 =============\n");
    return 0;
}
