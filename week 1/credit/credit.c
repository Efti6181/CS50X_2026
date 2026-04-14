#include <cs50.h>
#include <stdio.h>
int main(void)
{
    long card = get_long("Number: ");
    long n = card;
    int sum = 0;
    int length = 0;
    bool alt = false;
    while (n > 0)
    {
        int digit = n % 10;
        if (alt)
        {
            int prod = digit * 2;
            sum += prod / 10 + prod % 10;
        }
        else
        {
            sum += digit;
        }
        alt = !alt;
        n /= 10;
        length++;
    }
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    long first_two = card;
    while (first_two >= 100)
    {
        first_two /= 10;
    }
    long first_one = first_two / 10;
    if (length == 15 && (first_two == 34 || first_two == 37))
        printf("AMEX\n");
    else if (length == 16 && (first_two >= 51 && first_two <= 55))
        printf("MASTERCARD\n");
    else if ((length == 13 || length == 16) && first_one == 4)
        printf("VISA\n");
    else
        printf("INVALID\n");
}
