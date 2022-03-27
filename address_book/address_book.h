#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#define DEFAULT_FILE				"address_book.csv"

/* Length of a contact name  */
#define NAME_LEN					32
/* Length of a phone number */
#define NUMBER_LEN					32
/* Length of an email address */
#define EMAIL_ID_LEN				32

/* Maximum number of Names per contact, Just for easy design */
#define NAME_COUNT					1
/* Maximum number of phones per contact */
#define PHONE_NUMBER_COUNT			5
/* Maximum number of email addresses per contact */
#define EMAIL_ID_COUNT				5

#define FIELD_DELIMITER				','
#define FIELD_SEPARATOR				' '
#define NEXT_ENTRY					'\n'

typedef int bool_t;

typedef enum 
{
	e_add,
	e_search,
	e_edit,
	e_delete,
	e_list,
} Modes;

typedef enum 
{
	e_first_opt = 48,
	e_second_opt = 49,
	e_third_opt = 50,
	e_fourth_opt = 51,
	e_fifth_opt = 52,
	e_sixth_opt = 53,
	e_no_opt = '\n' -'0',
} MenuOptions;

typedef enum
{
	e_fail = -10,
	e_back,
	e_success,
	e_no_match,
	e_new_line,
} Status;

typedef enum 
{
	e_exit = 48,
	e_add_contact = 49,
	e_search_contact = 50,
	e_edit_contact = 51,
	e_delete_contact = 52,
	e_list_contacts = 53,
	e_save = 54
} MenuFeatures;

typedef struct
{
	char name[NAME_COUNT][NAME_LEN];
	char phone_numbers[PHONE_NUMBER_COUNT][NUMBER_LEN];
	char email_addresses[EMAIL_ID_COUNT][EMAIL_ID_LEN];
	int si_no;
} ContactInfo;

typedef struct
{
	FILE *fp;
	ContactInfo *list;
	int count;	
} AddressBook;

#endif