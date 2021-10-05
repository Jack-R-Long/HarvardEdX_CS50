from cs50 import get_int

def main():
    i = get_positive_int()
    print(i)
    

def get_positive_int():
    # Pythonic way to replicate a do while
    while True:
        n = get_int("Positive integer: ")
        if n > 0:
            break
    return n
    

main()