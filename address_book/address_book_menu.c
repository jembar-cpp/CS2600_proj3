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
	/* Add the functionality for delete contacts here */
}