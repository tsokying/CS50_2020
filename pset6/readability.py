import re
from cs50 import get_string


def main():
    text = get_string("Text: ")
    # find Coleman-Liau index
    result = findCL(text)
    if result < 1:
        print("Before Grade 1")
    elif result >= 1 and result <= 16:
        print("Grade", result)
    else:
        print("Grade 16+")


def findCL(text):
    # formula 0.0588 * L - 0.296 * S - 15.8, where
    # L is the ave no.  of letters per 100 words
    # S is the ave no. of sentences per 100 words

    # more pythonic way than C's for loop
    words = len(re.findall(' ', text)) + 1
    L = sum(l.isalpha() for l in text) / words * 100
    S = len(re.findall(r'(?<=[.!?])', text)) / words * 100
    return round(0.0588 * L - 0.296 * S - 15.8)


main()