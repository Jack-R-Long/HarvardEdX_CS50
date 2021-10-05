from cs50 import get_string
import re


def main():
    input_string = get_string("Text: ")
    
    # Get number of characters
    chars = input_string
    for x in [' ', '.', '\'', '!', ',', '?']:
        chars = chars.replace(x, '')
    num_letters = len(chars)
    
    # Get number of words
    word_list = input_string.split()
    num_words = len(word_list)
    
    # Get the number of sentences
    sentence_list = re.split(r'[.!?]+', input_string)
    num_sentences = len(sentence_list) - 1  # Account for empty last item
    
    # Coleman-Liau index computation
    L = num_letters / (num_words / 100)
    S = num_sentences / (num_words / 100)
    grade_level = round(0.0588 * L - 0.296 * S - 15.8)
    
    if (grade_level < 1):
        print("Before Grade 1")
    elif (grade_level < 16):
        print(f"Grade: {grade_level}")
    else:
        print("Grade 16+")


main()
