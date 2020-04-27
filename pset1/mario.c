#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height: ");
    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }
    for (int i = 0; i < height; i++)
    {
        // for line i, print (height-i) spaces in the front
        for (int j = 0; j < height - 1 - i; j++)
        {
            printf(" ");
        };    
        // and then print (i) # 
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        };
        printf("  ");
        // again, print (i) # 
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        };
        //next line
        printf("\n");
    }
}