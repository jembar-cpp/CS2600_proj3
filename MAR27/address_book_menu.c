#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"


int get_option(int type, const char *msg)
{
    // display the prompt
    printf("%s", msg);

    int option = 0;

    if (type == NONE) {
        getc(stdin);
    }
    else if (type == CHAR) {
        option = getc(stdin);
    }

        // convert char to integer, assume user enter single digit
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

// @author: Serly Teymoorian
Status add_contacts(AddressBook *address_book)
{
    ContactInfo* contactInfo = address_book->list;
    char response[50];
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
            scanf("%s", ((address_book->count) + contactInfo)->name[0]);
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
    return e_success;
}

// @author: Serly Teymoorian
Status delete_contact(AddressBook *address_book)
{
    ContactInfo* contactInfo = address_book->list;

    char response[50];
    char searchword[50];
    char searchBy[50];
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
            printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+ptr)->si_no, (i+ptr)->name[0], (i+ptr)->phone_numbers[0], (i+ptr)->email_addresses[0]);
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
                    if ( search(searchword, address_book, address_book->count, 4, "Serial", e_search) == e_success )
                    {
                        while (strcmp(response, "0") != 0)
                        {
                            menu_header("Edit Contact: ");
                            printf("\n0. Back");
                            printf("\n1. Name        : %s", ((i)+contactInfo)->name[0]);
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

    return e_success;
}


// @author: Jeremy
Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{

    int results[50]; // array of list indices for search matches
    for(int i = 0; i < 50; i++) {
        results[i] = -1; // -1: no match
    }

    int rCount = 0;
    int sn;

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
            sn = atoi(str);

            for(int i = 0; i < loop_count; i++) {
                if(sn == (address_book->list[i].si_no)) { // successful match
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


// @author: Jeremy
Status search_contact(AddressBook *address_book) {
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
            fgets(input, 500, stdin);
            if (input[strlen(input)-1] == '\n') {
                input[strlen(input)-1] = '\0';
            }
            field = 4;
            break;
    }

    if(!back) {
        Status result = search(input, address_book, address_book->count, field, "Search result:\n", e_search);
    }

    return e_success;
}



// when user enter N, do nothing but will exist the loop
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

        // continue the while loop if user neither enter Y nor enter N
    } while (option != 'N');


    return e_success;
}


void menu_header(const char *str)
{
    //  fflush(stdout);

    system("clear");

    printf("#######  Address Book  #######\n");
    if (str !=  NULL)
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

// I modified a bit with numerical value
Status menu(AddressBook *address_book)
{
    ContactInfo backup;
    Status ret;
    int option;

    do
    {
        main_menu();

        option = get_option(NUM, "");

        // what if it's an empty file?
//        if ((address_book-> count == 0) && (option != e_add_contact))
//        {
//            get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");
//
//            continue;
//        }

        switch (option) // NOLINT(hicpp-multiway-paths-covered)
        {
            case 1:
                add_contacts(address_book);
                break;

            case 2:
                search_contact(address_book);
                break;


            case 3:
            {
                printf("Number of contacts = %d\n\n", (address_book->count));
                edit_contact(address_book);
                break;
            }


            case 4:
                delete_contact(address_book);
                break;


            case 5:
                list_contacts(address_book, "", (void*)'\0', "", e_list);
                break;


            case 6:
                save_file(address_book);
                break;

            case 0:
                save_prompt(address_book);
                break;

            default: // invalid input, prompt again
                break;
        }

    } while (option != 0);

    return e_success;
}

// @author: Jeremy
Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
    ContactInfo* contactInfo = address_book->list;
    if (mode == e_list)
    {
        menu_header("Search Result:\n");
        printf("==============================================================================================================================\n");
        printf("   : S.No : Name                              : Phone No                          : Email ID                                  :");
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
        printf("\n1. Name        : %s", ((address_book->count)+contactInfo)->name[0]);
        printf("\n2. Phone No 1  : %s",((address_book->count)+contactInfo)->phone_numbers[0]);
        printf("\n3. Email ID 1  : %s", ((address_book->count)+contactInfo)->email_addresses[0]);
    }



    return e_success;
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
    char ch;
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
        int sNum = get_option(NUM, "Select a Serial Number (S.No) to Edit: ");

        // 3c
        ContactInfo* listPtr  = address_book->list;

        for (int rowfieldIndex = 0; rowfieldIndex < (address_book->count); rowfieldIndex++)
        {
            if ( (((address_book->list) + rowfieldIndex)->si_no) == sNum )
            {
                listPtr = (address_book->list) + rowfieldIndex;
                break; 
            }
        }

        // step 4
        do {
            menu_header("Edit Contact");
            printf("\n0. Back\n");

            // display name (only one name per contact)
            printf("1. Name       : %-s\n", listPtr->name[0]);

            // display phone number
            printf("2. Phone No 1 : %-s\n", listPtr->phone_numbers[0]);

            for (int phonefieldIndex = 1; phonefieldIndex < PHONE_NUMBER_COUNT; phonefieldIndex++) {

                // if there is more one phone numbers
                // if condition compares if the max length of a phone number are empty string with NUL termination
                // display        2 ...
                //                3 ...etc.
                if ( strcmp(listPtr->phone_numbers[phonefieldIndex], "") != 0) {
                    printf("\n%13d : %-s", phonefieldIndex + 1, listPtr->phone_numbers[phonefieldIndex]);
                }
            }


            // display email address
            printf("\n3. Email ID 1 : %-s\n", listPtr->email_addresses[0]);
            for (int emailfieldIndex = 1; emailfieldIndex < EMAIL_ID_COUNT; emailfieldIndex++) {

                if ( strcmp(listPtr->email_addresses[emailfieldIndex], "") != 0) {
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
                    strcpy(listPtr->name[fieldIndex - 1], target);
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

                    strcpy(listPtr->phone_numbers[fieldIndex - 1], target);
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

                    strcpy(listPtr->email_addresses[fieldIndex - 1], target); save_prompt(address_book);
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


