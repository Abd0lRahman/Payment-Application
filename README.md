# Payment-Application
## Application Flowchart
![image](https://user-images.githubusercontent.com/74074348/222790235-f76f687b-926f-4ecc-94f5-cbb1d2d1f6f7.png)

## The project can be distributed over 6 main tasks:


### 1-Development environment preparation

    1.Create modules folders
    2.Create .c and .h file for each module
    3.Add header file guard
    4.Create the main.c file

### 2-Implement the card module

    1.Fill in card.h file with functions' prototypes and typedefs
    2.Implement getCardHolderName function
    3.Implement getCardExpiryDate function
    4.Implement getCardPAN function

### 3-Implement the terminal module

    1.Fill in terminal.h file with functions' prototypes and typedefs
    2.Implement getTransactionDate function
    3.Implement isCardExpried function
    4.Implement gatTransactionAmount function
    5.Implement isBelowMaxAmount function
    6.Implement setMaxAmount function

### 4-Implement the server module

    1.Fill in server.h file with functions' prototypes and typedefs
    2.Implement server-side accounts' database
    3.Implement server-side transactions' database
    4.Implement recieveTransactionData function
    5.Implement isValidAccount function
    6.Implement isAmountAvailable function
    7.Implement saveTransaction function

### 5-Implement the application

    1.Fill in application.h file with functions' prototypes
    2.Implement appStart function

### 6-Testing the application

    1.Transaction approved user story
    2.Exceed the maximum amount user story
    3.Insufficient fund user story
    4.Expired card user story
    5.Invalid card user story
