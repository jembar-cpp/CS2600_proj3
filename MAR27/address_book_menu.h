#ifndef ABK_MENUS_H
#define ABK_MENUS_H

#include "address_book.h"

#define	NONE							0
#define	NUM							1
#define	CHAR							2

#define WINDOW_SIZE					5

void menu_header(const char *str);
Status menu(AddressBook *address_book);
Status save_prompt(AddressBook *address_book);
Status add_contacts(AddressBook *address_book);
Status search_contact(AddressBook *address_book);
Status delete_contact(AddressBook *address_book);
Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode);
int get_option(int type, const char *msg);
void main_menu(void);
Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode);
Status edit_contact(AddressBook* address_book);
#endif