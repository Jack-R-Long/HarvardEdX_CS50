from cs50 import get_int


def main():
    height = get_int("Height: ")
    # Input validaion
    while (height > 8 or height < 1):
        height = get_int("Height: ")
    
    # Call recursive function
    recursive_print(height, 1)


def recursive_print(height, row):
    # break condition
    if (height == 0):
        return
    
    empty_space = ' ' * (height - 1)
    bricks = '#' * row
    print(empty_space + bricks + 2 * ' ' + bricks)
    recursive_print(height - 1, row + 1)


main()
