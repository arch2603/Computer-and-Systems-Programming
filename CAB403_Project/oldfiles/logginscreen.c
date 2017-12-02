#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define IN_FILE "Authentication.txt"


char client_uname[20] ="";

struct authentication{
    unsigned int pinnumber;
	unsigned int client_no;
    char username[20];
    struct authentication *next;

};


/*
 * Name: insert_back
 * Parameters:
 * 			struct authentication *head
 * 			unsigned int cl_no
 * 			unsigned int pin_no
 * 			char uname[]
 *Description:
 *			Take in the head of the list and members of the list and inserted according to the order which is read from
 *
 *
 * */
struct authentication * insert_back(struct authentication * head, unsigned int cl_no, unsigned int pin_no, char uname[])
{
	struct authentication  *temp1;//temporary pointer to the list head
	struct authentication *temp2;//temporary pointer used a dummy to iterate the list

	//check if the pointer to the list points to nothing otherwise it is already pointing to a list
	if(head == NULL){
		temp1 = (struct authentication*)malloc(sizeof(struct authentication));
		temp1->client_no = cl_no;
		temp1->pinnumber = pin_no;
		strcpy(temp1->username, uname);
		head = temp1;
		return head;
	}
	//building the next node in the list
	temp1 = (struct authentication*)malloc(sizeof(struct authentication));
	temp1->client_no = cl_no;
	temp1->pinnumber = pin_no;
	strcpy(temp1->username,uname);

	temp2 = head;

	//traversing the list until the next pointer is not pointing to a list
	while(temp2->next != NULL){
		temp2 = temp2->next;
	}
	//attaching or inserting a node to the existing list
	temp2->next = temp1;

	return head;
}



struct authentication * openfile()
{
	//authentication list read from file
	char username[20] = "";
	char pin_num[20] = "";
	char client_no[20] = "";

	unsigned int clientno = 0;//store converted string read from file
	unsigned int pinnumber = 0;//store converted string read from file

	//head or entry into the list
	struct authentication * head = NULL;

	//handler to file for reading in the file
	FILE * filein;

	filein = fopen(IN_FILE, "r");

	if(filein == NULL)
	{
		printf("The file could not be found");
		exit(EXIT_FAILURE);
	}

	//reading the first line of the file and discard it, string not relevant
	fscanf(filein, "%s %s %s", username,pin_num,client_no);

	//open authentication list file and read in the file
	while(fscanf(filein, "%s %s %s",username,pin_num,client_no) != EOF)
	{
		//store contents of the file in linked list
		pinnumber = atoi(pin_num);
		clientno = atoi(client_no);
		head = insert_back(head, clientno, pinnumber, username);

	}

	if(fclose(filein)== EOF){
		error("Error closing the file");
		exit(EXIT_FAILURE);
	}

	return head;

}


int loggin_screen(unsigned int * cl_num)
{
	//boolean value check for user valid username and pinnumber
	int valid = 0;

	//user client number and pin number
	char user_name[20] = "";
	char password[20] = "";
    unsigned int p_num = 0;
    int loggin_count = 3;//count the number of user attempted log in, max log in attempt is 3


    struct authentication * head = NULL;
    struct authentication * temp = NULL;

    head = openfile();

	printf("=======================================================\n");
	printf("\n");
	printf("\n");
	printf("Welcome to the Online ATM System\n");
	printf("\n");
	printf("\n");
	printf("=======================================================\n");


	printf("You are required to logon with your registered Username and PIN\n");

	//record the number of attempts by the user, if attempts exceed 3, logout user from system
	while(loggin_count > 0)
	{

		printf("Please enter username--> ");
		scanf("%s",user_name);
		printf("\nPlease enter your password-->");
		scanf("%s",password);
		p_num = atoi(password);
			//authenticate username
			//compare the user input username and password to the stored username and password
			temp = head;

			while(temp != NULL)
			{
				//authenticating clients credentials against stored credentials
				if(strcmp(user_name,temp->username)== 0 && p_num == temp->pinnumber)
				{
					*cl_num = temp->client_no;//storing the client number in global var, for use in main menu
					//printf("Line 160 logginscreen() Client Number%d",*cl_num);
					strcpy(client_uname, temp->username);//copying the user name of client to global var for use in main menu
					valid = 1;
					break;
				}
				temp = temp->next;//traversing the linked list
			}

		//if user and password fails prompt the use to enter again until count expires
		if(!valid){
			printf("\nInvalid combination of username and password!\n");

		}

		//if username and password authenticate go to main menu
		if(valid){

			break;
		}

		//counting the number of loggin attempts by the user, 3 is maximum
		loggin_count--;

	}
	return valid;
}


