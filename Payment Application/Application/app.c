#include "..\Card\card.h"
#include "..\Terminal\terminal.h"
#include "..\Server\server.h"
#include <stdio.h>
#include <string.h>


/*-----------Globle Variables----------*/

int c;
ST_cardData_t card1;
ST_terminalData_t terminal;
EN_cardError_t rescard;  //CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
EN_terminalError_t resterminal;  //TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
EN_serverError_t resserver;  //SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
ST_accountsDB_t accountsDB;
ST_transaction_t transaction;
EN_accountState_t accountstate;
EN_transState_t transState;
EN_serverError_t serverError;

/*-----------Function's Prototypes----------*/

void printenumcard(int);
void printenumterminal(int);
void printenumserver(int);
void printenumstate(int);

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);  
void getCardPANTest(void);

void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void setMaxAmountTest(void);
void isBelowMaxAmountTest(void);

void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
//void saveTransactionTest(void);

/*-----------------------Main Program----------------------*/


void appStart(void)
{
	int i = 1, continue_tran=1;
	
    do //Get card holder name
    {
	    printf("Card Holder Name: ");
	    gets(card1.cardHolderName);
	    rescard = getCardHolderName(&card1);
	    if (rescard == 1)
	    {
			printenumcard(rescard);
		    printf("\n");
	    }
		//else //TEST
		//{
			//printenumcard(rescard);
			//printf("\n");
		//}
	    printf("\n");
    } while (rescard == 1);
	
	
	do //Get card expiration date
	{
		printf("Card Expiry Date \"MM/YY\": ");
		gets(card1.cardExpirationDate);
		rescard = getCardExpiryDate(&card1);
		if (rescard == 2)
		{
			printenumcard(rescard);
			printf("\n");
		}
		//else //TEST
		//{
			//printenumcard(rescard);
			//printf("\n");
		//}
		printf("\n");
	} while (rescard == 2);
	
	
	do //Get card PAN
	{
		printf("Card PAN: ");
		gets(card1.primaryAccountNumber);
		rescard = getCardPAN(&card1);
		if (rescard == 3)
		{
			printenumcard(rescard);
			printf("\n");
		}
		//else //TEST
		//{
			//printenumcard(rescard);
			//printf("\n");
		//}
		printf("\n");
	} while (rescard == 3);
	
	
	do //Get transaction date
	{
		printf("Transaction Date \"DD/MM/YYYY\": ");
		gets(terminal.transactionDate);
		resterminal = getTransactionDate(&terminal);
		if (resterminal == 1)
		{
			printenumterminal(resterminal);
			printf("\n");
		}
		//else //TEST
		//{
		//	printenumterminal(resterminal);
		//	printf("\n");
		//}
		printf("\n");
	} while (resterminal == 1);
	
	
	resterminal = isCardExpired(&card1, &terminal);
	if (resterminal == 2)
	{
		printf("Declined Expired Card");
		printf("\n\n");
		exit(0);
	}
	//else //TEST
	//{
		//printenumterminal(resterminal);
	//	printf("\n");
	//}
	
	
	do //Get transaction Amount
	{
		printf("Transaction Amount: ");
		scanf_s("%f", &terminal.transAmount);
		resterminal = getTransactionAmount(&terminal);
		if (resterminal == 4)
		{
			printenumterminal(resterminal);
			printf("\n");
		}
		//else //TEST
		//{
			//printenumterminal(resterminal);
			//printf("\n");
		//}
		printf("\n");
	} while (resterminal == 4);
	
	
	terminal.maxTransAmount = 15000;
	resterminal = setMaxAmount(&terminal, 0.0); 
	
	resterminal = isBelowMaxAmount(&terminal);
	if (resterminal == 5)
	{
		printf("Declined Amount Exceeding Limit");
		printf("\n\n");
		exit(0);
	}
	//else //test
	//{
		//printenumterminal(resterminal);
		//printf("\n");
	//}

	
	resserver = isValidAccount(&card1, &accountsDB);
	if (resserver == 3)
	{
		printf("Declined Invalid Account");
		printf("\n\n");
		exit(0);
	}
	
	resserver = isBlockedAccount(&accountsDB);
	if (resserver == 5)
	{
		printf("Declined Stolen Card");
		printf("\n\n");
		exit(0);
	}

	resserver = isAmountAvailable(&terminal, &accountsDB);
	if (resserver == 4)
	{
		printf("Declined Insuffecient Fund");
		printf("\n\n");
		exit(0);
	}

	transaction.cardHolderData = card1;
	transaction.terminalData = terminal;
	transaction.transactionSequenceNumber = i;

	saveTransaction(&transaction);

	recieveTransactionData(&transaction);

	listSavedTransactions();

	i++;
	printf("\n\n");
	
}


