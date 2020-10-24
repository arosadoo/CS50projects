#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool alphaCheck(string key);
bool repeatCheck(string key);
string encipher(string text, string key);

string ALPH = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, string argv[])
{

    // Validate Key Logic
    if (argc != 2)
    {
        printf("Usage: ./substitution key \n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters. \n");
        return 1;
    }
    else if (!alphaCheck(argv[1]))
    {
        printf("Key must only contain alphabetical characters. \n");
        return 1;
    }
    else if (repeatCheck(argv[1]))
    {
        printf("Key must not contain repeated characters. \n");
        return 1;
    }

    string plainText = get_string("plaintext: ");
    printf("ciphertext: %s\n", encipher(plainText, argv[1]));
    
}



// checks if string has any non alphabetical charcters
bool alphaCheck(string key)
{
    for(int i = 0, n = strlen(key); i < n; i++)
    {
        if (isalpha(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}


// Checks if any repeated characters are in the key
bool repeatCheck(string key)
{
    for(int i = 0, n = strlen(key); i < n; i++)
    {
        int check = 0;
        for(int j = 0, m = strlen(key); j < m; j++)
        {
           if(key[i] == key[j]) 
           {
               check++;
           }
        }
        
        if(check > 1)
        {
            return true;
        }
    }
    return false;
    
}


// Enciphers the plain text using they given key
string encipher(string text, string key)
{
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            for (int j = 0, m = strlen(ALPH); j < m; j++)
            {
                if(tolower(text[i]) == tolower(ALPH[j]) && isupper(text[i]))
                {
                    text[i] = toupper(key[j]);
                    break;
                }
                else if (tolower(text[i]) == tolower(ALPH[j]) && islower(text[i]))
                {
                    text[i] = tolower(key[j]);
                    break;
                }
            }
        }
    }
    return text;
}