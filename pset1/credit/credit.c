#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get credit card no
    long card_no = get_long("Number: ");

    // Check length
    if (card_no < 1000000000000 | card_no > 9999999999999999)
    {
        printf("INVALID\n");
    }
    else 
    {
        // Luhn's algo loop
        bool is_odd = true;
        int odd_digit;
        int odd_digit_sum = 0;
        int even_digit;
        int even_digit_sum = 0;
        long card_copy = card_no;
        int card_length = 0;
        while (card_copy != 0)
        {
            // Odd digits
            if (is_odd)
            {
                odd_digit = card_copy % 10;
                // Sum odd digits 
                odd_digit_sum = odd_digit_sum + odd_digit;
                is_odd = false;
                
            }
            // Even digits
            else
            {
                even_digit = card_copy % 10;
                // Multiply even digits by two and sum digits
                even_digit = even_digit * 2;
                if (even_digit > 9)
                {
                    even_digit_sum = even_digit_sum + (even_digit / 10) + (even_digit % 10);
                }
                else
                {
                    even_digit_sum = even_digit_sum + even_digit;
                }
                is_odd = true;
            }
            card_length ++;
            // Decremnet card_copy
            card_copy = card_copy / 10;
        }
        // Add the even and odd digit sum
        int total = even_digit_sum + odd_digit_sum;
        // printf("Luhn's sum is  %d and the card is %d digits long\n", total, card_length);

        // Check if last digit is 0
        if (total % 10 == 0)
        {
            // Amex must have a length of 15 and start with a 34 or 37
            if (card_length == 15 & odd_digit == 3)
            {
                if (even_digit == 8 | even_digit == 14)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            // Mastercard must start with a 5, changed to 10 because of Luhn's algo
            else if (even_digit == 10 & odd_digit < 6)
            {
                printf("MASTERCARD\n");
            }
            // Visa must have a length of 13 or 16 and start with a 4
            else if (even_digit == 8 | odd_digit == 4)
            {
                printf("VISA\n");
            }
            // Card does not fit any card type specs
            else
            {
                printf("INVALID\n");
            }
        }
        else 
        {
            // Card is invalid, does not pass Luhn's algo
            printf("INVALID\n");
        }

    }
}
