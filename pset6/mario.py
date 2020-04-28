from cs50 import get_int
from sys import exit

while True:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        for i in range(h):
            # pythonic way (?)
            print(" " * int(h-i-1) + "#" * int(i+1) + "  " + "#" * int(i+1))
        exit(0)
