#include "..\Card\card.h"
#include "..\Terminal\terminal.h"
#include "server.h"
#include <stdio.h>
#include <string.h>

int iter = 0;
int j=0;

ST_accountsDB_t accountsDB[255] = { {100,RUNNING,"1111111111111111"},{200,BLOCKED,"2222222222222222"},
	                              {300,RUNNING,"3333333333333333"},{400,BLOCKED,"4444444444444444"},{500,RUNNING,"5555555555555555"},
	                              {600,BLOCKED,"66666666666666666"},{700,RUNNING,"7777777777777777"},{800,BLOCKED,"8888888888888888"},
	                              { 900,RUNNING,"9999999999999999" }, { 1000,BLOCKED,"0000000000000000" } };

ST_transaction_t transaction[255]= { 0,0,0,0 };

EN_transState_t TEST; //APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
void printenum_transState(int);

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	accountsDB[j].balance = accountsDB[j].balance - transaction[iter].terminalData.transAmount;
	return TEST;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t res;
	for (int i = 0; i < 255; i++)
	{
		int x = strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber);
		if (x == 0)
		{
			res = SERVER_OK;
			accountRefrence->balance = accountsDB[i].balance;
			strcpy_s(accountRefrence->primaryAccountNumber, 20, accountsDB[i].primaryAccountNumber);
			accountRefrence->state = accountsDB[i].state;
			TEST = APPROVED;
			j = i;
			break;
		}
		else
		{
			res = ACCOUNT_NOT_FOUND;
			TEST = FRAUD_CARD;

		}
	}
		
	return res;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t res;
	if (accountRefrence->state == BLOCKED)
	{
		res = BLOCKED_ACCOUNT;
		if (TEST == APPROVED)
		{
			TEST = DECLINED_STOLEN_CARD;
		}

	}
	else
	{
		res = SERVER_OK;
		TEST = APPROVED;
	}
	return res;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t res;
	if (termData->transAmount > accountRefrence->balance)
	{
		res = LOW_BALANCE;
		if (TEST == APPROVED)
		{
			TEST = DECLINED_INSUFFECIENT_FUND;
		}

	}
	else
	{
		res = SERVER_OK;
		TEST = APPROVED;
	}
	
	return res;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transaction[iter].cardHolderData = transData->cardHolderData;
	transaction[iter].terminalData = transData->terminalData;
	transaction[iter].transactionSequenceNumber = transData->transactionSequenceNumber;
	transaction[iter].transState = TEST;
	return TEST;
}


void listSavedTransactions(void)
{
	printf("#########################\n");
	printf("Transaction Sequence Number: %d\n", transaction[iter].transactionSequenceNumber);
	printf("Transaction Date: %s\n", transaction[iter].terminalData.transactionDate);
	printf("Transaction Amount: %f\n", transaction[iter].terminalData.transAmount);
	printf("Transaction State: ");
	printenum_transState(transaction[iter].transState);
	printf("\nTerminal Max Amount: %f\n", transaction[iter].terminalData.maxTransAmount);
	printf("Cardholder Name: %s\n", transaction[iter].cardHolderData.cardHolderName);
	printf("PAN: %s\n", transaction[iter].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s\n", transaction[iter].cardHolderData.cardExpirationDate);
	printf("#########################\n");
	printf("BALANCE REMAINING: %f\n\n", accountsDB[j].balance);
	
	iter++;
}

void printenum_transState(int e)
{
	switch (e)
	{
	case 0:
		printf("APPROVED");
		break;
	case 1:
		printf("DECLINED_INSUFFECIENT_FUND");
		break;
	case 2:
		printf("DECLINED_STOLEN_CARD");
		break;
	case 3:
		printf("FRAUD_CARD");
		break;
	case 4:
		printf("INTERNAL_SERVER_ERROR");
		break;
	}
}
