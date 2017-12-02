#include "interface.h"


enum selection get_user_input()
{
    int userinput;
    char selection[10] = "";
    int _true = 1;

    while(_true)
    {
        printf("Please enter a selection\n");
        printf("<1> Account Balance\n");
        printf("<2> Withdrawal\n");
        printf("<3> Deposit\n");
        printf("<4> Transfer\n");
        printf("<5> Transaction Listing\n");
        printf("<6> EXIT\n");
        printf("Selection option 1-6 -> ");
        scanf("%s", selection);

        userinput = atoi(selection);

        if(userinput == 1)
        {
            return account_bal;

        }
        if(userinput == 2)
        {
            return withdraw;

        }
        if(userinput == 3)
        {
            return deposit;

        }
        if(userinput == 4)
        {
            return transfer;

        }
        if(userinput == 5)
        {
            return transaction_list;

        }
        if(userinput == 6)
        {
            return signout;

        }
        printf("\nInvalid Selection. Please select option from menu!\n");
    }

}

/*
 * mainmenu():
 * 	- parameters: none
 * 	- Description: this is the main menu display to the user when successfully login.
 * 	  Several options presented to user to choose from
 *
*/

int mainmenu(int client_number)
{
	int exit = 0;

	printf("You are currently logged in as: %s\n",client_uname);
	printf("Client Number - %d", client_number);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

    enum selection userselection;
    userselection = get_user_input();

    switch(userselection)
    {
        case account_bal:
            puts("\nAccount Balance Selected: \n");
            exit = account_Type_Mainmenu(client_number, client_uname, userselection, exit);
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

		case signout:
			puts("GoodBye! \n");
			exit = 0;
			break;

    }

    return exit;
}

/*
 * main():
 * 	-parameters: none
 * 	-Description: main entrance into program
*/

int main(int argc, char *in_con[])
{
	unsigned int client_num = 0;
	/*int portno;
	char hostname;

	if (argc < 3)
	{
	  fprintf(stderr,"usage %s hostname port\n", in_con[0]);
	  exit(0);
	}

	portno = atoi(in_con[2]);
	hostname = in_con[1];

	server_side();
	printf("Line 143, Test!");
	client_side(portno, hostname);*/



    //displaymenu();
    //chooseAccountNumber();
    if(loggin_screen(&client_num))
    {
    	//printf("Line 150 main() Client Number%d",client_num);
    	//printf("\n");
    	while(mainmenu(client_num))
    	;

    }

    return 0;

}
