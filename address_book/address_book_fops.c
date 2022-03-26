/**
 * @file address_book_fops.c
 * @author Jeremy Embar
 *
 * Handles file operations for the address book.
 * Responsible for loading and saving the contents of the address book.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ctype.h>

#include "address_book.h"

/**
 * Function load_file
 * Loads the content of the address book's CSV file into the address book's memory.
 * If the file does not already exist, it is created.
 * Return success if the file exists or if it was created properly.
 * Return failure if the file was not created properly.
 *
 * @param address_book, pointer to an address book
 * @return Status (enum), whether the file was successfully read / created or not.
 */
Status load_file(AddressBook *address_book)
{
    int ret = access(DEFAULT_FILE, F_OK); // sets ret to 0 if the file exists
    address_book->list = calloc(1000, sizeof(ContactInfo)); // allocate memory for contacts - maximum of 1000 contacts

    if (ret == 0)
    {
        address_book->fp = fopen(DEFAULT_FILE, "r"); // open the file for reading
        if (address_book->fp == NULL) { // file wasn't opened successfully
            return e_fail;
        }
        char line[500];
     //   char *number = NULL;
        int len;
        for (address_book->count = 0; fgets(line, 500, address_book->fp); address_book->count++) { // read file line by line
            ContactInfo c; // create a new contact

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

            char *field1 = strchr(line, FIELD_DELIMITER)+1; // get the first field - name
            len = field1-line-1;
            strncpy(c.name[0], line, len);
            c.name[0][len] = '\0'; // null-terminate string

            char *field2 = strchr(field1, FIELD_DELIMITER)+1; // get the second field - phone numbers
            len = field2-field1-1;
            char numbers[NUMBER_LEN*PHONE_NUMBER_COUNT];
            strncpy(numbers, field1, len);
            numbers[len] = '\0';

            char *field3 = strchr(field2, FIELD_DELIMITER)+1; // get the third field - email addresses
            len = field3-field2-1;
            char emails[EMAIL_ID_LEN*EMAIL_ID_COUNT];
            strncpy(emails,field2,len);
            emails[len] = '\0';

            char *field4 = strchr(field3, NEXT_ENTRY)+1; // get the fourth field - ID number
            len = field4-field3-1;
            char id[10];
            strncpy(id,field3,len);
            id[len] = '\0';
            c.si_no = atoi(id);

            // Parse numbers and add to contact
            if(strlen(numbers) != 0) { // at least 1 number
                char *number = strchr(numbers, FIELD_SEPARATOR)+1;
                char *number_prev = number; // pointer to the previous number
                len = number-numbers-1;
                strncpy(c.phone_numbers[0], numbers, len); // write the first number
                c.phone_numbers[0][len] = '\0';
                for (int j = 1; strcmp(number, "") != 0 && j < PHONE_NUMBER_COUNT; j++) { // check for more numbers
                    number_prev = number;
                    number = strchr(number, FIELD_SEPARATOR)+1;
                    len = number-number_prev-1;
                    strncpy(c.phone_numbers[j], number_prev, len);
                    c.phone_numbers[j][len] = '\0';
                }
            }

            // Parse emails and add to contact
            if(strlen(emails) != 0) { // at least 1 email
                char *email = strchr(emails, FIELD_SEPARATOR)+1;
                char *email_prev = email; // pointer to the previous email
                len = email-emails-1;
                strncpy(c.email_addresses[0], emails, len); // write the first email
                c.email_addresses[0][len] = '\0';
                for (int j = 1; strcmp(email, "") != 0 && j < EMAIL_ID_COUNT; j++) { // check for more emails
                    email_prev = email;
                    email = strchr(email, FIELD_SEPARATOR)+1;
                    len = email-email_prev-1;
                    strncpy(c.email_addresses[j], email_prev, len);
                    c.email_addresses[j][len] = '\0';
                }
            }
            address_book->list[address_book->count] = c; // add contact to address book
        }
       fclose(address_book->fp);
    }
    else
    {
        /* Create a file for adding entries */
        printf("Creating a new file...\n");
        address_book->fp = fopen(DEFAULT_FILE, "w"); // create the file
        fclose(address_book->fp); // close the file

       // free(address_book->list);
    }

    return e_success;
}

/**
 * Function save_file
 * Saves the content of the address book's contacts list from memory into a CSV file.
 * Return success if the file was saved properly.
 * Return failure if the file was not saved properly.
 *
 * @param address_book, pointer to an address book
 * @return Status (enum), whether the file was successfully saved or not.
 */
Status save_file(AddressBook *address_book)
{
    address_book->fp = fopen(DEFAULT_FILE, "w"); // try to open the file

    if (address_book->fp == NULL) { // file wasn't opened successfully
        return e_fail;
    }

    rewind(address_book->fp); // overwrite the file
    for(int i = 0; i < address_book->count; i++) { // loop through list of contacts

        ContactInfo cur = address_book->list[i]; // get the current contact info
        // Write the name of the contact
        fprintf(address_book->fp, "%s%c", cur.name[0], FIELD_DELIMITER);

        // Write the contact's phone numbers
        for(int j = 0; strcmp(cur.phone_numbers[j],"") != 0; j++) {
            fprintf(address_book->fp,"%s%c",cur.phone_numbers[j], FIELD_SEPARATOR);
        }
        fprintf(address_book->fp,"%c",FIELD_DELIMITER);

        // Write the contact's email addresses
        for(int j = 0; strcmp(cur.email_addresses[j],"") != 0; j++) {
            fprintf(address_book->fp,"%s%c",cur.email_addresses[j], FIELD_SEPARATOR);
        }
        fprintf(address_book->fp,"%c",FIELD_DELIMITER);

        // Write the contact's serial number
        fprintf(address_book->fp,"%d", cur.si_no);
        fprintf(address_book->fp,"%c",NEXT_ENTRY);
    }

    fclose(address_book->fp);
    // free(address_book->list);
    return e_success;
}