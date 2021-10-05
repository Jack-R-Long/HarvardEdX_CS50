#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string names[] = {"Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"};
    
    for (int i = 0; i < 7; i++)
    {
        // Can't compare whole strings in C
        // if (names[i] == "Ron")
        
        // strcmp compares each char of string ASCII-betically
        if (strcmp(names[i], "Ron") == 0)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}