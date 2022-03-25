#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"


/*
 * void display_subMenu();
 * display sub menu option for Edit Contact
 */
void display_subMenu()
{
    printf("0. Back\n");
    printf("1. Name\n");
    printf("2. Phone No\n");
    printf("3. Email ID\n");
    printf("4. Serial No\n");
    printf("\nPlease select an option: ");
}

int get_option(int type, const char *msg)
{
    printf("%s\n", msg);

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
        EXIT_FAILURE;
    }

    fflush(stdin);
    return option;
}


Status add_contacts(AddressBook *address_book)
{
    /* Add the functionality for adding contacts here */
    return e_success;
}
Status search_contact(AddressBook *address_book)
{
    /* Add the functionality for search contacts here */
    
    return e_success;
}



Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode) {

    return e_success;
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
    } while ( (option != 'N') || (option != 'n'));

    free(address_book->list);

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

        switch (option)
        {
            case e_add_contact:  // 1
                add_contacts(address_book);
                break;
          
            case e_search_contact:
                search_contact(address_book);
                break;
        

            case e_edit_contact: // 3
            {
                printf("Number of contacts = %d\n\n", (address_book->count));
                edit_contact(address_book);
                break;
            
            }
                

            case e_delete_contact:
                delete_contact(address_book);
                break;
           

            case e_list_contacts:
                //display_searchResult(address_book->list, address_book->count);
                break;

            
            case e_save:
                save_file(address_book);
                break;

            case e_exit: // 0
               save_prompt(address_book);
               break;
            
        }
    } while (option != e_exit);

    return e_success;
}


void footer()
{
    printf("\n============================================================================================================================");
    printf("\nPress: [s] = Select, [q] | Cancel: ");
}


void header()
{
    printf("============================================================================================================================");
    printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :\n");
}


/**
 * Status edit_contact (AddressBook *address_book);
 * 
 * 1a. prompt user to choose Edit by :
 * name / phone No / email address
 * press 0 to exit, back to main menu;
 * 1b. Prompt user to enter the target to search, store in char array target
 * 
 * 2. display the entire contact entry list matches with the target
 * 
 * 3a. Define a ContactInfo pointer named listPtr, assign with NULL; 
 * 3b. prompt user enter the serial No of contact list to edit, 
 * 3c. search the corresponding rowfieldIndex for that list, 
 * assign listPtr to the start address of that list: (address_book->list) + rowfieldIndex
 * 
 * 4a. Display all information from that contact list in column format for each field
 *     output emptry space if the corresponding string value is ""
 * 4b. prompt user to select option of editBy: 
 * 4c. go back if user press 0
 * 
 * calling edit_helper function
 * 
 */ 
Status edit_contact (AddressBook *address_book) {

    Status ret;

    int editBy = 0;
    char *msg = "Press: [s] = Select, Press: [q] | Cancel: ";

     // since the max of name / phone no / email are all 32,
     // use one of them as the size of char array
    char target[NAME_LEN];


    do {

        ContactInfo* listPtr = NULL;
        ContactInfo* entryPtr = NULL;
        

        // 1a. 
        menu_header("Search contact to edit by:\n");
        display_subMenu();
        editBy = get_option(NUM, "");

        if (editBy == 0)
        {
            ret = e_back;
        }

        // 1b.
        switch (editBy) {

            // case 0: // e_exit
                // return e_back;

            case 1: {
                printf("Enter the Name: ");
                fgets(target, NAME_LEN, stdin);
                break;
            }


            case 2:
                printf("Enter the Phone Number: ");
                fgets(target, NUMBER_LEN, stdin);
                break;


            case 3:
                printf("Enter the Email ID: ");
                fgets(target, EMAIL_ID_LEN, stdin);
                break;
            
            case e_no_opt:
            default:
                editBy = e_no_opt;
                break;
            
        } // end of switch (editBy)

        if (editBy == e_no_opt) {
            break;
        }
        
        // step 2, 3
        do { 
       
            menu_header("Search result:\n\n");
            header();

// Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode);
            if (search(target, address_book, address_book->count, editBy, msg, e_edit)) {
                return e_success;
            }                                                                               


            printf("\nSelect a Serial Number (S.No) to Edit: ");

            int targetSi = get_option(NUM, "");

            // 3c
            for (int rowfieldIndex = 0; rowfieldIndex < (address_book->count); rowfieldIndex++)
            {
                if ( (((address_book->list) + rowfieldIndex)->si_no) == targetSi )
                {
                    listPtr = (address_book->list) + rowfieldIndex;
                    break; // serial No is unique
                }
            }

            // reprompt user until get a valid serial No
        } while(listPtr == NULL);


        // step 4
        do
        {
            menu_header("\nEdit Contact:");
            printf("\n0. Back");

            // display name (only one name per contact)
            printf("\n1. Name       : %s", listPtr->name[0]);

            // display phone number
            printf("\n2. Phone No 1 : %s", listPtr->phone_numbers[0]); 
            for (int phonefieldIndex = 1; phonefieldIndex < PHONE_NUMBER_COUNT; phonefieldIndex++)
                {
                    // if there is more phone numbers (strcmp returns non-zero)
                    // display Phone No 2 etc.
                    if (strcmp(listPtr->phone_numbers[phonefieldIndex], ""))
                    {
                        printf("\n%13d : %s", phonefieldIndex + 1, listPtr->phone_numbers[phonefieldIndex]);
                    }
                }


            // display email address
            printf("\n3. Email ID 1 : %s", listPtr->email_addresses[0]);
            for (int emailfieldIndex = 1; emailfieldIndex < EMAIL_ID_COUNT; emailfieldIndex++)
            {    
                if (strcmp(listPtr->email_addresses[emailfieldIndex], ""))
                {
                    printf("\n%13d : %s", emailfieldIndex + 1, listPtr->email_addresses[emailfieldIndex]);
                }
                
            }

            printf("\n");
            display_subMenu();
            editBy = get_option(NUM, "");

            ret = edit_helper(listPtr, editBy);


        } while (editBy != 0);


    } while (editBy != 0);


    ret = e_success;
    return ret;
}



