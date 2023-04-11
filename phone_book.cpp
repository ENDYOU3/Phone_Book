#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct phone_book {
    char id[5];
    char name[30];
    char phone[12];
};
struct phone_book contact;

void home();
void insert_data();
void delete_data();
void edit_data();
void search_data_byName();
void sell_all_data();

main() {
    int choice;
    char number[3];
    char temp_enter;
    do {
        home();
        fflush(stdin);
        printf("Please select your function : ");
        scanf("%c", number);
        scanf("%c", &temp_enter);
        choice = atoi(number);
        printf("\n");
        switch (choice) {
            case 1:
                insert_data();
                printf("\n\n");
                break;
            case 2:
                delete_data();
                printf("\n\n");
                break;
            case 3:
                edit_data();
                printf("\n\n");
                break;
            case 4:
                search_data_byName();
                printf("\n\n");
                break;
            case 5:
                sell_all_data();
                printf("\n\n");
                break;
            case 6:
                printf("Exit Program\n\n");
                break;
            default:
                printf("Please select only 1-6!\n\n");
        }
    } while (choice != 6);
}

void home() {
    printf("#################################\n");
    printf("##    Welcome to Phone Book    ##\n");
    printf("#################################\n");
    printf("#        1. Insert data        #\n");
    printf("#        2. Delete data        #\n");
    printf("#        3. Edit data          #\n");
    printf("#        4. Search data        #\n");
    printf("#        5. See all data       #\n");
    printf("#        6. Exit Program       #\n");
    printf("#################################\n\n");
}

void insert_data() {
    FILE *file;
    char answer, temp_Enter;
    if ((file = fopen("contact.txt", "ab")) == NULL) {
        printf("\nCan not add new contact!\n\n");
        exit(1);
    }
    do {
        printf("- - - - - - - - - - - - - - - -\n");
        printf("|         New Contact         |\n");
        printf("- - - - - - - - - - - - - - - -\n");
        //ID >> collect 3 character + '\n' + '\0'
        printf("| ID            :  ");  
        fgets(contact.id, 5, stdin);
        // Name >> //collect 28 character + '\n' + '\0'
        printf("| Name          :  ");  
        fgets(contact.name, 30, stdin);
        // Phone Number >> //collect 10 character + '\n' + '\0'
        printf("| Phone number  :  "); 
        fgets(contact.phone, 12, stdin);
        printf("- - - - - - - - - - - - - - - -\n");
        fwrite(&contact, sizeof(contact), 1, file);
        if (ferror(file)) {
            printf("\nError for add new contact\n\n");
            exit(1);
        }
        else {
            printf("\nComplete add new contact!\n\n");
        }
        printf("Add another contact (Press any key) or Exit to home (Press \'e\') : ");
        answer = getche();
        printf("\n\n");
    } while (answer != 'e');
    fclose(file);
}

void delete_data() {
    FILE *file;
    char record[4];
    int rec = 0, count = 0;
    char answer;
    if ((file = fopen("contact.txt", "rb+")) == NULL) {
        printf("Can not open file for delete contact!\n\n");
        exit(1);
    }
    while (1) {
        fread(&contact, sizeof(contact), 1, file);
        if (ferror(file)) {
            printf("\nError read file for delete data\n\n");
            exit(1);
        }
        if (feof(file)) {
            break;
        }
        ++rec;
        if (strcmp(contact.id, "\0") != 0) {
            ++count;
            printf(" Record Number : %d | ID : %s", rec, contact.id);
            printf("--------------------------------\n");
        }
    }
    printf("\n");
    if (count != 0) {
        printf("Enter your record number for delete : ");
        scanf("%s", record);
        if (atoi(record) < 1 || atoi(record) > rec) {
            printf("\nRecord number not found!\n");
        }
        else {
            do {
                printf("Are you sure for delete this contact? (y/n) : ");
                answer = getche();

                if (answer == 'y') {
                    fseek(file, (atoi(record)-1)*sizeof(contact), SEEK_SET);
                    strcpy(contact.id, "\0");
                    fwrite(&contact, sizeof(contact), 1, file);
                    if (ferror(file)) {
                        printf("Error for delete data\n\n");
                        exit(1);
                    }
                    printf("\nDelete data record %d complete!\n", atoi(record));
                    break;
                }
                else if (answer == 'n') {
                    printf("\n");
                    break;
                }
                else {
                    printf("\nPlease enter \'y\' or \'n\' only!\n");
                }
            } while (answer != 'y' || answer != 'n');
        }
    }
    else {
        printf("All contact already to delete!\n");
    }
    fclose(file);
}

