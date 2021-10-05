from cs50 import get_int
from math import floor


def main():
    # Get credit card no
    card_no = get_int("Number: ")
    
    # Check length
    if (card_no < 1000000000000 or card_no > 9999999999999999):
        print("INVALID")
    else :
        # Declare vars
        odd_digit_sum = 0
        even_digit_sum = 0
        card_copy = card_no
        card_length = len(str(card_no))
        
        # Luhn's algo
        while (card_copy != 0):
            
            # Odd digits
            if (card_copy % 2 != 0):
                odd_digit_sum += card_copy % 10
            
            # Even digits
            else:
                even_digit = card_copy % 10
                # Multiply even digits by two and sum
                even_digit *= 2
                if (even_digit > 9):
                    even_digit_sum += (even_digit / 10) + (even_digit % 10)
                else:
                    even_digit_sum += even_digit
            
            # Decrement card_copy
            card_copy /= 10
        
        # Add the even and odd digits
        digit_sum = even_digit_sum + odd_digit_sum
        # round it 
        digit_sum = floor(digit_sum)
        # print(digit_sum)
        
        # Check if last digit is 0
        if (digit_sum % 10 == 0):
            # Amex must have a length of 15 and start with a 34 or 37
            if (card_length == 15 and str(card_no)[0] == '3'):
                if (str(card_no)[14] == '4' or str(card_no)[14] == '7'):
                    print("AMEX")
                else:
                    print("INVALID")
            
            # Mastercard start with a 5
                


main()
