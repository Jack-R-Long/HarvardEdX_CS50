#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s:  ");
    
    // this is technically just an alias
    // char *t = s;  
    
    // memory allocation for #  extra byte for the null char
    char *t = malloc(strlen(s) + 1);
    // error checking if malloc trys to grab too much
    if (t == NULL)
    {
        return 1;
    }
    
    for (int i = 0; i <= strlen(s); i++)
    {
        t[i] = s[i];
    }
    
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }
    
    printf("s: %s\n", s);
    printf("t: %s\n", t);
    
    // give the mem back
    free(t);

}