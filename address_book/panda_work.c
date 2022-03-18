#include <stdio.h>
#include <string.h> 
#include "address_book.h"

Status delete_contact(AddressBook *address_book);
Status delete_list(AddressBook *pc, int pos);
void subMenu();
int compareByName(AddressBook* pc, const char* name);
int compareByNum(const AddressBook* pc, const int si);

// 
/**
 * 1. check if address book is empty
 * 2. search by 
 * name
 * 
 * 3. delete the whole list of entry
 * 4. decrement the counter by 1
 */ 
Status delete_contact(AddressBook *address_book) {

	 if (address_book->count == 0)
    {
        printf("The address book is empty and cannot be deleted\n");
        return e_back;
    }

    printf("Please enter the option that you want to delete by: ");
    subMenu();
    int option;
    scanf("%d", &option);
    int pos;

    switch (option) {
        case 0:
        {
            char name[NAME_LEN] = { 0 };
            printf("Please enter the name of the person you want to find:");
            scanf("%s", name);
            pos = compareByName(address_book, name);
            delete_list(address_book, pos);
            break;
        }

        case 3: {
            int value= 0;
            printf("Please enter a si no to delete: ");
            scanf("%d", &value);
            pos = compareByNum(address_book, value);
            delete_list(address_book, pos);
            break;
        }

        default:
            break;
    }

	return e_success;
}

Status delete_list(AddressBook *pc, int pos)
{
    if (pos == -1)
    {
        printf("The specified contact does not exist\n");
        return e_no_match;
    }
    else
    {
        //delete
        int j = 0;
        for (j = pos; j < pc->count-1; j++)
        {
            pc->list[j] = pc->list[j + 1];
        }
        (pc->count)--;
        printf("Delete succeeded\n");
        return e_success;
    }
}


void subMenu() {
    printf("Please enter the number to choose:\n"
           "0. Name\n"
           "1. Phone number\n"
           "2. Email address\n"
           "3. Si Number\n");
}


int compareByName(AddressBook* pc, const char* name)
{
    int i = 0;
    for (i = 0; i < pc->count; i++)
    {
        // only one name per contact list at index zero
        if (strcmp((pc->list[i]).name[0], name) == 0)
        {
            return i;
        }
    }
    return -1;
}
int compareByNum(const AddressBook* pc, const int si) {

    for(int i = 0; i < pc->count; ++i) {
        if (si == (pc->list)->si_no) {
            return i;
        }
    }
    return -1;
}




