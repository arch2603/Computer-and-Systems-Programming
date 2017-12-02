#include "interface.h"
#define C_DETAILS "Client_Details.txt"
#define C_ACCOUNTS "Accounts.txt"


struct Accounts{
	unsigned int savings;
	unsigned int creditcard;
	unsigned int loan;
};

struct Client{
	char firstname[20];
	char lastname[20];
	unsigned int client_num;
	struct Accounts acc_type;
};

//size of the structure array
int size;

/*
 *
 *
 *
 *
 *
*/
struct Client* read_File(struct Client details[])
{
		char f_name[20] = "";//client first name
		char l_name[20] = "";//client last name
		char client_num[20] = "";//client number

		char acc[30] = "";//stored the accounts read in from the file
		char *ptracct;
		int account_type, cl_num;//savings, loan, and credit card

		//handler to file for reading in the file
		FILE * cl_details_f;


		cl_details_f = fopen(C_DETAILS, "r");

		//unable to open file because file not in directory
		if(cl_details_f == NULL)
		{
			printf("The file could not be found");
			exit(EXIT_FAILURE);
		}

		int index = 0;
		//reading the first line of the file and discard it, string not relevant
		fscanf(cl_details_f, "%s %s %s %s", f_name,l_name ,client_num, acc);

		while(fscanf(cl_details_f, "%s %s %s %s", f_name,l_name ,client_num, acc) != EOF)
		{

			strcpy(details[index].firstname, f_name);
			strcpy(details[index].lastname, l_name);
			cl_num = atoi(client_num);
			details[index].client_num = cl_num;


			ptracct = strtok(acc,",");

			//parsing the three accounts types savings, creditcard and loan and store to the relevant member with the struct Accounts
			while(ptracct != NULL)
			{
				account_type = atoi(ptracct);

				//check if the number read in is a savings type
				if(account_type % 11 == 0)
				{
					details[index].acc_type.savings = account_type;
					details[index].acc_type.creditcard = 0;
					details[index].acc_type.loan = 0;

				}
				if(account_type % 12 == 0)//check if the number read in is a loan
				{
					details[index].acc_type.loan = account_type;

				}
				else if(account_type % 13 == 0)//check if the number read in is a credit card
				{
					details[index].acc_type.creditcard = account_type;

				}
				ptracct = strtok(NULL, ",");//Delimiter used parse the account types
			}
			index++;
		}

		//closing file
		if(fclose(cl_details_f)== EOF){
			error("Error closing the file");
			exit(EXIT_FAILURE);
		}

		return details;
}

/*
 *
 *
 *
 *
 *
*/
int dummy_File_Reader()
{
	int count = 0;

	char f_name[20] = "";//client first name
	char l_name[20] = "";//client last name
	char client_num[20] = "";//client number
	char acc[30] = "";//stored the accounts read in from the file

	FILE * dummy_fd;//dummy file descriptor use to count the number of clients in the file.

	dummy_fd = fopen(C_DETAILS, "r");


	if(dummy_fd == NULL)
	{
		printf("The file could not be found");
		exit(EXIT_FAILURE);
	}

	fscanf(dummy_fd, "%s %s %s %s", f_name,l_name ,client_num, acc);

	count = 0;

	//A dummy opening and reading of the file in order to count the number of clients in the file
	while(fscanf(dummy_fd, "%s %s %s %s", f_name,l_name ,client_num, acc) != EOF)
		count++;

	return count;
}

/*
 *
 *
 *
 *
 *
*/
double get_Balance(unsigned int account_type)
{
	unsigned int acc_type;
	double opening_bal;
	double closing_bal;


	char acct_type[15] = "";
	char o_balance[15] = "";
	char c_balance[15] = "";


	FILE * c_accounts_f;

	c_accounts_f = fopen(C_ACCOUNTS, "r");

	//unable to open file because file not in directory
	if(c_accounts_f == NULL)
	{
		printf("The file could not be found");
		exit(EXIT_FAILURE);
	}

	fscanf(c_accounts_f, "%s %s %s", acct_type, o_balance,c_balance);

	//reading the file
	while(fscanf(c_accounts_f, "%s %s %s", acct_type, o_balance,c_balance) != EOF)
	{
		acc_type = atoi(acct_type);

		if(account_type == acc_type)
		{
			closing_bal = atof(c_balance);
			break;
		}

	}
	//closing the file
	if(fclose(c_accounts_f)== EOF){
				error("Error closing the file");
				exit(EXIT_FAILURE);
			}
	return closing_bal;
}