//------------------------------------------TEST FUNCTIONS------------------------------------------

//void appStart(void)
//{
	//Test 1 CARD
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name: getCardHolderName");
	c = 1;
	while (1)
	{
		getCardHolderNameTest();
		rescard = getCardHolderName(&card1);
		printf("\nActual Result: ");
		printenumcard(rescard);
	}
	*/
	// end Test 1 CARD

	//Test 2 CARD
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name : getCardExpiryDate");
	c = 1;
	while (1)
	{
		getCardExpiryDateTest();
		rescard = getCardExpiryDate(&card1);
		printf("\nActual Result: ");
		printenumcard(rescard);
	}
	*/
	// end Test 2 CARD

	//Test 3 CARD
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name : getCardPAN");
	c = 1;
	while (1)
	{
		getCardPANTest();
		rescard = getCardPAN(&card1);
		printf("\nActual Result: ");
		printenumcard(rescard);
	}
	*/
	// end Test 3 CARD



	//Test 1 TERMINAL
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name : getTransactionDate");
	c = 1;
	while (1)
	{
		getTransactionDateTest();
		resterminal = getTransactionDate(&terminal);
		printf("\nActual Result: ");
		printenumterminal(resterminal);
	}
	*/
	// end Test 1 TERMINAL

	//Test 2 TERMINAL
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name : isCardExpried");
	c = 1;
	while (1)
	{
		isCardExpriedTest();
		resterminal = isCardExpired(&card1,&terminal);
		printf("\nActual Result: ");
		printenumterminal(resterminal);
	}
	*/
	// end Test 2 TERMINAL

	//Test 3 TERMINAL 
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name: getTransactionAmount");
	c = 1;
	while (1)
	{
		getTransactionAmountTest();
		resterminal = getTransactionAmount(&terminal);
		printf("\nActual Result: ");
		printenumterminal(resterminal);
	}
	*/
	// end Test 3 TERMINAL

	//Test 4 TERMINAL 
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name: setMaxAmount");
	c = 1;
	while (1)
	{
		setMaxAmountTest();
		resterminal = setMaxAmount(&terminal,0.0); //leeh el float dah????
		printf("\nActual Result: ");
		printenumterminal(resterminal);
	}
	*/
	// end Test 4 TERMINAL

	//Test 5 TERMINAL 
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name: isBelowMaxAmount");
	c = 1;
	while (1)
	{
		isBelowMaxAmountTest();
		resterminal = isBelowMaxAmount(&terminal);
		printf("\nActual Result: ");
		printenumterminal(resterminal);
	}
	*/
	// end Test 5 TERMINAL



    //Test 1 SERVER
    /*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name: isValidAccount");
	c = 1;
	while (1)
	{
		isValidAccountTest();
		serverError = isValidAccount(&card1, &accountsDB);
		printf("\nActual Result: ");
		printenumserver(serverError);
	}
	*/
	// end Test 1 SERVER

    //Test 2 SERVER
    /*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name: isBlockedAccount");
	c = 1;
	while (1)
	{
		isBlockedAccountTest();
		serverError = isBlockedAccount(&accountsDB);
		printf("\nActual Result: ");
		printenumserver(serverError);
	}
	*/
	// end Test 2 SERVER

    //Test 3 SERVER
    /*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name: isAmountAvailable");
	c = 1;
	while (1)
	{
		isAmountAvailableTest();
		serverError = isAmountAvailable(&terminal,&accountsDB);
		printf("\nActual Result: ");
		printenumserver(serverError);
	}
	*/
	// end Test 3 SERVER

    //Test 4 SERVER
	/*
	printf("Tester Name: Jehan Mohamed Refaa\nFunction Name: saveTransaction");
	c = 1;
	while (1)
	{
		saveTransactionTest();
		serverError = saveTransaction(&terminal);
		printf("\nActual Result: ");
		printenum_transState(transState);
	}
	*/
	// end Test 4 SERVER
//}


/*-----------Functions----------*/

