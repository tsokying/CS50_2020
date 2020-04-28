from cs50 import get_string


def main():
    n = get_string("Number: ")
    if Luhn(n) == True:
        if n.startswith('4'):
            if len(n) == 13 or len(n) == 16:
                # 13 or 16-digit and start w/ 4
                print("VISA")
        elif len(n) == 15:
            if n.startswith('34') or n.startswith('37'):
                # 15-digit and start w/ 34 or 37
                print("AMEX")
        elif int(n) > 5100000000000000 and int(n) < 5600000000000000:
            # 16-digit and start w/ 51, 52, 53, 54, 55
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


def Luhn(n):
    sum = 0
    number = int(n)
    while number >= 1:
        sum += number % 10
        number = number // 10
        # for every 2 digit, multiply 2
        if number >= 1:
            temp = number % 10 * 2
            # add the multiplied number by digit as well
            if (temp > 9):
                sum = sum + temp % 10 + temp // 10
            else:
                sum += temp
            number = number // 10
    if (sum % 10 == 0):
        return True
    else:
        return False


main()