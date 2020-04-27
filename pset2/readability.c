#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int find_W(int length, string s);
float find_L(int length, string s);
float find_S(int length, string s);

int main(int argc, string argv[])
{
    float CL_index;
    //W is the no. of words.
    //L is the average no. of letters per 100 words
    //S is the average no. of sentences per 100 words.
    int W;
    float L, S;

    string text = get_string("Text: ");
    int length = strlen(text);
    W = find_W(length, text);
    L = find_L(length, text) / W * 100;
    S = find_S(length, text) / W * 100;
    CL_index = 0.0588 * L - 0.296 * S - 15.8;
    int result = round(CL_index);

    if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    if (result > 16)
    {
        printf("Grade 16+\n");
    }
    else if (result >= 1 && result <= 16)
    {
        printf("Grade %i\n", result);
    }

}

int find_W(int length, string s)
{
    int count = 1;

    for (int i = 0; i < length; i++)
    {
        if (s[i] == ' ')
        {
            count++;
        }
    }
    //printf("W: %i\n", count);
    return count;
}

float find_L(int length, string s)
{

    int count = 0;

    for (int i = 0; i < length; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            count++;
        }
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            count++;
        }
    }

    //printf("L: %i\n", count);
    return count;

}

float find_S(int length, string s)
{

    int count = 0;

    for (int i = 0; i < length; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count++;
        }
    }

    //printf("S: %i\n", count);
    return count;

}