#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(int argc, string argv[])
{
    // Ensure one CL arg
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Key must be 26 letters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // CL argument
    string key = argv[1];

    // Loop through key
    int letter;
    int used_letters[26];
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // Cast all upper to lowers
        key[i] = tolower(key[i]);
        letter = key[i];

        // Key must be only letters
        if (letter < 'a' | letter > 'z')
        {
            printf("Key must only contain letters.\n");
            return 1;
        }

        // Letters can only be used once
        for (int j = 0; j < n; j++)
        {
            if (letter == used_letters[j])
            {
                printf("Caught char copy at %c with used ref %c at index %d\n", letter, used_letters[j], j);
                printf("Key must use letters only once.\n");
                return 1;
            }
        }
        // Add letter to used array
        used_letters[i] = letter;
    }

    // Output
    string plain = get_string("plaintext: ");

    // Encrypt
    int plaintext_len = strlen(plain);
    string ciphertext = plain;
    for (int i = 0; i < plaintext_len; i++)
    {
        // Get alphabet position
        int alphabet_index = tolower(plain[i]) - 97;

        // Lowercase letters
        if (plain[i] >= 'a' & plain[i] <= 'z')
        {
            ciphertext[i] = key[alphabet_index];
        }
        // Uppercase letters
        else if (plain[i] >= 'A' & plain[i] <= 'Z')
        {
            ciphertext[i] = toupper(key[alphabet_index]);
        }
        // Non letters are unchanged
        else
        {
            ciphertext[i] = plain[i];
        }
    }

    // Output
    printf("ciphertext: %s\n", ciphertext);

}