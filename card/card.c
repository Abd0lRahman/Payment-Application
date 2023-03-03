#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData) //function to get card holder name
{
    printf("please enter card holder name:");
    gets(cardData->cardHolderName);
        if((strlen(cardData->cardHolderName)>24)||(strlen(cardData->cardHolderName)<20))
        {
            printf("Name must be between 20 and 24\n");
            return WRONG_NAME;
        }
        else
        {
                printf("Name is okay\n");
        }
    return CARD_OK;
}
void getCardHolderNameTest(void)
{
    ST_cardData_t cardTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getCardHolderName\nTest Case 1:characters less than 20 \n");

    printf("Input Data:Abdelrahman Mahmoud\nExpected Result:Name must be between 20 and 24\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardHolderName(&cardTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getCardHolderName\nTest Case 2:characters more than 24 \n");

    printf("Input Data:Abdelrahman Mahmoud Abdelsalam\nExpected Result:Name must be between 20 and 24\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardHolderName(&cardTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getCardHolderName\nTest Case 3:CARD OK \n");

    printf("Input Data:Abdelrahman Mahmoud Abdo\nExpected Result:Name is okay\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardHolderName(&cardTest);
}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("please enter card holder expiry date'the format must be like MM/YY':");
    for(uint8_t counter=0;;counter++)                     //loop to get all char user entered
    {
        uint8_t user_entered=getchar();
        if(user_entered=='\n')       //check if user entered enter button and then check the condition of card expiry date should be 5 digits
        {
            cardData->cardExpirationDate[counter]='\0';
            if(counter!=5 || cardData->cardExpirationDate[2]!='/')
            {
                printf("Card expiry date must be 5 digits! & char'/' in the middle\n");
                return WRONG_EXP_DATE;
            }
            else
            {
                printf("Card expiry date is okay\n");
                return CARD_OK;

            }
        }
        else                                                //save the data in card data struct if the user didn't press enter yet
            cardData->cardExpirationDate[counter]=user_entered;
    }
}

void getCardExpiryDateTest(void)
{
    ST_cardData_t cardTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getCardExpiryDate\nTest Case 1:expiry date not 5 digits \n");

    printf("Input Data:5/9\nExpected Result:Card expiry date must be 5 digits! \n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardExpiryDate(&cardTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getCardExpiryDate\nTest Case 2:card okay \n");

    printf("Input Data:05/09\nExpected Result:CARD OKAY\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardExpiryDate(&cardTest);

    printf("Tester Name: Abdelrahman Mahmoud Abd\nFunction Name: getCardExpiryDate\nTest Case 3: expiry date without '/' \n");

    printf("Input Data:05:09\nExpected Result:CARD OK\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardExpiryDate(&cardTest);
}


EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("please enter card PAN:");
    for(uint8_t counter=0;;counter++)                     //loop to get all char user entered
    {
        uint8_t user_entered=getchar();
        if(user_entered=='\n')       //check if user entered enter button and then check the condition of card expiry date should be 5 digits
        {
            cardData->primaryAccountNumber[counter]='\0';
            if ((strlen(cardData->primaryAccountNumber) > 19) && (strlen(cardData->primaryAccountNumber < 16)))
            {
                printf("Card PAN must be from 16 to 19 numrical \n");
                return WRONG_PAN;
            }
            else
            {

                printf("Card PAN is okay\n");
                return CARD_OK;
            }
        }
        else                                                //save the data in card data struct if the user didn't press enter yet
            cardData->primaryAccountNumber[counter]=user_entered;
    }
}
void getCardPANTest(void)
{
    ST_cardData_t cardTest;
    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getCardPAN\nTest Case 1:PAN less than 16 \n");

    printf("Input Data:123456789012345\nExpected Result:Card PAN must be more than 16! \n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&cardTest);

    printf("Tester Name: Abdelrahman Mahmoud Abdelsalam\nFunction Name: getCardPAN\nTest Case 2:PAN more than 19 \n");

    printf("Input Data:12345678901234567890\nExpected Result:Card PAN must be less than 19! \n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&cardTest);

    printf("Tester Name: Abdelrahman Mahmoud Abd\nFunction Name: getCardExpiryDate\nTest Case 3: PAN is between 16 and 19 \n");

    printf("Input Data:12345678901234567\nExpected Result:CARD OK\n");

    printf("!!!!!!!!!!!!!!FUNCTION STARTS!!!!!!!!!!!!!!!!!\n");

    getCardPAN(&cardTest);
}

