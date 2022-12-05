#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#include "terminal.h"
#include"../Card/card.h"

typedef unsigned int uint32_t;

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t  termData) {
    //2 digits of the year
    //MM/YY
    uint8_t expirationDateYears1 = cardData.cardExpirationDate[3] - '0';
    uint8_t expirationDateYears2 = cardData.cardExpirationDate[4] - '0';
    uint8_t expyear = 10 * expirationDateYears1 + expirationDateYears2;
    printf("the expiration year is :%d\n", expyear);
    //2 digits of the month
    //MM/Yy
    uint8_t expirationDateMonth1 = cardData.cardExpirationDate[0] - '0';
    uint8_t expirationDateMonth2 = cardData.cardExpirationDate[1] - '0';
    uint8_t expmonth = 10 * expirationDateMonth1 + expirationDateMonth2;
    printf("the expiration month is :%d\n", expmonth);


    // terminal date example: DD/MM/YYYY
    // last 2 digits indicates to years that will be compared
    uint8_t transDateYears1 = termData.transactionDate[8] - '0';
    uint8_t transDateYears2 = termData.transactionDate[9] - '0';
    uint8_t transyear = 10 * transDateYears1 + transDateYears2;
    printf("the transaction year is :%d\n", transyear);

    // Months digits that will be compared
    uint8_t transDateMonth1 = termData.transactionDate[3] - '0';
    uint8_t transDateMonth2 = termData.transactionDate[4] - '0';
    uint8_t transmonth = 10 * transDateMonth1 + transDateMonth2;
    printf("the transaction month is :%d\n", transmonth);

    // comparing
    if (expyear < transyear) return EXPIRED_CARD;
    else if (transyear < expyear) return TERMINAL_OK;
    else if (expmonth < transmonth) return EXPIRED_CARD;
    else if (transmonth < expmonth)return TERMINAL_OK;
    else return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
    printf("Please set the max amount:\n");
    scanf("%f", &termData->maxTransAmount);
    if (termData->maxTransAmount <= 0)
        return INVALID_MAX_AMOUNT;
    return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    printf("Please enter the transaction amount:\n");
    scanf("%f", &termData->transAmount);
    if (termData->transAmount <= 0)
        return INVALID_AMOUNT;
    return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    if (termData->transAmount > termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT;
    return TERMINAL_OK;
}

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
    printf("Please enter the transaction date:DD/MM/YY\n");
    gets(termData->transactionDate);

    uint8_t monthFirstDigit = termData->transactionDate[3] - '0';
    uint8_t monthSecondDigit = termData->transactionDate[4] - '0';
    uint8_t monthNumber = monthFirstDigit * 10 + monthSecondDigit;
    
    uint8_t dayFirstDigit = termData->transactionDate[0] - '0';
    uint8_t daySecondDigit = termData->transactionDate[1] - '0';
    uint8_t dayNumber = dayFirstDigit * 10 + daySecondDigit;
    //checking if day is between 1 and 31 inclusive
    if (strlen(termData->transactionDate) < 10 || termData->transactionDate == NULL|| termData->transactionDate[2]!='/'||
        termData->transactionDate[5] != '/'|| !(monthNumber >= 1 && monthNumber <= 12)|| !(dayNumber >= 1 && dayNumber <= 31))
        return WRONG_DATE;
    return TERMINAL_OK;
}