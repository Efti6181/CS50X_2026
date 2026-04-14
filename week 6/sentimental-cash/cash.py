from cs50 import get_float
import math
while True:
    dollars = get_float("Change owed: ")
    if dollars >= 0:
        break
cents = round(dollars * 100)
coins = 0
coin_values = [25, 10, 5, 1]
for coin in coin_values:
    coins += cents // coin
    cents %= coin
print(coins)
