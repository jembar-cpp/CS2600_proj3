#include <stdio.h>
// #include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h" 
#include "address_book_fops.h"

// #include "abk_fileops.h"
// #include "abk_log.h"
// #include "abk_menus.h"
// #include "abk.h"
// 

int searchBy () {

   printf("0. Back\n"
        "1. Name\n"
        "2. Phone No\n"
        "3. Email ID\n"
        "4. Serial No\n"
        "\nPlease select an option: ");

	return get_option(NUM, "");
}


/*
 * Mutilfuction user intractions like
 * Just an enter key detection
 * Read an number
 * Read a charcter
 */ 
int get_option(int type, const char *msg)
{
	//  printf("%s\n", msg);
	
   if (type == CHAR || type == NUM) {
        int option;
        scanf("%d", &option);
        return option;
    }
	 
	 //  else if (type == NONE) 
	else {
		printf("%s\n", msg);
      return e_no_match;
   }

}



Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	// fflush(stdout);

	// system("clear");

	printf("#######  Address Book  #######\n");
	if (str != (void *) '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");

	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option = 0; // default

	do
	{
		main_menu();

		option = get_option(NUM, "");

		printf("\n");


		// what if it's an empty file?
		// if ((address_book-> count == 0) && (option != e_add_contact))
		// {
			// get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			// continue;
		// }

		switch (option)
		{
			case e_add_contact:  // 1
				/* Add your implementation to call add_contacts function here */
				add_contacts(address_book);
				break;

			case e_search_contact:
				search_contact(address_book);
				break;

			case e_edit_contact:
				edit_contact(address_book);
				break;

			case e_delete_contact:
				delete_contact(address_book);
				break;

			case e_list_contacts:
				// list_contacts(address_book);
				break;

			
			case e_save:
				save_file(address_book);
				break;

			case e_exit: // 0
				EXIT_SUCCESS;
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	return e_success;
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	return e_success;
}



Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	return e_success;
}
// 
// 