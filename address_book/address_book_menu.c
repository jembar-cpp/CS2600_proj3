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

// Used functions from other files
Status save_file(AddressBook *address_book);

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
	Status ret;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			ret = save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	return ret;
}

Status list_contacts(AddressBook *address_book)
{
	menu_header("Search Result:\n");
	printf("============================================================================================================================");
	printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");
	for (int i = 0; i < address_book->count; i++) 
	{   
		char format[20] = " ";
		ContactInfo *ptr = address_book->list;
		printf("\n============================================================================================================================");
		printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+ptr)->si_no, (i+ptr)->name[0], (i+ptr)->phone_numbers[0], (i+ptr)->email_addresses[0]);
		for (int j = 1; j < 5; j++) {
			printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :"
			,format, format,(i+ptr)->phone_numbers[j], (i+ptr)->email_addresses[j]);
		}
		}
	printf("\n============================================================================================================================\n");
	char exit;
	do {
		exit = get_option(CHAR, "Press: [q] to Cancel: ");
	} while(exit != 'q');

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
	Status ret = e_back;
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
                ret = add_contacts(address_book);
				break;
			case e_search_contact:
				ret = search_contact(address_book);
				break;
			case e_edit_contact:
				ret = edit_contact(address_book);
				break;
			case e_delete_contact:
				ret = delete_contact(address_book);
				break;
			case e_list_contacts:
				ret = list_contacts(address_book);
				break;
			case e_save:
				ret = save_file(address_book);
				get_option(NONE, "Done. Please enter key to continue: ");
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return ret;
}

Status add_contacts(AddressBook *address_book)
{
	int end = 0;
	int edited = 0; // keep track of whether contact was edited or not
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
				edited = 1;
				printf("Enter the name: ");
				fgets(input, 500, stdin);
				if (input[strlen(input)-1] == '\n') {
					input[strlen(input)-1] = '\0';
				}
				strncpy(c.name[0], input, NAME_LEN);
				break;
			case e_third_opt:
				edited = 1;
				printf("Enter the phone number: ");
				fgets(input, 500, stdin);
				if (input[strlen(input)-1] == '\n') {
					input[strlen(input)-1] = '\0';
				}
				strncpy(c.phone_numbers[phoneCount], input, NUMBER_LEN);
				phoneCount++;
				break;
			case e_fourth_opt:
				edited = 1;
				printf("Enter the email address: ");
				fgets(input, 500, stdin);
				if (input[strlen(input)-1] == '\n') {
					input[strlen(input)-1] = '\0';
				}
				strncpy(c.email_addresses[emailCount], input, EMAIL_ID_LEN);
				emailCount++;
				break;
		}
	} while(end == 0);
	
	// Add the new contact
	if(edited) {
		c.si_no = address_book->count == 0 ? 0 : address_book->list[address_book->count-1].si_no+1;
		address_book->list[address_book->count++] = c;
		return e_success;
	}
	return e_back;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	int results[50]; // array of list indices for search matches
	for(int i = 0; i < 50; i++) {
		results[i] = -1; // -1: no match
	}
	int rCount = 0;
	switch(field) {
		case 1: // search by name
			for(int i = 0; i < loop_count; i++) {
				if(strcmp(address_book->list[i].name[0], str) == 0) { // successful match
					results[rCount++] = i;
				}
			}
			break;
		case 2: // search by phone number
			for(int i = 0; i < loop_count; i++) {
				for(int j = 0; j < PHONE_NUMBER_COUNT; j++) {
					if(strcmp(address_book->list[i].phone_numbers[j], str) == 0) { // successful match
						results[rCount++] = i;
					}
				}
			}
			break;
		case 3: // search by email address
			for(int i = 0; i < loop_count; i++) {
				for(int j = 0; j < EMAIL_ID_COUNT; j++) {
					if(strcmp(address_book->list[i].email_addresses[j], str) == 0) { // successful match
						results[rCount++] = i;
					}
				}
			}
			break;
		case 4: // search by serial number
			int sn = atoi(str);
			for(int i = 0; i < loop_count; i++) {
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
		for (int i = 0; i < rCount; i++) {   
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
		else if (mode == e_delete) {
			do {
				option = get_option(CHAR, "Press: [s] = Select, [q] | Cancel: ");
				if(option == 's') {
					ContactInfo c;
					int match = 0;
					int matchNum;
					char input[100];
					do {
						printf("Select a Serial Number (S.No) to Delete: ");
						fgets(input, 500, stdin);
						int sn = atoi(input);
						for (int i = 0; i < rCount; i++) {   
							c = address_book->list[results[i]];
							if (c.si_no == sn) {
								match = 1;
								matchNum = results[i];
								break;
							}
						}
						if(!match) {
							printf("Invalid serial number.\n");
						}
					} while(!match);
					
					// Print contact info
					printf("\n0. Back");
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
					option = get_option(CHAR, "Enter 'Y' to delete. [Press any key to ignore]: ");
					if(option == 'Y') {
						// Shift all elements down the list to delete the contact
						for(int i = matchNum; i < loop_count; i++) {
							address_book->list[i] = address_book->list[i+1];
						}
						address_book->count--;
					}
					return e_back;
				}
			} while(option != 'q');
		}
		return e_fail;
	}
	else {
		printf("No search results found.\n\n");
		return e_fail;
	}
}

Status search_contact(AddressBook *address_book)
{
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
			field = 1;
			break;
		case e_third_opt: // search by phone number
			printf("Enter the phone number: ");
			field = 2;
			break;
		case e_fourth_opt: // search by email
			printf("Enter the email address: ");
			field = 3;
			break;
		case e_fifth_opt: // search by ID
			printf("Enter the ID number: ");
			field = 4;
			break;
	}
	if(!back) {
		fgets(input, 500, stdin);
		if (input[strlen(input)-1] == '\n') {
			input[strlen(input)-1] = '\0';
		}
		Status result = search(input, address_book, address_book->count, field, "Search result:\n", e_search);
		if(result == e_success) {
			return e_success;
		}
	}
	else {return e_back;}
	return e_fail;
}

