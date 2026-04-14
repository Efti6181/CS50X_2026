from cs50 import get_string
def main():
    card = get_string("Number: ")
    if not luhn_check(card):
        print("INVALID")
        return
    if (len(card) == 15) and (card.startswith("34") or card.startswith("37")):
        print("AMEX")
    elif (len(card) == 16) and (51 <= int(card[:2]) <= 55):
        print("MASTERCARD")
    elif (len(card) in [13, 16]) and card.startswith("4"):
        print("VISA")
    else:
        print("INVALID")
def luhn_check(number):
    """Return True if number is valid per Luhn's algorithm, else False."""
    total = 0
    reverse_digits = number[::-1]
    for i, digit in enumerate(reverse_digits):
        n = int(digit)
        if i % 2 == 1:
            n *= 2
            if n > 9:
                n -= 9
        total += n
    return total % 10 == 0
if __name__ == "__main__":
    main()
