#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int check(string s);
string substitution(int length, string key, string text);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (strlen(argv[1]) == 26)
        {
            if (check(argv[1]) == 1)
            {
                string plaintext = get_string("plaintext: ");
                int length = strlen(plaintext);
                string ciphertext = substitution(length, argv[1], plaintext);
                printf("ciphertext: %s\n", ciphertext);
            }
            else
            {
                printf("Key must contain 26 alphabetic characters, each letter exactly once.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 alphabetic characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

int check(string s)
{
    int count = 0;
    {
        for (int j = (int)'A'; j <= (int)'Z'; j++)
        {
            for (int i = 0; i < 26; i++)
            {
                char temp = toupper(s[i]);
                if (j == (int)temp)
                {
                    count++;
                    break;
                }
            }
        }
    }
    if (count == 26)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string substitution(int length, string key, string text)
{
    string ciphertext = text;
    for (int i = 0; i < length; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            ciphertext[i] = toupper(key[((int)text[i] - 65)]);
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            ciphertext[i] = tolower(key[((int)text[i] - 97)]);
        }
    }
    return ciphertext;
}