// function to print enum results
void printenumcard(int e)
{
	switch (e)
	{
	case 0:
		printf("CARD_OK");
		break;
	case 1:
		printf("WRONG_NAME");
		break;
	case 2:
		printf("WRONG_EXP_DATE");
		break;
	case 3:
		printf("WRONG_PAN");
		break;
	}
}

void printenumterminal(int e)
{
	switch (e)
	{
	case 0:
		printf("TERMINAL_OK");
		break;
	case 1:
		printf("WRONG_DATE");
		break;
	case 2:
		printf("EXPIRED_CARD");
		break;
	case 3:
		printf("INVALID_CARD");
		break;
	case 4:
		printf("INVALID_AMOUNT");
		break;
	case 5:
		printf("EXCEED_MAX_AMOUNT");
		break;
	case 6:
		printf("INVALID_MAX_AMOUNT");
		break;
	}
}

void printenumserver(int e)
{
	switch (e)
	{
	case 0:
		printf("SERVER_OK");
		break;
	case 1:
		printf("SAVING_FAILED");
		break;
	case 2:
		printf("TRANSACTION_NOT_FOUND");
		break;
	case 3:
		printf("ACCOUNT_NOT_FOUND");
		break;
	case 4:
		printf("LOW_BALANCE");
		break;
	case 5:
		printf("BLOCKED_ACCOUNT");
		break;
	}
}

void printenumstate(int e)
{
	switch (e)
	{
	case 0:
		printf("RUNNING");
		break;
	case 1:
		printf("BLOCKED");
		break;
	}
}


/**************************************************CARD**************************************************/

// Test 1 CARD
void getCardHolderNameTest(void)
{
	printf("\n\nTest Case %d: ",c++);
	printf("\nInput Data: ");
	gets(card1.cardHolderName);
	int x = strlen(card1.cardHolderName);
	if (x < 20 || x>24)
	{
		rescard = WRONG_NAME;
	}
	else
	{
		rescard = CARD_OK;
	}
	printf("Expected Result: ");
	printenumcard(rescard);
}
// end Test 1 CARD


// Test 2 CARD
void getCardExpiryDateTest(void)
{
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data: ");
	gets(card1.cardExpirationDate);
	int x = strlen(card1.cardExpirationDate);
	if ((x != 5) || (card1.cardExpirationDate[2] != '/') || (card1.cardExpirationDate[0] > 49)
		|| (card1.cardExpirationDate[0] < 48) || (card1.cardExpirationDate[1] > 50 && card1.cardExpirationDate[0] == 49) ||
		(card1.cardExpirationDate[1] < 48 && card1.cardExpirationDate[0] == 49) || (card1.cardExpirationDate[1] > 57) ||
		(card1.cardExpirationDate[1] < 48) || (card1.cardExpirationDate[1] == 48 && card1.cardExpirationDate[0]== 48) ||
		(card1.cardExpirationDate[3] < 48) || (card1.cardExpirationDate[3] > 57) || (card1.cardExpirationDate[4] < 48) || (card1.cardExpirationDate[4] > 57))
	{
		rescard = WRONG_EXP_DATE;
	}
	else
	{
		rescard = CARD_OK;
	}
	printf("Expected Result: ");
	printenumcard(rescard);
}
// end Test 2 CARD


//Test 3 CARD
void getCardPANTest(void) 
{
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data: ");
	gets(card1.primaryAccountNumber);
	int x = strlen(card1.primaryAccountNumber);
	if (x < 16 || x > 19 )
	{
		rescard = WRONG_PAN;
	}
	else
	{
		rescard = CARD_OK;
	}
	printf("Expected Result: ");
	printenumcard(rescard);
}
// end Test 3 CARD

/**************************************************CARD**************************************************/



/************************************************TERMINAL************************************************/


// Test 1 TERMINAL
void isCardExpriedTest(void)
{
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data:\n");      
	gets(card1.cardExpirationDate); 
	gets(terminal.transactionDate); 
	if (terminal.transactionDate[8] < card1.cardExpirationDate[3])
	{
		resterminal = TERMINAL_OK;
	}
	else if (terminal.transactionDate[8] >  card1.cardExpirationDate[3])
	{
		resterminal = EXPIRED_CARD;
	}
	else if (terminal.transactionDate[9] < card1.cardExpirationDate[4])
	{
		resterminal = TERMINAL_OK;
	}
	else if (terminal.transactionDate[9] > card1.cardExpirationDate[4])
	{
		resterminal = EXPIRED_CARD;
	}
	else if (terminal.transactionDate[3] < card1.cardExpirationDate[0])
	{
		resterminal = TERMINAL_OK;
	}
	else if (terminal.transactionDate[3] > card1.cardExpirationDate[0])
	{
		resterminal = EXPIRED_CARD;
	}
	else if (terminal.transactionDate[4] <= card1.cardExpirationDate[1])
	{
		resterminal = TERMINAL_OK;
	}
	else
	{
		resterminal = EXPIRED_CARD;
	}
	printf("Expected Result: ");
	printenumterminal(resterminal);
}
// end Test 1 TERMINAL


