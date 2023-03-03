#include "server.h"
ST_accountsDB_t accountsDB[255]={{2000.0, RUNNING, "8989374615436851"},{80000.0, BLOCKED, "5807007076043875"},
                                 {10000.0, RUNNING, "8989374615436815"},{100000.0, BLOCKED, "5807007076043889"},
                                 {5000.0, RUNNING, "8989374615436800"},{9000.0, BLOCKED, "5807007076043890"},
                                 {100000.0, RUNNING, "5807007076043811"}};

ST_transaction_t transaction[255]={0};
uint8_t  AccountRef;
uint16_t TransactionSequanceNumber=0;
uint32_t transactionAmount ;

EN_transState_t recieveTransactionData (ST_transaction_t *transData)
{
    if (isValidAccount(&transData->cardHolderData, accountsDB) == ACCOUNT_NOT_FOUND )
    {
        transaction->transState=FRAUD_CARD;
        return FRAUD_CARD;
    }
    else if (isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT)
    {

        transaction->transState=DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    else if (isAmountAvailable(&transData->terminalData, accountsDB) == LOW_BALANCE)
    {
        printf("NotApproved\n");
        transaction->transState=DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    else if(saveTransaction(&transData))
    {
        transaction->transState=INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }
    else
    {
        printf("Approved\n");
        transaction->transState=APPROVED;
        TransactionSequanceNumber++;
        return APPROVED;
    }
}

void recieveTransactionDataTest(void)
{
    ST_transaction_t ServerTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: ReciveTransactionData\n");

    printf("Input Data:pan=8989374615436815TransactionAmount=5000\nExpected Result:Approved\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&ServerTest.cardHolderData);
    getTransactionAmount(&ServerTest.terminalData);
    recieveTransactionData(&ServerTest);


    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: ReciveTransactionData\n");

    printf("Input Data:TransactionAmount=15000\nExpected Result:Not Approved\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getTransactionAmount(&ServerTest.terminalData);
    recieveTransactionData(&ServerTest);
}



EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    for(uint8_t i=0;i<25;i++)
    {
        if(strcmp(cardData->primaryAccountNumber,accountRefrence[i].primaryAccountNumber)==0)
        {

            printf("Account is valid\n");
            AccountRef=i;
            return SERVER_OK;
        }
    }
    printf("Account isn't valid\n");

    return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void)
{
    ST_cardData_t cardTest;

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isValidAccount\nTest Case 1:Account isn't valid\n");

    printf("Input Data:9949574685436251\nExpected Result:Account isn't valid\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&cardTest); //to get card pan
    isValidAccount(&cardTest,accountsDB);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isValidAccount\nTest Case 2:Account is valid \n");

    printf("Input Data:8989374615436800\nExpected Result:Account is valid\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&cardTest);//to get card pan
    isValidAccount(&cardTest,accountsDB);
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    if((accountRefrence[AccountRef].state)==BLOCKED)
    {
        printf("Account is Blocked\n");
        return BLOCKED_ACCOUNT;
    }
    else if((accountRefrence[AccountRef].state)==RUNNING)
    {
        printf("Account isn't Blocked\n",AccountRef);
        return SERVER_OK;
    }
}

void isBlockedAccountTest(void)
{
    ST_cardData_t cardTest;

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isBlockedAccount\nTest Case 1:Account isn't Blocked\n");

    printf("Input Data:8989374615436800\nExpected Result:Account isn't Blocked\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&cardTest);//to get card pan
    isValidAccount(&cardTest,accountsDB);//to set accountRef that knows which account in the accountDB
    isBlockedAccount(accountsDB);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isBlockedAccount\nTest Case 2:Account is Blocked \n");

    printf("Input Data:5807007076043890\nExpected Result:Account is Blocked\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&cardTest);//to get card pan
    isValidAccount(&cardTest,accountsDB);//to set accountRef that knows which account in the accountDB
    isBlockedAccount(accountsDB);

}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    if((termData->transAmount) > (accountRefrence[AccountRef].balance))
    {
        printf("Can't make this Transaction due to low balance\n");
        return LOW_BALANCE;
    }
    printf("Amount is Avilable\n");
    return SERVER_OK;
}

void isAmountAvailableTest(void)
{
    ST_cardData_t cardTest;
    ST_terminalData_t TermTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isAmountAvailable\nTest Case 1:Amount isn't avilable\n");

    printf("Input Data:pan=8989374615436851&&Amount=5000\nExpected Result:Amount isn't avilable\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&cardTest);//to get card pan
    getTransactionAmount(&TermTest);//to get the amount of transaction
    isValidAccount(&cardTest,accountsDB);//to set accountRef that knows which account in the accountDB
    isAmountAvailable(&TermTest, accountsDB);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: isAmountAvilable\nTest Case 2:Amount is avilable \n");

    printf("Input Data:Amount=1000\nExpected Result:Amount is avilable\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getTransactionAmount(&TermTest);//to get the amount of transaction
    isValidAccount(&cardTest,accountsDB);//to set accountRef that knows which account in the accountDB
    isAmountAvailable(&TermTest, accountsDB);
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    transData->transactionSequenceNumber = (TransactionSequanceNumber + 1);
    transaction[TransactionSequanceNumber] = *transData;
    transactionAmount=transData->terminalData.transAmount;
    return SERVER_OK;
}

void saveTransactionTest(void)
{
    ST_transaction_t ServerTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: saveTransaction\n");

    getCardHolderName(&ServerTest.cardHolderData);
    getCardPAN(&ServerTest.cardHolderData);
    getCardExpiryDate(&ServerTest.cardHolderData);
    getTransactionDate(&ServerTest.terminalData);
    getTransactionAmount(&ServerTest.terminalData);
    recieveTransactionData(&ServerTest);
    saveTransaction(&ServerTest);
    listSavedTransactions();

}

void listSavedTransactions(void)
{
    accountsDB[AccountRef].balance=accountsDB[AccountRef].balance-transactionAmount;
    printf("#########################\n");
    printf("Transaction Sequence Number:%d\n",transaction[TransactionSequanceNumber-1].transactionSequenceNumber);
    printf("Transaction Date:%s\n",transaction[TransactionSequanceNumber].terminalData.transactionDate);
    printf("Transaction Amount:%f\n",transaction[TransactionSequanceNumber].terminalData.transAmount);
    printf("Transaction State: Approved\n");
    printf("Terminal Max Amount:%f\n",transaction[TransactionSequanceNumber].terminalData.maxTransAmount);
    printf("Card holder Name:%s\n",transaction[TransactionSequanceNumber].cardHolderData.cardHolderName);
    printf("PAN:%s\n",accountsDB[AccountRef].primaryAccountNumber);
    printf("NewBalance:%f\n",accountsDB[AccountRef].balance);
    printf("#########################\n");
}

void listSavedTransactionsTest(void)
{
    ST_transaction_t ServerTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: ListSavedTransaction\n");

    getCardHolderName(&ServerTest.cardHolderData);
    setMaxAmount(&ServerTest.terminalData,10000);
    getCardPAN(&ServerTest.cardHolderData);
    getCardExpiryDate(&ServerTest.cardHolderData);
    getTransactionDate(&ServerTest.terminalData);
    getTransactionAmount(&ServerTest.terminalData);
    recieveTransactionData(&ServerTest);
    saveTransaction(&ServerTest);
    listSavedTransactions();

}