/*
 *
 *
 *
 *
 *
*/
unsigned int get_Account_Type(struct Client *ptrcl, unsigned int cl_no)
{
	unsigned int account;

	printf("\n Line 206 in get_Account_Type() size is %d", size);
	while(size > 0)
		{
			//searching for the client number in the struct array
			if(cl_no == ptrcl->client_num)
			{
				account = ptrcl->acc_type.savings;
				break;
			}
			ptrcl++;
			size--;
		}
	return account;//account selected by the user to show balance
}


/*

*/

void get_Frist_Name(struct Client *ptrcl, char f_name[], unsigned int cl_no, int* size)
{
	printf("\n Line 227 in get_First_Name() Test\n");
	printf("\n Line 229 Size = %d, test", *size);

	while((*size) > 0)
			{
				//searching for the client number in the struct array
				if(cl_no == ptrcl->client_num)
				{
					strcpy(f_name, ptrcl->firstname);
					printf("\n Line 233 Printiing first name: %s",f_name);
					break;
				}
				ptrcl++;//increment to the next array element or another Deatails Structure
				(*size)--;//size of struct array
			}



}

void get_Last_Name(struct Client *ptrcl,char l_name[], unsigned int cl_no, int* size)
{
			while((*size) > 0)
				{
					//searching for the client number in the struct array
					if(cl_no == ptrcl->client_num)
					{
						strcpy(l_name, ptrcl->lastname);
						break;
					}
					ptrcl++;
					(*size)--;
				}
}

void print_Balance(unsigned int acc_type, char f_name[],char l_name[], double bal )
{
	printf("\n===============================================================================================\n");
	printf("\n");
	printf("\n");
	printf("Account Name - %s %s", f_name,l_name);
	printf("\n");
	printf("\n");
	printf("Current Balance for your Savings Account %d : $%.2f",acc_type, bal);
	printf("\n");
	printf("\n");
	printf("\n===============================================================================================\n");

}



void display_Balance(struct Client *ptrcl, unsigned int cl_no, int * size)
{
	//return client account type by calling the Get_client_number() i.e. actual client_number requesting balance for his/her account
	unsigned int  account_type;

	double closing_bal;

	char f_name[20]; //Authenticated client First Name
	char l_name[20];//Authenticated client Last Name

	printf("\n Line 290 Size = %d, test", *size);

	//Retrieving account type i.e. savings, loan or credit card in this case savings
	account_type = get_Account_Type(ptrcl,cl_no);

	//Retrieve client First Name
	get_Frist_Name(ptrcl,f_name, cl_no, size);

	//Retrieve client Last Name
	get_Last_Name(ptrcl,l_name, cl_no, size);

	//Getting closing balance
	closing_bal = get_Balance(account_type);
	//Printing closing balance
	print_Balance(account_type, f_name ,l_name, closing_bal);
}

/*
 *
*/
void transaction_Type(enum selection sel, struct Client *ptrcl, unsigned int cl_no, int* size)
{
	 switch(sel)
	    {
	        case account_bal:
	        	display_Balance(ptrcl, cl_no, size);
	            break;

	        case withdraw:
	            puts("Withdraw Balance Selected: \n");
	            break;

	        case deposit:
				puts("Deposit: \n");
				break;

			case transfer:
				puts("Transfer: \n");
				break;

			case transaction_list:
				puts("Transaction List: \n");
				break;
	    }
}

/*
 *
*/
void Savings(unsigned int client_num, char client_name[], enum selection sel){

	int numberofclients;//actual count of clients on the file returned by dummy reading the file

	numberofclients = dummy_File_Reader();//counting the number of people or list of people by mock reading the file

	struct Client details[numberofclients];
	struct Client *ptrcl;

	size = sizeof(details)/sizeof(details[0]);//size of list needed
	printf("\n");
	printf("Line 347 Size in Savings() = %d", size);
	printf("\n");

	ptrcl = read_File(details);//invoking the Read_file() to read and store the contents of the file

	transaction_Type(sel, ptrcl, client_num, &size);
}


