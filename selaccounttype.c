#include <ctype.h>
#include "interface.h"

#define C_DETAILS "Client_Details.txt"


int account_Type_Mainmenu(unsigned int client_num, char client_uname[], enum selection sel, int _exit)
{
	char selection[5] = "";
	char f_name[20] = "";//client first name
	char l_name[20] = "";//client last name
	char cl_num[20] = "";//client number

	char acc[30] = "";//stored the accounts read in from the file
	char *ptracct;

	int option;
	int account_type;
	//..................different account types.............................//
	unsigned int savings = 0; unsigned int cr_card = 0; unsigned int loan = 0;
	//authenticated client number
	unsigned int client_no;

	//handler to file for reading in the file
	FILE * cl_details_f;


	cl_details_f = fopen(C_DETAILS, "r");

	//unable to open file because file not in directory
	if(cl_details_f == NULL)
	{
		printf("The file could not be found");
		exit(EXIT_FAILURE);
	}

	fscanf(cl_details_f, "%s %s %s %s", f_name,l_name ,cl_num, acc);

	do{
		printf("\nSelect Account Type\n");

		//reading the client details file
		while(fscanf(cl_details_f, "%s %s %s %s", f_name,l_name ,cl_num, acc) != EOF)
		{
			client_no = atoi(cl_num);
			if(client_num == client_no)
			{
				ptracct = strtok(acc,",");

				//parsing the three accounts types savings, creditcard and loan and store to the relevant member with the struct Accounts
				while(ptracct != NULL)
				{
					account_type = atoi(ptracct);

					if(account_type % 11 == 0)
					{
						savings = account_type;

					}
					if(account_type % 12 == 0)//check if the number read in is a loan
					{
						loan = account_type;

					}
					else if(account_type % 13 == 0)//check if the number read in is a credit card
					{
						cr_card = account_type;

					}

					ptracct = strtok(NULL, ",");//Delimiter used to parse the account types
				}

			}
		}
		/*
		 * The following code display only the accounts the client has with the bank. It will not
		 * display any other account if the user or client does not have such account
		 * */
		if(savings)
		{
			printf("\n1. Savings Account\n");

		}
		if(loan)
		{
			printf("\n2. Loan Account\n");

		}
		if(cr_card)
		{
			printf("\n3. Credit Card\n");

		}

		printf("\nEnter your selection (E or e to exit) - ");
		scanf("%s",selection);

		//converting the user option to an integer
		option = atoi(selection);

		//coverting the uppercase letter to a lower case letter
		if(strcmp(selection, "E") == 0){
			selection[0] = selection[0] + 32;
		}
		if(option == 1){
			Savings(client_num, client_uname, sel);
		}
		if(option == 2){
			;
		}
		if(option == 3){

		}


	}while(strcmp(selection, "e") != 0);

	//closing file
	if(fclose(cl_details_f)== EOF){
		error("Error closing the file");
		exit(EXIT_FAILURE);
	}

	_exit = 1;
	return _exit;
}
