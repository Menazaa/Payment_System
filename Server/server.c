#include "server.h"
#include"../Card/card.h"
#include <stdio.h>
#include <string.h>
//global variable for a found account in the database
ST_accountsDB_t* foundAccount = NULL;
//index of the found account
uint8_t indexFound;
//the database
ST_accountsDB_t dataBase[] =
{
        { 3000.00,RUNNING,"3456123567456789567"},
        {20000.00,RUNNING,"232345671234545671"},
        {9255.25,RUNNING,"561649578916341232",},
        {15070.1,BLOCKED,"451267832439342321"},
        {11040.00,RUNNING,"253218646449321323"},
        {2000.50,RUNNING,"65482375465465465419"},
        {0.00, RUNNING ,"97136248657454747435"},
        {1.00,  RUNNING,"793345353414854625" },
        { 50.1, RUNNING,"123123459067545466"},
        { 0.63, BLOCKED,"455435367898765433"},
};
//index of the found account
uint8_t indexFound;
ST_transaction_t transactions[] = {0};
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
    
    
    uint8_t isValid = isValidAccount((ST_cardData_t*)transData, dataBase);
    if (isValid == SERVER_OK) {
        uint32_t isBLOCKED = isBlockedAccount(foundAccount);
        if (isBLOCKED == RUNNING) {
           
            uint8_t isAmountAv = isAmountAvailable(transData, foundAccount);
            if (isAmountAv == SERVER_OK) {
               
                saveTransaction(transData);
                
                return APPROVED;
            }
            else if (isAmountAv == LOW_BALANCE) {
                return DECLINED_INSUFFECIENT_FUND;
            }
        }
        else if(isBLOCKED==BLOCKED)
        {

            return DECLINED_STOLEN_CARD;
        }
    }
    else {
        return FRAUD_CARD;
    }
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
    //getting number of elements in the database
    uint32_t sizeDB = sizeof(dataBase) / sizeof(ST_accountsDB_t);
    
    for (uint32_t i = 0; i < sizeDB; i++) {
        //to detect the found account and pass it to isAmountAvaliable later
        
        ST_accountsDB_t* currentAccount = (accountRefrence + i);
       
        if (strcmp(cardData->primaryAccountNumber,currentAccount->primaryAccountNumber)==0) {

            printf("\nAccount is Valid!");
            foundAccount = currentAccount;
            
            indexFound = i;
            return SERVER_OK;
        }
    }
    printf("\n%s", "Account is not Valid!");
    return ACCOUNT_NOT_FOUND;
}
EN_accountState_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
    if (accountRefrence->state == BLOCKED) {
       
        return BLOCKED;
    }
    else if (accountRefrence->state == RUNNING) {
        printf("\n%s", "your account is Running");
        return RUNNING;
    }
}
EN_serverError_t isAmountAvailable(ST_transaction_t* termData, ST_accountsDB_t* accountRefrence) {
    
    if (accountRefrence->balance < termData->terminalData.transAmount) {
        
       
      
        return LOW_BALANCE;
    }
    else
    {
        
       
        return SERVER_OK;
    }
}
uint8_t lastTransactionNum = 0;
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    transactions[lastTransactionNum].cardHolderData = transData->cardHolderData;
    transactions[lastTransactionNum].terminalData = transData->terminalData;
    transactions[lastTransactionNum].transactionSequenceNumber++;

    //editing the database
    foundAccount->balance -= transactions[lastTransactionNum].terminalData.transAmount;
    printf("your transaction is done and your new balance is: %f", foundAccount->balance);
    uint32_t isSaved = getTransaction(transactions[lastTransactionNum].transactionSequenceNumber, transData);
    //increment the index of last transaction to store the next transaction in a new place
    lastTransactionNum++;
    if (isSaved == SERVER_OK) {
        return SERVER_OK;
    }
    else
    {
       return SAVING_FAILED;
    }
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
    if (transactionSequenceNumber == transData->transactionSequenceNumber) {
        return SERVER_OK;
    }
    else {
        return TRANSACTION_NOT_FOUND;
    }
}