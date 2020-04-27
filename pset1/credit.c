#include <cs50.h>
#include <stdio.h>

int Luhn(long number)
{
    int sum = 0;
    while (number != 0)
    {
        sum += number % 10;
        number = number / 10;
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

int main(void)
{
    long number = get_long("Number: ");
    if (number > 1000000000000)
    {
        if (Luhn(number) == 1)
        {
            if (number > 4000000000000 && number < 5000000000000)
            {
                printf("VISA\n");
            }
            else if (number > 4000000000000000 && number < 5000000000000000)
            {
                printf("VISA\n");
            }
            else if (number > 340000000000000 && number < 350000000000000)
            {
                printf("AMEX\n");
            }
            else if (number > 370000000000000 && number < 380000000000000)
            {
                printf("AMEX\n");
            }
            else if (number > 5100000000000000 && number < 5600000000000000)
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