void edit_data() {
    FILE *file;
    char answer, name[30];
    int count = 0;
    if ((file = fopen("contact.txt", "rb+")) == NULL) {
    printf("Can not open file for edit data!\n\n");
    exit(1);
    }
    printf("Please enter contact name for edit : ");
    fgets(name, 30, stdin);
    while (fread(&contact, sizeof(contact), 1, file) == 1) {
        if (ferror(file)) {
            printf("Error for edit data\n");
        }
        if (feof(file)) {
            break;
        }
        if (strcmp(name, contact.name) == 0) {
            ++count;
            printf("\nCurrent Data!\n");
            printf("ID     : %s", contact.id); 
            printf("Name   : %s", contact.name); 
            printf("Phone  : %s", contact.phone);
            do {
                printf("\nDo you want to edit data? (y/n) : ");
                answer = getche();
                if (answer == 'y') {
                    fseek(file, ftell(file)-sizeof(contact), SEEK_SET);
                    printf("\nPlease Enter new data\n\n");
                    printf("ID : %s", contact.id);
                    printf("Name : "); fgets(contact.name, 30, stdin);
                    printf("Phone : "); fgets(contact.phone, 12, stdin);
                    fwrite(&contact, sizeof(contact), 1, file);
                    if (ferror(file)) {
                        printf("Error for edit data\n");
                    }
                    else {
                        printf("Edit data complete!\n\n");
                        fclose(file);
                        break;
                    }
                }
                else if (answer == 'n') {
                    printf("\n");
                    break;
                }
                else {
                    printf("\nPlease enter only \'y\' or \'n\' !!\n");
                }
            } while (answer != 'y' || answer != 'n');
        }
    }
    if (count == 0) {
        printf("No employee data to edit!\n");
    }
    fclose(file);
}

void search_data_byName() {
    FILE *file;
    char name[30];
    int count = 0;
    if ((file = fopen("contact.txt", "rb")) == NULL) {
    printf("Can not open file for search data!\n\n");
    exit(1);
    }
    printf("Enter contact name : ");
    fgets(name, 30, stdin);
    printf("\n");
    while (1) {
        fread(&contact, sizeof(contact), 1, file);
        if (ferror(file)) {
            printf("\nError for search data\n\n");
            exit(1);
        }
        if (feof(file)) {
            break;
        }
        if (strcmp(contact.name, name) == 0) {
            ++count;
            printf("--------------------------------\n");
            printf("|           Found it [%d]!      |\n", count);
            printf("--------------------------------\n");
            printf("|   ID : %s", contact.id);
            printf("|   Name : %s", contact.name);
            printf("|   Phone :%s", contact.phone);
            printf("--------------------------------\n");
        }
    }
    if (count == 0) {
        printf("Sorry, could not be found!\n");
    }
    else {
        printf("Found %d contact\n", count);
    }
    fclose(file);
}

void sell_all_data() {
    FILE *file;
    int i = 0, count = 0;
    if ((file = fopen("contact.txt", "rb+")) == NULL) {
    printf("Can not open file for show all contact!\n\n");
    exit(1);
    }
    while (1) {
        fread(&contact, sizeof(contact), 1, file);
        if (ferror(file)) {
            printf("\nError for see data\n\n");
            exit(1);
        }
        if (feof(file)) {
            break;
        }
        ++i;
        if (strcmp(contact.id, "\0") != 0) {
            count++;
            printf(" Record Number : %d | ID : %s", i, contact.id);
            printf(" Name : %s Phone : %s", contact.name, contact.phone);
            printf("--------------------------------\n");
        }
    }
    if (count == 0) {
        printf("Sorry, no contacts found!\n");
    }
    fclose(file);
}