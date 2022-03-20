#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "abk_fileops.h"
#include "abk_log.h"
#include "abk_menus.h"
#include "abk.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
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
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
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
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
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
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
    char choice; 
    char* searchWord[255];
    char searchBy[255];
    char select[10];
    while(strcmp(choice,'0') !=0)
    {
        //call menu_header function 
        menu_header("Search Contact to Delete by: "); 
        strcmp(select, "select");
        //choices 
        printf("\n0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No 1\n");
        printf("4. Serial No\n");
        prontf("Please select an option for search: "); 
        scanf("%c", choice); //save the result in var choice 
        //input validation loop 
        while((int)choice <0 || (int)choice > 4)
        {
            //call menu_header function 
            menu_header("Search Contact to Delete by: "); 
            strcmp(select, "select");
            //choices 
            printf("\n0. Back\n");
            printf("1. Name\n");
            printf("2. Phone No 1\n");
            printf("4. Serial No\n");
            prontf("Please select an option for search: "); 
            scanf("%s", choice); //save the result in var choice 
        }
        //Back 
        if(strcmp(choice, '0') ==0)
        {
            break; //stop 
        }
        //Name 
        else if(strcmp(choice, '1') ==0)
        {
            printf("\nEnter the name: ");
            scanf("%s", searchWord);
            strcpy(searchBy, "Name"); 
        }
        //Phone Number  
        else if(strcmp(choice, '2') ==0)
        {
            printf("\nEnter Phone No 1: ");
            scanf("%s", searchWord);
            strcpy(searchBy, "Phone"); 
        }
        //Email 
        else if(strcmp(choice, '3') ==0)
        {
            printf("\nEnter Email ID 1: ");
            scanf("%s", searchWord);
            strcpy(searchBy, "Email"); 
        }
        //Serial No 
        else if(strcmp(choice, '4') ==0)
        {
            printf("\nEnter Serial No: ");
            scanf("%s", searchWord);
            strcpy(searchBy, "Serial"); 
        }
        //view the search results 
        menu_header("Search Result:\n");
        printf("===================================================================================================");
        printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");

        for(int i=0; i < newAddress ->count; ++i)
        {
            if(search(searchWord, address_book, i, 0, searchBy, e_search) == e_success)
            {
                 char format[20] = " ";
                ContactInfo *contactPtr = newAddress ->list;
                printf("==================================================================================================");
                printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+contactPtr)->si_no, (i+contactPtr)->name, (i+contactPtr)->phone_numbers[0], (i+contactPtr)->email_addresses); 
                for(int j=1; j<5; ++j)
                {
                    printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :",format, format,(i+contactPtr)->phone_numbers[j], (i+contactPtr)->email_addresses[j]);

                }
            }

        }
        while(strcmp(choice,'q')!=0)
        {
            printf("\nPress: [s] = Select, [q] to Cancel: ");
            scanf("%s", choice);
            if(strcmp(choice,'q')!=0)
            {
                printf("\nSelect a Serial Number (S.No) to Edit: ");
                scanf("%s", searchWord); 
                menu_header("Edit Contact: "); 
                for(int i=0; i < newAddress->count; ++i)
                {
                    if(search(searchWord, address_book,i,0,"Serial",e_search) ==e_success)
                    {
                        while(strcmp(choice,'0')!=0)
                        {
                            menu_header("Edit Contact: ");
                            printf("\n0. Back");
                            printf("\n1. Name       : %s", ((i)+contactinfo)->name);
                            printf("\n2. Phone No 1 : %s", ((i)+contactinfo)->phone_numbers[0]);
                            int counter = 3; 
                            int amtOfEmails = 1; 
                            int amtOfPhones = 1;
                            for(int j=1; j<5; ++j)
                            {
                                if(strcmp((i+contactinfo)->phone_numbers[j], " ") !=0)
                                {
                                    printf("\n Phone No %d: %s", j+1, (i + contactinfo)->phone_numbers[1]);
                                    ++counter;
                                    ++amtOfPhones;
                                }
                            }
                            printf("\n3. Email ID 1 : %s", ((i)+contactinfo)->email_addresses[0]);
                            for(int j=1; j<5;++j)
                            {
                                if(strcmp((i+contactinfo)->email_addresses[j], " ") !=0)
                                {
                                    printf("\n  Email No %d  :  %s", j+1,(i+contactinfo)->email_addresses[j]);
                                    ++amtOfEmails;
                                    ++counter;
                                }
                            }
                            printf("\n\nPress Y to delete. You can press any other key to ignore. ");
                            scanf("%s", choice);
                            if(strcmp(choice, 'Y') ==0)
                            {
                                ContactInfo *contactPtr = newAddress->list;
                                printf("\nSerial: %d", (i+contactPtr)->si_no);
                                strcpy(*(i+contactPtr)->name, *((newAddress->count-1)+contactPtr)->name);
                                for(int j=0; j,5;++j)
                                {
                                    strcpy((i+contactPtr)->phone_numbers[j], ((newAddress->count-1)+contactPtr)->phone_numbers[j]);
                                }
                                for(int j=0; j,5;++j)
                                {
                                    strcpy((i+contactPtr)->email_addresses, ((newAddress->count-1)+contactPtr)->email_addresses[j]);
                                }
                                contactinfo = (ContactInfo*) realloc(contactinfo, ((newAddress->count - 1) * sizeof(ContactInfo)));
                                newAddress->list = contactinfo;
                                newAddress->count--; 
                            }
                            strcpy(choice,'0');
                            strcpy(choice,'q');
                        }
                    }
                }
            }
        }
    }
}
