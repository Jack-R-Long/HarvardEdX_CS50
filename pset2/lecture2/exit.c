#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("missing CL arguments\n");
        return 1;
    }
    printf("Hello %s\n", argv[1]);
}