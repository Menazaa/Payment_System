#include "card.h"
#include <stdio.h>
#include <string.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

	printf("Enter Cardholder Name: \n");

	gets(cardData->cardHolderName);
	
	if (strlen(cardData->cardHolderName) > CARDHOLDER_NAME_MAX_LENGTH || 
    strlen(cardData->cardHolderName) < CARDHOLDER_NAME_MIN_LENGTH || 
    cardData->cardHolderName == NULL)
    {
        return WRONG_NAME;
    }
	
	return CARD_OK;

}