// Test 2 TERMINAL
void getTransactionAmountTest(void)
{
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data: ");
	scanf_s("%f",&terminal.transAmount);
	if (terminal.transAmount <= 0.0)
	{
		resterminal = INVALID_AMOUNT;
	}
	else
	{
		resterminal = TERMINAL_OK;
	}
	printf("Expected Result: ");
	printenumterminal(resterminal);
}
// end Test 2 TERMINAL


// Test 3 TERMINAL
void setMaxAmountTest(void)
{
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data: ");
	scanf_s("%f", &terminal.maxTransAmount);
	if (terminal.maxTransAmount <= 0.0)
	{
		resterminal = INVALID_MAX_AMOUNT;
	}
	else
	{
		resterminal = TERMINAL_OK;
	}
	printf("Expected Result: ");
	printenumterminal(resterminal);
}
// end Test 3 TERMINAL


// Test 4 TERMINAL
void isBelowMaxAmountTest(void)
{
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data:\n");
	scanf_s("%f", &terminal.transAmount);
	scanf_s("%f", &terminal.maxTransAmount);
	if (terminal.transAmount > terminal.maxTransAmount)
	{
		resterminal = EXCEED_MAX_AMOUNT;
	}
	else
	{
		resterminal = TERMINAL_OK;
	}
	printf("Expected Result: ");
	printenumterminal(resterminal);
}
// end Test 4 TERMINAL

/************************************************TERMINAL************************************************/




/*************************************************SERVER*************************************************/

// Test 1 SERVER
void isValidAccountTest(void)
{
	ST_accountsDB_t accountsDB[255] = { {100,RUNNING,"1111111111111111"},{200,BLOCKED,"2222222222222222"},
								  {300,RUNNING,"3333333333333333"},{400,BLOCKED,"4444444444444444"},{500,RUNNING,"5555555555555555"},
								  {600,BLOCKED,"66666666666666666"},{700,RUNNING,"7777777777777777"},{800,BLOCKED,"8888888888888888"},
								  { 900,RUNNING,"9999999999999999" }, { 1000,BLOCKED,"0000000000000000" } };
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data:");
	gets(card1.primaryAccountNumber);
	for (int i = 0; i < 255; i++)
	{
		int x = strcmp(accountsDB[i].primaryAccountNumber, card1.primaryAccountNumber);
		if (x == 0)
		{
			serverError = SERVER_OK;
			break;
		}
		else
		{
			serverError = ACCOUNT_NOT_FOUND;
		}
	}
	printf("Expected Result: ");
	printenumserver(serverError);
}
// end Test 1 SERVER


// Test 2 SERVER
void isBlockedAccountTest(void)
{
	int y=0;
	ST_accountsDB_t accountsDBT[255] = { {100,RUNNING,"1111111111111111"},{200,BLOCKED,"2222222222222222"},
								  {300,RUNNING,"3333333333333333"},{400,BLOCKED,"4444444444444444"},{500,RUNNING,"5555555555555555"},
								  {600,BLOCKED,"66666666666666666"},{700,RUNNING,"7777777777777777"},{800,BLOCKED,"8888888888888888"},
								  { 900,RUNNING,"9999999999999999" }, { 1000,BLOCKED,"0000000000000000" } };
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data:\n");
	gets(card1.primaryAccountNumber);
	for (int i = 0; i < 255; i++)
	{
		int x = strcmp(accountsDBT[i].primaryAccountNumber, card1.primaryAccountNumber);
		if (x == 0)
		{
			y = i;
			break;
		}
		
	}
	accountsDB.balance = accountsDBT[y].balance;
	accountsDB.state = accountsDBT[y].state;
	strcpy_s(accountsDB.primaryAccountNumber, 20, accountsDBT[y].primaryAccountNumber);
	
	if (accountsDB.state == BLOCKED)
	{
		serverError = BLOCKED_ACCOUNT;
	}
	else
	{
		serverError = SERVER_OK;
	}
	printf("Expected Result: ");
	printenumserver(serverError);
}
// end Test 2 SERVER


