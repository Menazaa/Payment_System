#include<stdio.h>

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

void appStart(void) {
	
	ST_cardData_t customer1 = { "","","" };
	ST_cardData_t* cptr = &customer1;
	ST_terminalData_t terminal1={0,0,""};
	ST_terminalData_t* tptr = &terminal1;

	uint8_t flag= 1;
	while (flag)
	{
		if (getCardHolderName(cptr) == WRONG_NAME) printf("Please re-enter your name\n");
		else {
			printf("SUCCESS!\n");
			break;
		}
	}
	
	while (flag) {
		if (getCardExpiryDate(cptr) == WRONG_EXP_DATE) printf("Please re-enter the date in a right formula\n");
		else { printf("SUCCESS!\n");
		break;
		}
	}
	
	

	while(flag){
		if (getCardPAN(cptr) == WRONG_PAN) printf("Please enter a valid PAN\n");
		else { printf("SUCCESS!\n");
		break;
		}

	}
	while (flag) {
		if (getTransactionDate(tptr) == WRONG_DATE) printf("Please re-enter a valid date\n");
		else {
			printf("SUCCESS!\n");
			break;
		}

	}
	uint8_t isExpired= isCardExpired(customer1, terminal1);
	if ( isExpired== EXPIRED_CARD) {
		printf("YOUR CARD IS EXPIRED!");
		exit();
		
	}
	else if (isExpired == TERMINAL_OK) {
		uint8_t getTransaction = getTransactionAmount(tptr);
		if (getTransaction == TERMINAL_OK) {
			uint8_t setMax = setMaxAmount(tptr);
			if (setMax == TERMINAL_OK) {
				if (isBelowMaxAmount(tptr) == TERMINAL_OK) {
					printf("Valid amount less than the maximum!");
					//getch();

				}
				else if (isBelowMaxAmount(tptr) == EXCEED_MAX_AMOUNT) {
					printf("Transaction failed! you have exceeded the max amount");
					exit();
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
	ST_transaction_t transaction = {customer1,terminal1,APPROVED ,23};
	ST_transaction_t* transptr = &transaction;

	uint8_t validityOfTransaction= recieveTransactionData(transptr);
	
	if (validityOfTransaction == APPROVED) {
		printf("\nTransaction success:ENOUGH BALANCE!\n");
	}
	else if (validityOfTransaction == DECLINED_INSUFFECIENT_FUND)
	{
		printf("\nTransaction failed:LOW BALANCE!");
	}
	else if (validityOfTransaction ==DECLINED_STOLEN_CARD) {
		printf("%s", "your account is Blocked");
	}
	else if (validityOfTransaction == FRAUD_CARD) {
		printf("\n%s", "Account is not Valid!");

	}
	
	

}
int main() {
	appStart();
}