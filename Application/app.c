#include "app.h"
void appStart(void)
{
    //Checking if card is OKAY if not start from the first
    ST_transaction_t server;

    if(getCardHolderName(&server.cardHolderData) !=CARD_OK)
    {
        printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
        appStart();
    }
    else if(getCardExpiryDate(&server.cardHolderData)!=CARD_OK)
    {
        printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
        appStart();
    }
    else if(getCardPAN(&server.cardHolderData)!=CARD_OK)
    {
        printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
        appStart();
    }
    //Checking if terminal is OKAY if not start from the first
    else
    {

        setMaxAmount(&server.terminalData,100000);
        if(getTransactionDate(&server.terminalData)!=TERMINAL_OK)
        {
            printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
            appStart();
        }
        else if(isCardExpired(&server.cardHolderData, &server.terminalData)!=TERMINAL_OK)
        {
            printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
            appStart();
        }
        else if(getTransactionAmount(&server.terminalData)!=TERMINAL_OK)
        {
            printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
            appStart();
        }
        else if(isBelowMaxAmount(&server.terminalData)!=TERMINAL_OK)
        {
            printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
            appStart();
        }
        else
        {
            if (recieveTransactionData(&server)==APPROVED)
            {
                if(saveTransaction(&server)==SERVER_OK)//every thing is okay
                {
                    listSavedTransactions();
                }
                else
                {
                    printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
                    appStart();
                }
            }
            else
            {
                printf("!!!!!!!!!!!!!!!application start from the beginning!!!!!!!!!!!!!!!\n");
                appStart();
            }
        }

    }

}
