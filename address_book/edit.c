#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
/**
 * @author: Suhuan Pan
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
        printf("Passed invalid int type to get_option function\n");
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
    char select_cancel[3];
    printf("\nPress: [s] = Select, [q] | Cancel: ");
    scanf("%s", select_cancel);
}

void searchResult_header()
{
    printf("============================================================================================================================");
    printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :\n");
}


Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
    int option;
    Status ret;
    do
    {
        menu_header("Search result:\n\n");
        searchResult_header();

        switch (field)
        {
            case 1:
            {
                for (int position = 0; position < loop_count; position++) {

                    for (int name = 0; name < NAME_COUNT; name++) {

                        if (strcmp(((address_book->list) + position)->name[name], str) == 0) {

                            ret = e_success; //if match is found, return e_success.

                            // print main information
                            printf(": %-4d : %-32s : %-32s : %-32s :\n",
                                   ((address_book->list) + position)->si_no,
                                   ((address_book->list) + position)->name[0],
                                   ((address_book->list) + position)->phone_numbers[0],
                                   ((address_book->list) + position)->email_addresses[0]);

                            // print additional information
                            display1(address_book, position);


                            break;
                        } else {
                            ret = e_no_match; //if no match if found, return e_fail.
                            break;
                        }
                    }
                }
                break;
            }

            case 2: // search by phone number
            {
                for (int person = 0; person < loop_count; person++) {
                    for (int phone_number = 0; phone_number < PHONE_NUMBER_COUNT; phone_number++) {


                        if (strstr(((address_book->list) + person)->phone_numbers[phone_number], str) != NULL) {
                            ret = e_success; //if match is found, return e_success.

                            display_editBy(address_book, person);

                            printf("=================================================================================================================\n");
                            break;
                        } else {
                            ret = e_no_match; //if no match if found, return e_fail.
                            break;
                        }
                    }
                }
                break;
            }

            case 3: // search by email
            {
                for (int position = 0; position < loop_count; position++) {
                    for (int email_id = 0; email_id < EMAIL_ID_COUNT; email_id++) {


                        if (strstr(((address_book->list) + position)->email_addresses[email_id], str) != NULL) {
                            ret = e_success; //if match is found, return e_success.

                            display2(address_book, position);
                            printf("=================================================================================================================\n");
                            break;
                        } else {
                            ret = e_no_match; //if no match if found, return e_fail.
                            break;
                        }
                    }
                }

                break;
            }

            case 4: // search si_no
            {
                for (int person = 0; person < loop_count; person++) {
                    //checks if there is a name in name[] that matches the name that it is searching for
                    if (((address_book->list) + person)->si_no == atoi(str)) {
                        ret = e_success; //if match is found, return e_success.
                        // print main information
                        printf(": %-4d : %-32s : %-32s : %-32s :\n", ((address_book->list) + person)->si_no, ((address_book->list) + person)->name[0], ((address_book->list) + person)->phone_numbers[0], ((address_book->list) + person)->email_addresses[0]);
                        // print additional information
                        for (int person_name = 1; person_name < NAME_COUNT; person_name++) {
                            char name_buffer[NAME_LEN];
                            if (person_name < NAME_COUNT && (((address_book->list) + person)->name[person_name]) != NULL)
                                strcpy(name_buffer, ((address_book->list) + person)->name[person_name]);
                            else
                                strcpy(name_buffer, " ");

                            char phone_buffer[NUMBER_LEN];
                            if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->phone_numbers[person_name]) != NULL)
                                strcpy(phone_buffer, ((address_book->list) + person)->phone_numbers[person_name]);
                            else
                                strcpy(phone_buffer, " ");

                            char email_buffer[EMAIL_ID_LEN];
                            if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->email_addresses[person_name]) != NULL)
                                strcpy(email_buffer, ((address_book->list) + person)->email_addresses[person_name]);
                            else
                                strcpy(email_buffer, " ");
                            printf(": %-4s : %-32s : %-32s : %-32s :", " ", name_buffer, phone_buffer, email_buffer);
                            printf("\n");
                        }
                        printf("=================================================================================================================\n");
                        break;
                    }
                }
                ret = e_no_match; //if no match if found, return e_fail.
                break;
            }

            default:
                break;
        }

        option = get_option(CHAR, msg);
        if (option == 'q')
        {
            ret = e_back;
        }

    } while (!(option == 'q' || ((mode == e_edit || mode == e_delete) && option == 's')));
    return ret;
}

void display1(const AddressBook *address_book, int person)
{
    for (int person_name = 1; person_name < NAME_COUNT; person_name++) {
        char name_buffer[NAME_LEN];
        if (person_name < NAME_COUNT && (((address_book->list) + person)->name[person_name]) != NULL)
            strcpy(name_buffer, ((address_book->list) + person)->name[person_name]);
        else
            strcpy(name_buffer, " ");

        char phone_buffer[NUMBER_LEN];
        if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->phone_numbers[person_name]) != NULL)
            strcpy(phone_buffer, ((address_book->list) + person)->phone_numbers[person_name]);
        else
            strcpy(phone_buffer, " ");

        char email_buffer[EMAIL_ID_LEN];
        if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->email_addresses[person_name]) != NULL)
            strcpy(email_buffer, ((address_book->list) + person)->email_addresses[person_name]);
        else
            strcpy(email_buffer, " ");

        printf(": %-4s : %-32s : %-32s : %-32s :", " ", name_buffer, phone_buffer, email_buffer);
        printf("\n");
    }
}

void display2(const AddressBook *address_book, int position)
{
    printf(": %-4d : %-32s : %-32s : %-32s :\n", ((address_book->list) + position)->si_no, ((address_book->list) + position)->name[0], ((address_book->list) + position)->phone_numbers[0], ((address_book->list) + position)->email_addresses[0]);
    // print additional information
    for (int person_name = 1; person_name < EMAIL_ID_COUNT; person_name++) {
        char name_buffer[NAME_LEN];
        if (person_name < NAME_COUNT && (((address_book->list) + position)->name[person_name]) != NULL)
            strcpy(name_buffer, ((address_book->list) + position)->name[person_name]);
        else
            strcpy(name_buffer, " ");

        char phone_buffer[NUMBER_LEN];
        if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + position)->phone_numbers[person_name]) != NULL)
            strcpy(phone_buffer, ((address_book->list) + position)->phone_numbers[person_name]);
        else
            strcpy(phone_buffer, " ");

        char email_buffer[EMAIL_ID_LEN];
        if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + position)->email_addresses[person_name]) != NULL)
            strcpy(email_buffer, ((address_book->list) + position)->email_addresses[person_name]);
        else
            strcpy(email_buffer, " ");
        printf(": %-4s : %-32s : %-32s : %-32s :", " ", name_buffer, phone_buffer, email_buffer);
        printf("\n");
    }
}

void display_editBy(const AddressBook *address_book, int person)
{
    printf(": %-4d : %-32s : %-32s : %-32s :\n", ((address_book->list) + person)->si_no, ((address_book->list) + person)->name[0], ((address_book->list) + person)->phone_numbers[0], ((address_book->list) + person)->email_addresses[0]);
    // print additional information

    for (int person_name = 1; person_name < PHONE_NUMBER_COUNT; person_name++) {
        char name_buffer[NAME_LEN];
        if (person_name < NAME_COUNT && (((address_book->list) + person)->name[person_name]) != NULL)
            strcpy(name_buffer, ((address_book->list) + person)->name[person_name]);
        else
            strcpy(name_buffer, " ");

        char phone_buffer[NUMBER_LEN];
        if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->phone_numbers[person_name]) != NULL)
            strcpy(phone_buffer, ((address_book->list) + person)->phone_numbers[person_name]);
        else
            strcpy(phone_buffer, " ");

        char email_buffer[EMAIL_ID_LEN];
        if (person_name < PHONE_NUMBER_COUNT && (((address_book->list) + person)->email_addresses[person_name]) != NULL)
            strcpy(email_buffer, ((address_book->list) + person)->email_addresses[person_name]);
        else
            strcpy(email_buffer, " ");
        printf(": %-4s : %-32s : %-32s : %-32s :", " ", name_buffer, phone_buffer, email_buffer);
        printf("\n");
    }
}


Status edit_contact (AddressBook *address_book) {

    // since the max of name / phone no / email are all 32,
    // use one of them as the size of char array
    char new[NAME_LEN + 1];

    MenuOptions option;
    char *msg = "Press: [s] = Select, Press: [q] | Cancel: ";

    do {
        ContactInfo* listPtr = NULL;

        menu_header("Search contact to edit by:\n");
        display_subMenu();
        option = get_option(NUM, "");

        if (option == e_exit)
        {
            return e_back;
        }

        switch (option) {

            case 1: {
                printf("Enter the Name: ");
                fgets(new, NAME_LEN, stdin);
                break;
            }


            case 2:
                printf("Enter the Phone Number: ");
                fgets(new, NUMBER_LEN, stdin);
                break;


            case 3:
                printf("Enter the Email ID: ");
                fgets(new, EMAIL_ID_LEN, stdin);
                break;


            case e_no_opt:
            default:
                option = e_no_opt;
                break;
        }

        // Select a Serial Number to edit
        if (option != e_no_opt)
        {
            do
            {
                if (search(new, address_book, address_book->count, option, msg, e_edit) == e_back)
                {
                    return e_success;
                }

                printf("\nSelect a Serial Number (S.No) to Edit: ");
                listPtr = NULL;

                int targetSi = get_option(NUM, "");

                for (int position = 0; position < address_book->count; position++)
                {
                    if (((address_book->list) + position)->si_no == targetSi)
                    {
                        listPtr = ((address_book->list) + position);
                    }
                }

            } while (listPtr == NULL);

            do
            {
                menu_header("\nEdit Contact:");
                printf("\n0. Back");
                printf("\n1. Name       : %s", listPtr->name[0]);
                for (int name = 1; name < NAME_COUNT; name++)
                {
                    if (strcmp(listPtr->name[name], ""))
                    {
                        printf("\n%13d : %s", name + 1, listPtr->name[name]);
                    }
                }

                printf("\n2. Phone No 1 : %s", listPtr->phone_numbers[0]); //prints the most recent entry from add contacts

                for (int phone = 1; phone < PHONE_NUMBER_COUNT; phone++)
                {
                    if (strcmp(listPtr->phone_numbers[phone], ""))
                    {
                        printf("\n%13d : %s", phone + 1, listPtr->phone_numbers[phone]);
                    }
                }
                printf("\n3. Email ID 1 : %s", listPtr->email_addresses[0]);
                for (int email = 1; email < EMAIL_ID_COUNT; email++)
                {
                    if (strcmp(listPtr->email_addresses[email], ""))
                    {
                        printf("\n%13d : %s", email + 1, listPtr->email_addresses[email]);
                    }
                }


                printf("\n");
                printf("Please select an option: ");
                option = get_option(NUM, "");
                edit_helper(listPtr, option, e_edit);


           } while (option != 0);
        }


    } while (option != 0);


    return e_success;
}



/**
 * edit_helper function is called after display an entry to be edited,
 * 1. choose what to edit: name / phone / email
 * 2. choose the index of field to edit
 * 3. modified the content
 */
