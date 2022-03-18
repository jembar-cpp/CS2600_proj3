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
		address_book->fp = fopen(DEFAULT_FILE, "r"); // open the file
		if (address_book->fp == NULL) { // file wasn't created successfully
			return e_fail;
		}
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

	fclose(address_book->fp);

	return e_success;
}

int main() {
	AddressBook address_book;
	Status ret = load_file(&address_book);
	return 0;
}