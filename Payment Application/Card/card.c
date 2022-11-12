#include "card.h"
#include <string.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	EN_cardError_t res;
	
	int x = strlen(cardData->cardHolderName);
	if ((x < 20) || (x > 24))
	{
		res= WRONG_NAME;
	}
	else
	{
		res= CARD_OK;
	}
	
	return res;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t res;
	int x = strlen(cardData->cardExpirationDate); // mm/yy
	
	if (x!=5 || cardData->cardExpirationDate[2]!='/' || (cardData->cardExpirationDate[0] > 49) ||
		(cardData->cardExpirationDate[0] < 48) || (cardData->cardExpirationDate[1] > 50 && cardData->cardExpirationDate[0] == 49) 
		|| (cardData->cardExpirationDate[1] < 48 && cardData->cardExpirationDate[0] == 49) || (cardData->cardExpirationDate[1] > 57)
		|| (cardData->cardExpirationDate[1] < 48) || (cardData->cardExpirationDate[1] == 48 && cardData->cardExpirationDate[0] == 48) 
		|| (cardData->cardExpirationDate[3] < 48) || (cardData->cardExpirationDate[3] > 57) || (cardData->cardExpirationDate[4] < 48) 
		|| (cardData->cardExpirationDate[4] > 57))
	{
		res = WRONG_EXP_DATE;
	}
	else
	{
		res = CARD_OK;
	}

	return res;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t res;

	int x = strlen(cardData->primaryAccountNumber);
	if ((x < 16) || (x > 19))
	{
		res = WRONG_PAN;
	}
	else
	{
		res = CARD_OK;
	}

	return res;
}