Status edit_helper(ContactInfo *listPtr, MenuOptions option, Modes mode)
{
    int index = 0;
    int string_len;
    char userInput[NAME_LEN];

    switch (option) {

        case 1: {

                printf("Enter Name index to be changed [Max %d]: ", NAME_COUNT);

                fgets(userInput, NAME_LEN, stdin);
                index = atoi(userInput);

                if (index < 1 || index > NAME_COUNT)
                    break;

                printf("Enter Name %d: [Just enter removes the entry]: ", index);

            fgets(userInput, NAME_LEN, stdin);

            // copy user defined new name to the corresponding list.name
            strcpy(listPtr->name[index - 1], userInput);

            break;
        }


        case 2: {

            if (mode == e_edit) {

                printf("Enter Phone Number index to be changed [Max %d]: ", PHONE_NUMBER_COUNT);
                fgets(userInput, NUMBER_LEN, stdin);

                // convert the integer to string representation
                index = atoi(userInput);
                if (index < 1 || index > PHONE_NUMBER_COUNT)
                    break;
                printf("Enter Phone Number %d: [Just enter removes the entry]: ", index);
            }

            fgets(userInput, NUMBER_LEN, stdin);
            string_len = strlen(userInput) - 1;

            if (userInput[string_len] == '\n')
                userInput[string_len] = '\0';

            strcpy(listPtr->phone_numbers[index - 1], userInput);

            break;
        }


        case 3: {

            if (mode == e_edit) {
                printf("Enter Email ID index to be changed [Max %d]: ", EMAIL_ID_COUNT);
                fgets(userInput, EMAIL_ID_LEN, stdin);
                index = atoi(userInput);
                if (index < 1 || index > EMAIL_ID_COUNT)
                    break;
                printf("Enter Email ID %d: [Just enter removes the entry]: ", index);
            }

            fgets(userInput, EMAIL_ID_LEN, stdin);
            string_len = strlen(userInput) - 1;
            if (userInput[string_len] == '\n')
                userInput[string_len] = '\0';
            strcpy(listPtr->email_addresses[index - 1], userInput);

            break;
        }

        default:
            break;
    }

    return e_success;
}
