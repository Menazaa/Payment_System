


#ifndef CARD_H
#define CARD_H

#define CARDHOLDER_NAME_MAX_LENGTH		24
#define CARDHOLDER_NAME_MIN_LENGTH		20
#define PAN_MAX_LENGTH					19
#define PAN_MIN_LENGTH					16
#define CARD_Expire_DATE_LENGTH			5



typedef unsigned char uint8_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;




EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


#endif