#include <cs50.h>
#include <stdio.h>

int Luhn(long number);

int main(void)
{
    long number = get_long("Number: ");
    if (number > 1000000000000)
    {
        if (Luhn(number) == 1)
        {
            if (number > 4000000000000 && number < 5000000000000)
            //13-digit and start w/ 4
            {
                printf("VISA\n");
            }
            else if (number > 4000000000000000 && number < 5000000000000000)
            //16-digit and start w/ 4    
            {
                printf("VISA\n");
            }
            else if (number > 340000000000000 && number < 350000000000000)
            //15-digit and start w/ 34     
            {
                printf("AMEX\n");
            }
            else if (number > 370000000000000 && number < 380000000000000)
            //15-digit and start w/ 37
            {
                printf("AMEX\n");
            }
            else if (number > 5100000000000000 && number < 5600000000000000)
            //16-digit and start w/ 51, 52, 53, 54, 55
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
    else
    {
        printf("INVALID\n");
    }
}

int Luhn(long number)
{
    int sum = 0;
    while (number != 0)
    {
        //Add digit number from the back
        sum += number % 10;
        number = number / 10;
        
        //For every other digit by 2, multiplied by 2 & add products’ digits if > 10
        if (number != 0)
        {
            int temp;
            temp = number % 10 * 2;
            if (temp > 9)
            {
                sum = sum + temp % 10 + temp / 10;
            }
            else
            {
                sum += temp;
            };
            number = number / 10;
        }
    }
    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
