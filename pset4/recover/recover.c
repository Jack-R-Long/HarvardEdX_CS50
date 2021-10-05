#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }
    
    // Open input files
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    // match count
    int image_count = -1;
    int in_block = 0;
    int block_match;
    int first_jpg = 1;
    // Create jpeg file name
    char jpeg_name[7];
    // pointer to open jpeg file
    FILE *img;
    // first 4 bytes
    BYTE jpeg_header[3] = {0xff, 0xd8, 0xff};
    // buffer to read 512 bytes block into
    BYTE buffer[BLOCK_SIZE];
    while (fread(buffer, BLOCK_SIZE, 1, input))
    {
        block_match = 1;
        // Check first 3 bytes of block
        for (int i = 0; i < 3; i++)
        {
            // printf("Byte %i: %x", i, buffer[i]);
            if (buffer[i] != jpeg_header[i])
            {
                block_match = 0;
            }
        }
        // Check fourth byte with bitwise & operation and make new file for new matches
        if ((buffer[3] & 0xf0) == 0xe0 && block_match)
        {
            image_count++;

            // first jpg
            if (first_jpg)
            {
                first_jpg = 0;
                in_block = 1;
                sprintf(jpeg_name, "%03i.jpg", image_count);
                img = fopen(jpeg_name, "w");

                // Write to file
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }
            // not first
            else
            {
                fclose(img);
                sprintf(jpeg_name, "%03i.jpg", image_count);
                img = fopen(jpeg_name, "w");

                // Write to file
                fwrite(buffer, BLOCK_SIZE, 1, img);
                
            }
        }
        // add to existing jpeg file
        else if (in_block)
        {
            // write to open file
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }
    
    // close files
    fclose(input);
    fclose(img);
 
}