// Test 3 SERVER
void isAmountAvailableTest(void)
{
	int y=0;
	ST_accountsDB_t accountsDBT[255] = { {100,RUNNING,"1111111111111111"},{200,BLOCKED,"2222222222222222"},
								  {300,RUNNING,"3333333333333333"},{400,BLOCKED,"4444444444444444"},{500,RUNNING,"5555555555555555"},
								  {600,BLOCKED,"66666666666666666"},{700,RUNNING,"7777777777777777"},{800,BLOCKED,"8888888888888888"},
								  { 900,RUNNING,"9999999999999999" }, { 1000,BLOCKED,"0000000000000000" } };
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data:\n");
	gets(card1.primaryAccountNumber);
	scanf_s("%f", &terminal.transAmount);

	for (int i = 0; i < 255; i++)
	{
		int x = strcmp(accountsDBT[i].primaryAccountNumber, card1.primaryAccountNumber);
		if (x == 0)
		{
			y = i;
			break;
		}

	}
	accountsDB.balance = accountsDBT[y].balance;
	accountsDB.state = accountsDBT[y].state;
	strcpy_s(accountsDB.primaryAccountNumber, 20, accountsDBT[y].primaryAccountNumber);
	
	if (terminal.transAmount > accountsDB.balance)
	{
		serverError = LOW_BALANCE;
	}
	else
	{
		serverError = SERVER_OK;
	}
	printf("Expected Result: ");
	printenumserver(serverError);
}
// end Test 3 SERVER


// Test 4 SERVER
/*
void saveTransactionTest(void)
{
	int y = 0;
	static int k = 0;
	ST_accountsDB_t accountsDBT[255] = { {100,RUNNING,"1111111111111111"},{200,BLOCKED,"2222222222222222"},
								  {300,RUNNING,"3333333333333333"},{400,BLOCKED,"4444444444444444"},{500,RUNNING,"5555555555555555"},
								  {600,BLOCKED,"66666666666666666"},{700,RUNNING,"7777777777777777"},{800,BLOCKED,"8888888888888888"},
								  { 900,RUNNING,"9999999999999999" }, { 1000,BLOCKED,"0000000000000000" } };
	ST_transaction_t transactionT[255];
	printf("\n\nTest Case %d: ", c++);
	printf("\nInput Data:\n");
	gets(card1.primaryAccountNumber);
	scanf_s("%f", &terminal.transAmount);

	for (int i = 0; i < 255; i++)
	{
		int x = strcmp(accountsDBT[i].primaryAccountNumber, card1.primaryAccountNumber);
		if (x == 0)
		{
			serverError = SERVER_OK;
			transState = APPROVED;
			y = i;
			break;
		}
		else
		{
			serverError = ACCOUNT_NOT_FOUND;
			transState = FRAUD_CARD;
		}
	}
	
	accountsDB.balance = accountsDBT[y].balance;
	accountsDB.state = accountsDBT[y].state;
	strcpy_s(accountsDB.primaryAccountNumber, 20, accountsDBT[y].primaryAccountNumber);

	if (accountsDB.state == BLOCKED)
	{
		serverError = BLOCKED_ACCOUNT;
		if (transState == APPROVED)
		{
			transState = DECLINED_STOLEN_CARD;
		}

	}
	else
	{
		serverError = SERVER_OK;
		
	}

	if (terminal.transAmount > accountsDB.balance)
	{
		serverError = LOW_BALANCE;
		if (transState == APPROVED)
		{
			transState = DECLINED_INSUFFECIENT_FUND;
		}

	}
	else
	{
		serverError = SERVER_OK;
		
	}

	transaction.cardHolderData = card1;
	transaction.terminalData = terminal;
	transaction.transactionSequenceNumber = k;
	transaction.transState = transState;

	transactionT[k].cardHolderData = transaction.cardHolderData;
	transactionT[k].terminalData = transaction.terminalData;
	transactionT[k].transactionSequenceNumber = transaction.transactionSequenceNumber;
	transactionT[k].transState = transaction.transState;
	
	printf("Expected Result: ");
	printenum_transState(transState);
}
// end Test 4 SERVER
*/

/*************************************************SERVER*************************************************/
