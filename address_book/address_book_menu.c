#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"
//#include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
    printf("%s", msg);

    int option = 0;

    if (type == NONE) {
        getc(stdin);
    }
    else if (type == CHAR) {
        option = getc(stdin);
    }
    else if (type == NUM) {
        option = getc(stdin);
        if (option >= '0' && option <= '9')
        {
            option -= '0';
        }
    }
    else {
        printf("Passed invalid int type to get_option function\n");
        EXIT_FAILURE;
    }

    fflush(stdin);
    return option;
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
			Status ret = save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book)
{
    ContactInfo* contactInfo = address_book->list; 
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

	return e_success;
}

void menu_header(const char *str)
{
	printf("#######  Address Book  #######\n");
	if (strcmp(str, "") != 0)
	{
		printf("#######  %s\n", str);
	}
}

void main_menu()
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
	char option;

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
				list_contacts(address_book);
				break;
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
	int end = 0;
	ContactInfo c;

	// Contacts have a dynamic amount of phone numbers and emails, so they must be cleared first
	for (int i = 0; i < NAME_COUNT; i++) {
		strcpy(c.name[i], "\0"); // clear names - this would be necessary if a contact could have multiple names
	}
	for (int i = 0; i < PHONE_NUMBER_COUNT; i++) {
		strcpy(c.phone_numbers[i], "\0"); // clear phone numbers
	}
	for (int i = 0; i < EMAIL_ID_COUNT; i++) {
		strcpy(c.email_addresses[i], "\0"); // clear emails
	}
	int phoneCount = 0; // number of phone numbers
	int emailCount = 0; // number of emails

	do {
		menu_header("Add Contact:\n");
		printf("0. Back");
		printf("\n1. Name : ");
		if(strcmp(c.name[0], "") != 0) { // check if name is set
			printf("%s", c.name[0]);
		}
		printf("\n2. Phone No 1 : ");
		if(strcmp(c.phone_numbers[0], "") != 0) { // check if phone number is set
			printf("%s", c.phone_numbers[0]);
		}
		// Print the rest of the phone numbers
		for(int i = 1; strcmp(c.phone_numbers[i], "") != 0; i++) {
			printf("\n            %d : %s",i+1,c.phone_numbers[i]);
		}
		
		printf("\n3. Email ID 1 : ");
		if(strcmp(c.email_addresses[0], "") != 0) { // check if email is set
			printf("%s", c.email_addresses[0]);
		}
		// Print the rest of the emails
		for(int i = 1; strcmp(c.email_addresses[i], "") != 0; i++) {
			printf("\n            %d : %s",i+1,c.email_addresses[i]);
		}
		printf("\n\n");
		int option = get_option(NUM, "Please select an option: ");

		switch(option) {
			char input[500];
			case e_first_opt:
				end = 1;
				break;
			case e_second_opt:
				printf("Enter the name: ");
				fgets(input, 500, stdin);
				if (input[strlen(input)-1] == '\n') {
					input[strlen(input)-1] = '\0';
				}
				strcpy(c.name[0], input);
				break;
			case e_third_opt:
				printf("Enter the phone number: ");
				fgets(input, 500, stdin);
				if (input[strlen(input)-1] == '\n') {
					input[strlen(input)-1] = '\0';
				}
				strcpy(c.phone_numbers[phoneCount], input);
				phoneCount++;
				break;
			case e_fourth_opt:
				printf("Enter the email address: ");
				fgets(input, 500, stdin);
				if (input[strlen(input)-1] == '\n') {
					input[strlen(input)-1] = '\0';
				}
				strcpy(c.email_addresses[emailCount], input);
				emailCount++;
				break;
		}
	} while(end == 0);
	
	// Add the new contact
	c.si_no = address_book->count;
	address_book->list[address_book->count++] = c;
}

