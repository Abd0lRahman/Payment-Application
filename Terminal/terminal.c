#include "terminal.h"
#include "../Server/server.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
     printf("please enter transaction date with format 'DD/MM/YYYY':");
    for(uint8_t counter=0;;counter++)                     //loop to get all char user entered
    {
        uint8_t user_entered=getchar();
        if(user_entered=='\n')       //check if user entered enter button and then check the condition of transaction date format
        {termData->transactionDate[counter]='\0';
            if(counter!=10 || termData->transactionDate[2]!='/' || termData->transactionDate[5]!='/')
            {
                printf("Transaction date must be 10 digits! & char'/' in the third and sixth\n");
                return WRONG_DATE;
            }
            else
            {
                printf("Transaction date is okay\n");
                return TERMINAL_OK;
            }
        }
        else                       //save the data in term data struct if the user didn't press enter yet
            termData->transactionDate[counter]=user_entered;
    }
}
void getTransactionDateTest(void)
{
        ST_terminalData_t terminalTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getTransactionDateTest\nTest Case 1:Transaction format not right \n");

    printf("Input Data:5/7/2022\nExpected Result:Transaction date must be 8 digits! & char'/' in the third and sixth\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getTransactionDate(&terminalTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getTransactionDateTest\nTest Case 2:Transaction format not right \n");

    printf("Input Data:5/07/2022\nExpected Result:Transaction date must be 8 digits! & char'/' in the third and sixth\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getTransactionDate(&terminalTest);

    printf("Tester Name: Abdelrahman Mahmoud Abd\nFunction Name: getTransactionDateTest\nTest Case 3:right transaction format \n");

    printf("Input Data:05/07/2022\nExpected Result:Transaction date is okay\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getTransactionDate(&terminalTest);
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    uint16_t card_exp_year = 0, card_exp_month = 0;
    card_exp_year = ((cardData->cardExpirationDate[3] - 48) * 10) + (cardData->cardExpirationDate[4] - 48);
    card_exp_month = ((cardData->cardExpirationDate[0] - 48) * 10) + (cardData->cardExpirationDate[1] - 48);
    uint16_t term_exp_year = 0, term_exp_month = 0;
    term_exp_year = ((termData->transactionDate[8] - 48) * 10) + (termData->transactionDate[9] - 48);
    term_exp_month = ((termData->transactionDate[3] - 48) * 10) + (termData->transactionDate[4] - 48);


    if(card_exp_year > term_exp_year)
    {
        printf("card is okay and not expired\n");
        return TERMINAL_OK;
    }
    else if ((card_exp_year == term_exp_year) && (card_exp_month >= term_exp_month))
    {
        printf("card is okay and not expired\n");
        return TERMINAL_OK;
    }
    else
    {
        printf("card is expired\n");
        return EXPIRED_CARD;
    }
}

void isCardExpiredTest(void)
{
    ST_cardData_t cardTest;
    ST_terminalData_t termTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isCardExpired\nTest Case 1:Card is expired \n");

    printf("Input Data:card expiry date less than transaction date\nExpected Result:card is expired\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");
    getCardExpiryDate(&cardTest);
    getTransactionDate(&termTest);
    isCardExpired(&cardTest,&termTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isCardExpired\nTest Case 2:card isn't expired \n");

    printf("Input Data:card expiry date less than transaction date\nExpected Result:card isn't expired\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardExpiryDate(&cardTest);
    getTransactionDate(&termTest);
    isCardExpired(&cardTest,&termTest);
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("please enter the transaction amount:");
    scanf("%f",&termData->transAmount);
    if((termData->transAmount)<=0)
    {
        printf("transaction amount must be positive value\n");
        return INVALID_AMOUNT;
    }
    else
    {
        return TERMINAL_OK;
    }

}
void getTransactionAmountTest(void)
{
        ST_terminalData_t terminalTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getTransactionAmount\nTest Case 1:Transaction amount less than or equal to zero\n");

    printf("Input Data:-80\nExpected Result:transaction amount must be positive value\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getTransactionAmount(&terminalTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getTransactionAmount\nTest Case 2:Transaction amount more than zero \n");

    printf("Input Data:89\nExpected Result:Transaction amount is okay\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getTransactionAmount(&terminalTest);

}

float MaxAmountOfTheTerminal=100000;

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{

    termData->maxTransAmount = MaxAmountOfTheTerminal;

    if((termData->maxTransAmount)>=(termData->transAmount))
    {
        return TERMINAL_OK;
    }
    else
    {
        printf("sorry That amount exceed maximum amount\n");
        return EXCEED_MAX_AMOUNT;
    }


}
void isBelowMaxAmountTest(void)
{
    ST_terminalData_t terminalTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isBelowMaxAmount\nTest Case 1:transaction amount higher than max amount\n");

    printf("Input Data:200,2000\nExpected Result:transaction amount must be less than max amount\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    isBelowMaxAmount(&terminalTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isBelowMaxAmount\nTest Case 2:Transaction is less than max amount \n");

    printf("Input Data:2000,2000\nExpected Result:Max amount is okay\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    isBelowMaxAmount(&terminalTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isBelowMaxAmount\nTest Case 3:Transaction is equal to max amount \n");

    printf("Input Data:4000,2000\nExpected Result:Max amount is okay\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    isBelowMaxAmount(&terminalTest);

}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    if (maxAmount <= 0)
    {
        return INVALID_MAX_AMOUNT;
    }

    else
    {
        MaxAmountOfTheTerminal=maxAmount;
        return TERMINAL_OK;
    }
}
void setMaxAmountTest(void)
{
    ST_terminalData_t terminalTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: setMaxAmount\nTest Case 1:Max amount less than or equal to zero\n");

    printf("Input Data:-150\nExpected Result:transaction amount must be positive value\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    setMaxAmount(&terminalTest,-150);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: setMaxAmount\nTest Case 2:Max amount more than zero \n");

    printf("Input Data:4000\nExpected Result:Max amount is okay\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    setMaxAmount(&terminalTest,4000);

}