/**
 * Status edit_contact (AddressBook *address_book);
 * @author: Suhuan
 *
 * 1a. prompt user to choose Edit by :
 * name / phone No / email address / Serial No.
 * press 0 to exit, back to main menu;
 * 
 * 2. calling search function to find and display the search result
 *
 * 3a. Define a ContactInfo pointer named listPtr, assign the pointer to address_book.list
 * 3b. prompt user enter the serial No of contact list to edit,
 * 3c. search the corresponding rowfieldIndex for that list,
 * assign listPtr to the start address of that list: (address_book->list) + rowfieldIndex
 *
 * 4a. Display all information from that contact list in column format for each field
 *     output empty space if the corresponding string value is ""
 * 4b. prompt user to select option of editBy:
 * 4c. go back if user press 0
 *
 */
Status edit_contact (AddressBook *address_book) {

    char targetName[NAME_LEN];
    char targetPhone[NUMBER_LEN];
    char targetEmail[EMAIL_ID_LEN];
    char targetSi[32];

    int editBy;
    int str_len;
    int sNum;
    Status ret;

    EDIT_BY:
    //  1a.
        menu_header("Search Contact to edit by:\n");
        printf("0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email ID\n");
        printf("4. Serial No\n");

        printf("\nPlease select an option: ");
        editBy = get_option(NUM, "");

        if (editBy == 0) {
            return e_back;
        }


        switch (editBy) {

            case 1: {
                printf("Enter the Name: ");
                fgets(targetName, NAME_LEN - 1, stdin);

             //  scan through the user input within the max range
                str_len = strnlen(targetName, NAME_LEN - 1);

             //  add NUL termination to the char array to make it as string
                targetName[str_len - 1] = '\0';

                // calling search method with e_edit mode, field = 1 is for name
                ret = search(targetName, address_book, address_book->count, 1, "Search result:\n", e_edit);
                break;
            }


            case 2: {
                printf("Enter the Phone Number: ");
                fgets(targetPhone, NUMBER_LEN - 1, stdin);

                str_len = strnlen(targetPhone, NUMBER_LEN - 1);
                targetPhone[str_len - 1] = '\0';

                ret = search(targetPhone, address_book, address_book->count, 2, "Search result:\n", e_edit);
                break;
            }

            case 3: {
                printf("Enter the Email ID: ");
                fgets(targetEmail, EMAIL_ID_LEN - 1, stdin);
                str_len = strnlen(targetEmail, EMAIL_ID_LEN - 1);
                targetEmail[str_len - 1] = '\0';

                ret = search(targetEmail, address_book, address_book->count, 3, "Search result:\n", e_edit);
                break;
            }

            case 4: {
                printf("Enter the Serial ID: ");
                fgets(targetSi, 5, stdin);
                str_len = strnlen(targetSi, 5);
                targetSi[str_len - 1] = '\0';

                ret = search(targetSi, address_book, address_book->count, 4, "Search result:\n", e_edit);
                break;
            }

            default:
                goto EDIT_BY;
                break;

        } // end of switch (editBy)


        if (ret == e_fail) {
            goto EDIT_BY;
        }


        // select a serial number of a list to edit
        // create an ContactInfo pointer that points to the address of specify list
        GET_SI_NO:
	sNum = get_option(NUM, "Select a Serial Number (S.No) to Edit: ");

        // 3c
        ContactInfo* listPtr  = address_book->list;

        for (int rowfieldIndex = 0; rowfieldIndex < (address_book->count); rowfieldIndex++)
        {
            if ( sNum == ((address_book->list) + rowfieldIndex)->si_no )
            {
                listPtr += rowfieldIndex;
                break; 
            }
	
	    else if (rowfieldIndex == (address_book->count) - 1) {
     		printf("Serial Number does not exits.\n");
     		goto GET_SI_NO;
 	    }	 
        }

        // step 4
        do {
            menu_header("Edit Contact");
            printf("\n0. Back\n");

            // display name (only one name per contact)
            printf("1. Name       : %-s\n", (listPtr->name[0]));

            // display phone number
            printf("2. Phone No 1 : %-s\n", (listPtr->phone_numbers[0]));

            for (int phonefieldIndex = 1; phonefieldIndex < PHONE_NUMBER_COUNT; phonefieldIndex++) {

                // if there is more one phone numbers
                // if condition compares if the max length of a phone number are empty string with NUL termination
                // display        2 ...
                //                3 ...etc.
                if ( strcmp(listPtr->phone_numbers[phonefieldIndex], "") ) {
                    printf("\n%13d : %-s", phonefieldIndex + 1, listPtr->phone_numbers[phonefieldIndex]);
                }
            }


            // display email address
            printf("\n3. Email ID 1 : %-s\n", listPtr->email_addresses[0]);
            for (int emailfieldIndex = 1; emailfieldIndex < EMAIL_ID_COUNT; emailfieldIndex++) {

                if ( strcmp(listPtr->email_addresses[emailfieldIndex], "") ) {
                    printf("%13d : %-s\n", emailfieldIndex + 1, listPtr->email_addresses[emailfieldIndex]);
                }

            }


            printf("\n");
            menu_header("Edit Contact:\n\n");
            printf("0. Back\n");
            printf("1. Name\n");
            printf("2. Phone No\n");
            printf("3. Email ID\n");
           // printf("4. Serial No\n");
            printf("\nPlease select an option: ");

            editBy = get_option(NUM, "");


            /**
             *  actual Edit part: 
             * 1a. prompt user to enter the fieldIndex of that field to edit
             * 1b. get the user input, break if out of the max count of that field
             * 2a. prompt user for the new one
             * 2b. add null termination by the end
             * 3. copy user input to replace the old one in the same position
             */
            int fieldIndex;
            int input_len;

            // only allow user to edit name / phone NO./ email
            switch (editBy) {

                case 0:
                    return e_back;

                case 1: {
                    // step 1
                    printf("Enter name index to be changed [Max %d]: ", NAME_COUNT);
                    char* target = (char*) malloc(sizeof(char) * NAME_LEN);
                    fgets(target, NAME_LEN, stdin);
                    fieldIndex = atoi(target);
                    if (fieldIndex < 1 || fieldIndex > NAME_COUNT) {
                        break;
                    }

                    // step 2
                    printf("Enter Name %d: [Just enter removes the entry]: ", fieldIndex);

                    fgets(target, NAME_LEN, stdin);
                    input_len = strlen(target) - 1;

                    // adding NULL termination
                    if (target[input_len] == '\n')
                    {
                        target[input_len] = '\0';
                    }

                    // step 3, copy user defined e name to the corresponding list.name
                    strncpy(listPtr->name[fieldIndex - 1], target, NAME_LEN);
                    free(target);

                    break;
                }


                case 2: {

                    printf("Enter Phone Number index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
                    char* target = (char*) malloc(sizeof(char) * NUMBER_LEN);
                    fgets(target, NUMBER_LEN, stdin);

                    // convert the integer to string representation
                    fieldIndex = atoi(target);

                    if (fieldIndex < 1 || fieldIndex > PHONE_NUMBER_COUNT)
                    {
                        break;
                    }

                    printf("Enter Phone Number %d: [Just enter removes the entry]: ", fieldIndex);

                    fgets(target, NUMBER_LEN, stdin);
                    input_len = strlen(target) - 1;

                    if (target[input_len] == '\n')
                    {
                        target[input_len] = '\0';
                    }

                    strncpy(listPtr->phone_numbers[fieldIndex - 1], target, NUMBER_LEN);
                    free(target);

                    break;
                }

                case 3: {
                    char* target = (char*) malloc(sizeof(char) * EMAIL_ID_LEN);

                    printf("Enter Email ID fieldIndex to be changed [Max %d]: ", EMAIL_ID_COUNT);
                    fgets(target, EMAIL_ID_LEN, stdin);
                    fieldIndex = atoi(target);

                    if (fieldIndex < 1 || fieldIndex > EMAIL_ID_COUNT)
                    {
                        break;
                    }

                    printf("Enter Email ID %d: [Just enter removes the entry]: ", fieldIndex);

                    fgets(target, EMAIL_ID_LEN, stdin);
                    input_len = strlen(target) - 1;

                    if (target[input_len] == '\n')
                    {
                        target[input_len] = '\0';
                    }

                    strncpy(listPtr->email_addresses[fieldIndex - 1], target, EMAIL_ID_LEN);
                    free(target);

                    break;
                }

                default:
                    break;
            }


        } while (editBy != e_back);



    free(listPtr);

    return e_success;

}

Status delete_contact(AddressBook *address_book)
{
	char input;
	int field;
    char searchword[50];
	do {
		menu_header("Search Contact to Delete by:");
		printf("\n0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No 1");
		printf("\n3. Email ID 1");
		printf("\n4. Serial No\n");
		input = get_option(NUM, "Please select an option for search: ");
	}
	while (input != e_first_opt
			&& input != e_second_opt 
			&& input != e_third_opt 
			&& input != e_fourth_opt 
			&& input != e_fifth_opt);

	if (input == e_second_opt){
		printf("\nEnter name: ");
		field = 1;
	}
	else if (input == e_third_opt){
		printf("\nEnter Phone No 1: ");
		field = 2;
	}
	else if (input == e_fourth_opt){
		printf("\nEnter Email ID 1: ");
		field = 3;
	}
	else if (input == e_fifth_opt){
		printf("\nEnter Serial No: ");
		field = 4;
	}
	if(input != e_first_opt) {
		fgets(searchword, 500, stdin);
		if (searchword[strlen(searchword)-1] == '\n') {
			searchword[strlen(searchword)-1] = '\0';
		}
		Status result = search(searchword, address_book, address_book->count, field, "Search result:\n", e_delete);
		if (result == e_back) {return e_back;}
		if (result == e_fail) {return e_fail;}
		return e_success;
	}
	return e_back;
}
