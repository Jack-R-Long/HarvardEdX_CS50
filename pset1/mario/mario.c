#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Prompt for height
    int height ;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 | height > 8);
    
    // Loop for each line
    for (int line = 1; line < height + 1; line++)
    {
        // Loop for each column
        for (int column = 0; column < 2 * height + 3; column++)
        {
            if (column < height - line)
            {
                putchar(' ');
            }
            // Front pyramid
            else if (column < height)
            {
                putchar('#');
            }
            // Create middle row
            else if (column < height + 2)
            {
                putchar(' ');
            }
            // Back pyramid
            else if (column < height + 2 + line)
            {
                putchar('#');
            }
        }
        putchar('\n');
    }
}