/**
 * Status edit_helper(ContactInfo *listPtr, MenuOptions option, Modes mode);
 * 
 * edit_helper function is called after choosing which field to edit
 * 
 * 1a. prompt user to enter the fieldIndex of that field to edit
 * 1b. get the user input, break if out of the max count of that field
 * 
 * 2a. prompt user for the new one
 * 2b. add null termination by the end
 * 
 * 3. copy user input to replace the old one in the same position
 */

Status edit_helper(ContactInfo* listPtr, int editBy)
{
    int fieldIndex = 0;
    int input_len;
    char userInput[NAME_LEN];
  

    switch (editBy) {

        case 0:
            return e_back;

        case 1: {
            // step 1
            printf("Enter name index to be changed [Max %d]: ", NAME_COUNT);

            fgets(userInput, NAME_LEN, stdin);
            fieldIndex = atoi(userInput);

            if (fieldIndex < 1 || fieldIndex > NAME_COUNT) {
                break;
            }   

            // step 2
            printf("Enter Name %d: [Just enter removes the entry]: ", fieldIndex);
            fgets(userInput, NAME_LEN, stdin);

            input_len = strlen(userInput) - 1;

            // adding NULL termination
            if (userInput[input_len] == '\n')
            {    
                userInput[input_len] = '\0';
            }

            // step 3, copy user defined e name to the corresponding list.name
            strcpy(listPtr->name[fieldIndex - 1], userInput);

            break;
        }


        case 2: {

            printf("Enter Phone Number index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
            fgets(userInput, NUMBER_LEN, stdin);

            // convert the integer to string representation
            fieldIndex = atoi(userInput);

            if (fieldIndex < 1 || fieldIndex > PHONE_NUMBER_COUNT)
            {
                break;
            }
            
            printf("Enter Phone Number %d: [Just enter removes the entry]: ", fieldIndex);
         
            fgets(userInput, NUMBER_LEN, stdin);
            input_len = strlen(userInput) - 1;

            if (userInput[input_len] == '\n')
            {    
                userInput[input_len] = '\0';
            }

            strcpy(listPtr->phone_numbers[fieldIndex - 1], userInput);

            break;
        }


        case 3: {
            
            printf("Enter Email ID fieldIndex to be changed [Max %d]: ", EMAIL_ID_COUNT);
            fgets(userInput, EMAIL_ID_LEN, stdin);
            fieldIndex = atoi(userInput);

            if (fieldIndex < 1 || fieldIndex > EMAIL_ID_COUNT)
            {        
                break;
            }
                
            printf("Enter Email ID %d: [Just enter removes the entry]: ", fieldIndex);

            fgets(userInput, EMAIL_ID_LEN, stdin);
            input_len = strlen(userInput) - 1;

            if (userInput[input_len] == '\n')
            { 
                userInput[input_len] = '\0';
            }

            strcpy(listPtr->email_addresses[fieldIndex - 1], userInput);

            break;
        }


        default:
            break;
    }

    return e_success;
}