Status search(const char *str, AddressBook *address_book, int field, const char *msg, Modes mode)
{
	int results[50]; // array of list indices for search matches
	for(int i = 0; i < 50; i++) {
		results[i] = -1; // -1: no match
	}
	int rCount = 0;
	switch(field) {
		case 1: // search by name
			for(int i = 0; i < address_book->count; i++) {
				if(strcmp(address_book->list[i].name[0], str) == 0) { // successful match
					results[rCount++] = i;
				}
			}
			break;
		case 2: // search by phone number
			for(int i = 0; i < address_book->count; i++) {
				for(int j = 0; j < PHONE_NUMBER_COUNT; j++) {
					if(strcmp(address_book->list[i].phone_numbers[j], str) == 0) { // successful match
						results[rCount++] = i;
					}
				}
			}
			break;
		case 3: // search by email address
			for(int i = 0; i < address_book->count; i++) {
				for(int j = 0; j < EMAIL_ID_COUNT; j++) {
					if(strcmp(address_book->list[i].email_addresses[j], str) == 0) { // successful match
						results[rCount++] = i;
					}
				}
			}
			break;
		case 4: // search by serial number
			int sn = atoi(str);
			for(int i = 0; i < address_book->count; i++) {
				if(sn == address_book->list[i].si_no) { // successful match
					results[rCount++] = i;
				}
			}
			break;
	}
	if(rCount > 0) {
	char *pNum;
		menu_header(msg);
		printf("============================================================================================================================");
		printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");
		for (int i = 0; i < rCount; i++) 
			{   
				ContactInfo c = address_book->list[results[i]];
				char format[2] = " ";
				printf("\n============================================================================================================================");
				printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", c.si_no, c.name[0], c.phone_numbers[0], c.email_addresses[0]);
				for (int j = 1; j < EMAIL_ID_COUNT; j++) {
					if(j < PHONE_NUMBER_COUNT) {
						pNum = c.phone_numbers[j];
					}
					else {
						pNum = format;
					}
					printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :",format, format, pNum , c.email_addresses[j]);
				}
			}
		printf("\n============================================================================================================================\n");
		int option;
		if (mode == e_search) {
			do {
				option = get_option(CHAR, "Press: [q] | Cancel: ");
			} while(option != 'q');
			return e_success;
		}
		else if (mode == e_edit) {
			do {
				option = get_option(CHAR, "Press: [s] = Select, [q] | Cancel: ");
				if(option == 's') {
					return e_success;
				}
			} while(option != 'q');
		}
		return e_fail;
	}
	else {
		printf("No search results found.\n");
		return e_fail;
	}
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	menu_header("Search Contact by:\n");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n");
	printf("4. Serial No\n\n");
	int option = get_option(NUM, "Please select an option: ");

	int back = 0;
	char input[500];
	int field;
	switch(option) {
		case e_first_opt: // go back
			back = 1;
			break;
		case e_second_opt: // search by name
			printf("Enter the name: ");
			fgets(input, 500, stdin);
			if (input[strlen(input)-1] == '\n') {
				input[strlen(input)-1] = '\0';
			}
			field = 1;
			break;
		case e_third_opt: // search by phone number
			printf("Enter the phone number: ");
			fgets(input, 500, stdin);
			if (input[strlen(input)-1] == '\n') {
				input[strlen(input)-1] = '\0';
			}
			field = 2;
			break;
		case e_fourth_opt: // search by email
			printf("Enter the email address: ");
			fgets(input, 500, stdin);
			if (input[strlen(input)-1] == '\n') {
				input[strlen(input)-1] = '\0';
			}
			field = 3;
			break;
		case e_fifth_opt: // search by ID
			printf("Enter the ID number: ");
			if (input[strlen(input)-1] == '\n') {
				input[strlen(input)-1] = '\0';
			}
			field = 4;
			break;
	}
	if(!back) {
		Status result = search(input, address_book, field, "Search result:\n", e_search);
	}
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