#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    int coins = 0;
    coins += cents / 25;
    cents = cents % 25;
    coins += cents / 10;
    cents = cents % 10;
    coins += cents / 5;
    cents = cents % 5;
    coins += cents;
    printf("%i\n", coins);
}
