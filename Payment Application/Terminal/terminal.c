#include "../Card/card.h"
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	EN_terminalError_t res; //dd/mm/yyyy
	int x = strlen(termData->transactionDate);

	if (x != 10 || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/' || (termData->transactionDate[3] > 49)
		|| (termData->transactionDate[3] < 48) || (termData->transactionDate[4] > 50 && termData->transactionDate[3] == 49) ||
		(termData->transactionDate[4] < 48 && termData->transactionDate[3] == 49) || (termData->transactionDate[4] > 57) 
		|| (termData->transactionDate[4] < 48) || (termData->transactionDate[3] == 48 && termData->transactionDate[4] == 48) 
		|| (termData->transactionDate[6] < 48) || (termData->transactionDate[6] > 57) || (termData->transactionDate[7] < 48) 
		|| (termData->transactionDate[7] > 57) || (termData->transactionDate[8] < 48) || (termData->transactionDate[8] > 57) 
		|| (termData->transactionDate[9] < 48) || (termData->transactionDate[9] > 57) || (termData->transactionDate[1] > 49 
			&& termData->transactionDate[0] == 51))
	{
		res = WRONG_DATE;
	}
	else
	{
		res = TERMINAL_OK;
	}

	return res;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	EN_terminalError_t res;
	
	if (termData->transactionDate[8] < cardData->cardExpirationDate[3])
	{
		res = TERMINAL_OK;
	}
	else if (termData->transactionDate[8] > cardData->cardExpirationDate[3])
	{
		res = EXPIRED_CARD;
	}
	else if (termData->transactionDate[9] < cardData->cardExpirationDate[4])
	{
		res = TERMINAL_OK;
	}
	else if (termData->transactionDate[9] > cardData->cardExpirationDate[4])
	{
		res = EXPIRED_CARD;
	}
	else if (termData->transactionDate[3] < cardData->cardExpirationDate[0])
	{
		res = TERMINAL_OK;
	}
	else if (termData->transactionDate[3] > cardData->cardExpirationDate[0])
	{
		res = EXPIRED_CARD;
	}
	else if (termData->transactionDate[4] <= cardData->cardExpirationDate[1])
	{
		res = TERMINAL_OK;
	}
	else
	{
		res = EXPIRED_CARD;
	}

	return res;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t res;
	if (termData->transAmount <= 0)
	{
		res = INVALID_AMOUNT;
	}
	else
	{
		res = TERMINAL_OK;
	}

	return res;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t res;
	if (termData->transAmount > termData->maxTransAmount)
	{
		res = EXCEED_MAX_AMOUNT;
	}
	else
	{
		res = TERMINAL_OK;
	}

	return res;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	EN_terminalError_t res;
	if (termData->maxTransAmount <= 0)
	{
		res = INVALID_MAX_AMOUNT;
	}
	else
	{
		res = TERMINAL_OK;
	}

	return res;
}

