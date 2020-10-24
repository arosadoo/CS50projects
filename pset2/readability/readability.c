#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>




int main(void)
{
    int letters = 0; 
    int words = 0; 
    int sentences = 0;
    
    string text = get_string("Text: ");
    
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        
        // Chekcs for any lowercase letters in string
        if( (int) tolower(text[i]) >= 97 && (int) tolower(text[i]) <= 122)
        {
            letters++;
        }
        
        // Checks if first array index is the start of a word and checks for spaces followed by a letter to count words
        if(isalpha(text[0]) && i == 0)
        {
            words++;
        }
        else if(i > 0 && text[i-1] == ' ' && text[i] != ' ')
        {
            words++;
        }
        
        // Checks for excimlation, periods, question marks to count sentences
        if((int) text[i] == 33 || (int) text[i] == 46 || (int) text[i] == 63)
        {
            sentences++;
        }
    }
    
    // printf("Letters: %i\n", letters);
    // printf("Words: %i\n", words);
    // printf("Sentences: %i\n", sentences);
    
    float formula = 0.0588 * ( (float) letters / (float) words * 100) - (0.296 * ((float) sentences / (float) words * 100)) - 15.8;
    int index = round(formula);
    // printf("formula: %f\n", formula);
    // printf("index: %i\n", index);
    
    if(index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    
}