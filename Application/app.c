#include<stdio.h>
#include <stdlib.h>

#include "../Card/card.c"
#include "../Terminal/terminal.c"
#include "../Server/server.c"

void appStart(void) {
	
	ST_cardData_t client = { "","","" };
	ST_cardData_t* cptr = &client;
	ST_terminalData_t terminal={0,0,""};
	ST_terminalData_t* tptr = &terminal;

	uint8_t flag= 1;
	while (flag)
	{
		if (getCardHolderName(cptr) == WRONG_NAME) printf("Re-enter your name\n");
		else {
			printf("SUCCESS!\n");
			break;
		}
	}
	
	while (flag) {
		if (getCardExpiryDate(cptr) == WRONG_EXP_DATE) printf("Re-enter the date in a right formula\n");
		else { printf("SUCCESS!\n");
		break;
		}
	}
	
	

	while(flag){
		if (getCardPAN(cptr) == WRONG_PAN) printf("Enter a valid PAN\n");
		else { printf("SUCCESS!\n");
		break;
		}

	}
	while (flag) {
		if (getTransactionDate(tptr) == WRONG_DATE) printf("Re-enter a valid date\n");
		else {
			printf("SUCCESS!\n");
			break;
		}

	}
	uint8_t isExpired= isCardExpired(client, terminal);
	if ( isExpired== EXPIRED_CARD) {
		printf("YOUR CARD IS EXPIRED!");
		exit(200);
		
	}
	else if (isExpired == TERMINAL_OK) {
		uint8_t getTransaction = getTransactionAmount(tptr);
		if (getTransaction == TERMINAL_OK) {
			uint8_t setMax = setMaxAmount(tptr);
			if (setMax == TERMINAL_OK) {
				if (isBelowMaxAmount(tptr) == TERMINAL_OK) {
					printf("Valid amount less than the maximum!");
					

				}
				else if (isBelowMaxAmount(tptr) == EXCEED_MAX_AMOUNT) {
					printf("Transaction failed! you have exceeded the max amount");
					exit(200);
				}
			}
			else if (setMax == INVALID_MAX_AMOUNT) {
				printf("please enter a valid max amount");
			}
		}
		else if (getTransaction == INVALID_AMOUNT) {
			printf("please enter a valid amount");
		}

	}
	
	//creating the transaction
	ST_transaction_t transaction = {client ,terminal,APPROVED ,23};
	ST_transaction_t* transactionptr = &transaction;

	uint8_t validityOfTransaction= recieveTransactionData(transactionptr);
	
	if (validityOfTransaction == APPROVED) {
		printf("Transaction success\n");
	}
	else if (validityOfTransaction == DECLINED_INSUFFECIENT_FUND)
	{
		printf("LOW BALANCE!");
	}
	else if (validityOfTransaction ==DECLINED_STOLEN_CARD) {
		printf("your account is Blocked\n");
	}
	else if (validityOfTransaction == FRAUD_CARD) {
		printf("Account is not Valid!\n");

	}
	
	

}
int main() {
	appStart();
}