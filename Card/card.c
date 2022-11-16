#include "card.h"
#include <stdio.h>
#include<stdlib.h>
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

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	printf("Enter your card expiry date is this format MM/YY : \n");
	gets(cardData->cardExpirationDate);

    uint8_t month_buf[2];
    uint8_t month;
    uint8_t year_buf[2];
    uint8_t year;


    memcpy( month_buf, &cardData->cardExpirationDate[0], 2 );
    sscanf(month_buf, "%d", &month);
    memcpy( year_buf, &cardData->cardExpirationDate[3], 2 );
    sscanf(year_buf, "%d", &year);



	if (strlen(cardData->cardExpirationDate) > 5 || cardData->cardExpirationDate[2] !='/' ||
                cardData->cardExpirationDate == NULL || !(month >= 1 && month <= 12) || (year<22))
            {
                return WRONG_EXP_DATE;
            }
		
	return CARD_OK;

}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter your Primary Account Number: \n");
	gets(cardData->primaryAccountNumber);
	
	if (strlen(cardData->primaryAccountNumber) > PAN_MAX_LENGTH || strlen(cardData->primaryAccountNumber) < PAN_MIN_LENGTH ||
	 	cardData->primaryAccountNumber == NULL)
		{
			return WRONG_PAN;	
		}
	return CARD_OK;
}