#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt for start size
    int start_size ;
    do
    {
        start_size = get_int("What is the starting population size? ");
    }
    while (start_size < 9);

    // Prompt for end size
    int end_size ;
    do
    {
        end_size = get_int("What is the ending population size? ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int current_size = start_size;
    int years = 0;
    while (current_size < end_size)
    {
        current_size += (current_size / 3) - (current_size / 4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", years);
}