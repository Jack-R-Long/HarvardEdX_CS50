#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(void)
{
    string s = get_string("Input: ");
    
    for (int i = 0; s[i] != '\0'; i++)
    {
        printf("Char is %c\n", s[i]);
    }
    
    // strlen looks for the \0 NULL char
    // declare strlen once instead of running it on each loop iteration
    for (int i = 0, n =strlen(s); i < n; i++)
    {
        printf("Char is %c\n", s[i]);
    }
}