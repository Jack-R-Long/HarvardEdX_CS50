#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(void)
{
    // Get sentence
    string sentence = get_string("Text: ");
    
    // Init counts
    int letter_count = 0;
    // Need to init word count at 1 for the first word
    int word_count = 1;
    int sentence_count = 0;
    char letter;
    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        // Cast all upper to lowers
        letter = tolower(sentence[i]);
        // Catch non letters
        if (letter < 'a' | letter > 'z')
        {
            // Count words
            if (letter == ' ')
            {
                word_count ++;
            }
            else if (letter == '.' | letter == '?' | letter == '?')
            {
                sentence_count ++;
            }
        }
        else
        {
            letter_count ++;
        }
    }
    // printf("Letter(s): %d\nWord(s): %d\nSentences(s): %d\n", letter_count, word_count, sentence_count);
    
    // Index calculations
    float avg_letters = letter_count / (word_count / 100.00);
    float avg_sentences = sentence_count / (word_count / 100.00);
    float index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;
    int answer = round(index);
    if (index < 2)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", answer);
    }

}
