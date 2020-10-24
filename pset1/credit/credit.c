#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit = get_long("Number: ");
    long creditC = credit;

    int check = 1;
    int checkSumEven = 0;
    int checkSumOdd = 0;
    
    // Iterates through credit number following Luhn's Alg
    do
    {
        if (check % 2 == 0)
        {
            int digits = 2 * (credit % 10);
           
            do
            {
               checkSumEven = checkSumEven + (digits % 10);
               digits = digits / 10;
            }while(digits != 0);
        }
        
        else
        {
            checkSumOdd = checkSumOdd + (credit % 10);
            // printf("Odd: %i\n",checkSumOdd);
            // printf("credit number: %li\n",credit);
        }
        credit = credit / 10;
        check++;
    }while(credit != 0);
    
    int total = checkSumEven + checkSumOdd;
    
    // Checks if credit card is valid and assigns correct credit company for each valid credit card number
    if (total % 10 == 0)
    {
        if (creditC / 10000000000000 == 34 || creditC / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else if (creditC / 1000000000000 == 4 || creditC / 1000000000000000 == 4)
        {
            printf("VISA\n");
        }
        else if (creditC / 100000000000000 == 51 || creditC / 100000000000000 == 52 || creditC / 100000000000000 == 53 
        || creditC / 100000000000000 == 54 || creditC / 100000000000000 == 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}