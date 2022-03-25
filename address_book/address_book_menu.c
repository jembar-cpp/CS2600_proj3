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
    	ContactInfo* contactInfo = address_book->list; 
	if (mode == e_list) 
    	{
		menu_header("Search Result:\n");
		printf("============================================================================================================================");
		printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");
		for (int i = 0; i < address_book->count; i++) 
		{   
			char format[20] = " ";
			ContactInfo *ptr = address_book->list;
			printf("\n============================================================================================================================");
			printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+ptr)->si_no, (i+ptr)->name, (i+ptr)->phone_numbers[0], (i+ptr)->email_addresses);
			for (int j = 1; j < 5; j++) {
				printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :"
				,format, format,(i+ptr)->phone_numbers[j], (i+ptr)->email_addresses[j]);
			}
    		}
		printf("\n============================================================================================================================");
		char exit[10];
		while(strcmp(exit, "q") != 0) {
			printf("\nPress: [q] to Cancel: ");
			scanf("%s", exit);
		}
	}
	else if(mode == e_add) 
    	{
		menu_header("Add Contact: ");
		printf("\n0. Back");
		printf("\n1. Name        : %s", ((address_book->count)+contactInfo)->name);
		printf("\n2. Phone No 1  : %s",((address_book->count)+contactInfo)->phone_numbers[0]);
		printf("\n3. Email ID 1  : %s", ((address_book->count)+contactInfo)->email_addresses[0]);
	}

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
	ContactInfo* contactInfo = address_book->list;
    char response[255]; 
    //no data added
    int addedData =1; 
    contactInfo = (ContactInfo*) realloc(contactInfo, ((address_book->count + 1) * sizeof(ContactInfo)));
    address_book->list = contactInfo; 
    strcpy(*((address_book->count) + contactInfo)->name, " ");
    strcpy(((address_book->count) + contactInfo)->phone_numbers[0], " ");
    strcpy(((address_book->count) + contactInfo)->email_addresses[0], " ");

    while(strcmp(response, "0") != 0)
    {
        list_contacts(address_book, "lister", 0, "list", e_add);
        printf("\n\nPlease select an option for add: ");
        scanf("%s", response);
        if(strcmp(response, "1") == 0)
        {
            printf("\nEnter name: ");
            scanf("%s", ((address_book->count) + contactInfo)->name); 
            //data was added
            addedData = 0;
        } 
        else if(strcmp(response, "2") ==0)
        {
            printf("\nEnter Phone No 1: ");
            scanf("%s", ((address_book->count) + contactInfo)->phone_numbers[0]); 
            //data was added
            addedData = 0;
        }
        else if(strcmp(response, "3")==0)
        {
            printf("\nEnter Email ID 1: ");
            scanf("%s", ((address_book->count) + contactInfo)->email_addresses[0]); 
            //data was added
            addedData = 0;
        }
    }
    //if anything was added 
    if(addedData ==0)
    {
        ((address_book->count)+contactInfo)->si_no = address_book->count + 1;
        for(int i =1; i <5; ++i)
        {
            strcpy(((address_book->count)+contactInfo)->phone_numbers[i], " ");
            strcpy(((address_book->count)+contactInfo)->email_addresses[i], " ");
        }
        ++address_book->count; 
    }
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
    ContactInfo* contactInfo = address_book->list;
	
	char response[255];
	char searchword[255];
	char searchBy[255];
	char selection[10];
	while (strcmp(response, "0") != 0) 
    {
		menu_header("Search Contact to Delete by:");
		strcmp(selection, "select");
		printf("\n0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No 1");
		printf("\n3. Email ID 1");
		printf("\n4. Serial No");
		printf("\n\nPlease select an option for search: ");
		scanf("%s", response);
		while (strcmp(response, "0") != 0 && strcmp(response, "1") != 0 && strcmp(response, "2") != 0 && strcmp(response, "3") != 0 && strcmp(response, "4") != 0) 
        {
			menu_header("Search Contact by:");
			strcpy(selection, "noexit");
			printf("\n0. Back");
			printf("\n1. Name");
			printf("\n2. Phone No 1");
			printf("\n3. Email ID 1");
			printf("\n4. Serial No");
			printf("\n\nPlease select an option for search: ");
			scanf("%s", response);
		}
		if (strcmp(response, "0") == 0){
			break;
		}
        if (strcmp(response, "1") == 0){
            printf("\nEnter name: ");
            scanf("%s", searchword);
            strcpy(searchBy, "Name");
        }
        if (strcmp(response, "2") == 0){
            printf("\nEnter Phone No 1: ");
            scanf("%s", searchword);
            strcpy(searchBy, "Phone");
        }
        if (strcmp(response, "3") == 0){
            printf("\nEnter Email ID 1: ");
            scanf("%s", searchword);
            strcpy(searchBy, "Email");
        }
        if (strcmp(response, "4") == 0){
            printf("\nEnter Serial No: ");
            scanf("%s", searchword);
            strcpy(searchBy, "Serial");
        }
        
        menu_header("Search Result:\n");
		printf("============================================================================================================================");
		printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");
		for (int i = 0; i < address_book->count; i++) {   
			char format[20] = " ";
			ContactInfo *ptr = address_book->list;
			printf("\n============================================================================================================================");
			printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+ptr)->si_no, (i+ptr)->name, (i+ptr)->phone_numbers[0], (i+ptr)->email_addresses);
			for (int j = 1; j < 5; j++) {
				printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :",format, format,(i+ptr)->phone_numbers[j], (i+ptr)->email_addresses[j]);
			}
    	}

        while(strcmp(selection, "q") != 0) 
        {
            printf("\nPress: [s] = Select, [q] to Cancel: ");
            scanf("%s", selection);
            if (strcmp(selection, "q") != 0) 
            {
                printf("\nSelect a Serial Number (S.No) to Edit: ");
                scanf("%s", searchword);
                menu_header("Edit Contact: ");

                for (int i = 0; i < address_book->count; i++) 
                {
                    if (search(searchword, address_book, 4, "Serial", e_search) == e_success) 
                    {
                        while (strcmp(response, "0") != 0) 
                        {
                            menu_header("Edit Contact: ");
                            printf("\n0. Back");
                            printf("\n1. Name        : %s", ((i)+contactInfo)->name);
                            printf("\n2. Phone No 1  : %s",((i)+contactInfo)->phone_numbers[0]);
                            int counter = 3;
                            int amtOfEmails = 1;
                            int amtOfPhones = 1;
                            for (int j= 1; j < 5; j++) 
                            {
                                if (strcmp((i+contactInfo)->phone_numbers[j], " ") != 0) 
                                {
                                    printf("\n   Phone No %d: %s", j+1,(i+contactInfo)->phone_numbers[1]);
                                    counter++;
                                    amtOfPhones++;
                                }
			   }
                            printf("\n3. Email ID 1  : %s", ((i)+contactInfo)->email_addresses[0]);
                            for (int j= 1; j < 5; j++) {
                                if (strcmp((i+contactInfo)->email_addresses[j], " ") != 0) {
                                    printf("\n   Email No %d  : %s", j+1,(i+contactInfo)->email_addresses[j]);
                                    amtOfEmails++;
                                    counter++;
                                }
                            }
                            printf("\n3. Email ID 1  : %s", ((i)+contactInfo)->email_addresses[0]);
                            for (int j= 1; j < 5; j++) {
                                if (strcmp((i+contactInfo)->email_addresses[j], " ") != 0) {
                                    printf("\n   Email No %d  : %s", j+1,(i+contactInfo)->email_addresses[j]);
                                    amtOfEmails++;
                                    counter++;
                                }
                            }
                            printf("\n\nPress 'Y' to delete. [Press any key to ignore]: ");
                            scanf("%s", response);
                            if (strcmp(response, "Y") == 0) 
			    {
                                ContactInfo c; 
				int pos =0;
				for(int i=0; i<address_book->count; ++i)
				{
					if(address_book->list[i].si_no == atoi(searchword))
					{
						c = address_book->list[i];
						pos = i; 
					}
				}
				for(int i= pos; i<address_book->count-1; ++i)
				{
					address_book->list[i] = address_book->list[i+1]; 
				}
				--address_book->count;

                            }
                            strcpy(response, "0");
                            strcpy(selection, "q");
                        }
                    }
                }	
        
            }
        }  
    }
}        
       
