#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

/**
 * Function load_file
 * Checks whether the address book file exists or not.
 * If the file does not exist, it is created.
 * Return success if the file exists or if it was created properly.
 * Return failure if the file was not created properly.
 * 
 * @param address_book, pointer to an address book
 * @return Status (enum), whether the file exists / has been created or not.
 */
Status load_file(AddressBook *address_book)
{
	int ret;

	/* 
	 * Check for file existance
	 */
	ret = access(DEFAULT_FILE, F_OK); // sets ret to 0 if the file exists

	if (ret == 0)
	{
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 
		address_book->fp = fopen(DEFAULT_FILE, "w"); // open the file
		if (address_book->fp == NULL) { // file wasn't created successfully
			return e_fail;
		}
		fclose(address_book->fp);
	}
	else
	{
		/* Create a file for adding entries */
		address_book->fp = fopen(DEFAULT_FILE, "w"); // create the file
		fclose(address_book->fp); // close the file
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 
	rewind(address_book->fp); // overwrite the file
	for(int i = 0; i < address_book->count; i++) { // loop through list of contacts
		ContactInfo cur = address_book->list[i]; // get the current contact info
		// Write the name of the contact
		fprintf(address_book->fp,"%s%c",cur.name,FIELD_DELIMITER);

		// Write the contact's phone numbers
		for(int j = 0; strcmp(cur.phone_numbers[j],"") != 0; j++) {
			fprintf(address_book->fp,"%s%c",cur.phone_numbers[j],FIELD_DELIMITER);
		}

		// Write the contact's email addresses
		for(int j = 0; strcmp(cur.email_addresses[j],"") != 0; j++) {
			fprintf(address_book->fp,"%s%c",cur.email_addresses[j],FIELD_DELIMITER);
		}
		fprintf(address_book->fp,"%c",NEXT_ENTRY);
	}
	

	fclose(address_book->fp);

	return e_success;
}

// Temporary - Not included in final project
int main() {
	AddressBook address_book;
	Status ret = load_file(&address_book); // attempt to load the file, create it if it does not exist

	// Create a set of contact info
	ContactInfo c;
	for (int i = 0; i < PHONE_NUMBER_COUNT; i++) {
		strcpy(c.phone_numbers[i], "\0"); // clear phone numbers
	}
	for (int i = 0; i < EMAIL_ID_COUNT; i++) {
		strcpy(c.email_addresses[i], "\0"); // clear emails
	}

	strcpy(c.name[0], "Contact name 1");
	strcpy(c.phone_numbers[0], "111-111-1111");
	strcpy(c.phone_numbers[1], "222-222-2222");
	strcpy(c.email_addresses[0], "email1@email.com");
	c.si_no = 0;
	int size = sizeof(c.phone_numbers);

	// Create another set of contact info
	ContactInfo c2;
	for (int i = 0; i < PHONE_NUMBER_COUNT; i++) {
		strcpy(c2.phone_numbers[i], "\0"); // clear phone numbers
	}
	for (int i = 0; i < EMAIL_ID_COUNT; i++) {
		strcpy(c2.email_addresses[i], "\0"); // clear emails
	}

	memset(c2.name, '\0', NAME_COUNT); // clear contact
	memset(c2.phone_numbers, '\0', PHONE_NUMBER_COUNT);
	memset(c2.email_addresses, '\0', EMAIL_ID_COUNT);

	strcpy(c2.name[0], "Contact name 2");
	strcpy(c2.phone_numbers[0], "333-333-3333");
	strcpy(c2.phone_numbers[1], "444-444-4444");
	strcpy(c2.phone_numbers[2], "555-555-5555");
	strcpy(c2.email_addresses[0], "email2@email.com");
	strcpy(c2.email_addresses[1], "email3@email.com");
	c2.si_no = 1;

	// Add the contact info to the address book's list of contact info
	address_book.list = calloc(10, sizeof(ContactInfo));
	address_book.list[0] = c;
	address_book.list[1] = c2;
	address_book.count = 2;
	
	ret = save_file(&address_book);
	free(address_book.list); // free memory when it's done
	
	return 0;
}