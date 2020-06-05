"""
Код на Си для переделки в Py
{
    //Request positive input
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0.009);
    // convert dollars to cents for future math
    int cents = round(dollars * 100);
    // count every piece of coin seoarately
    int quarters = cents / 25;
    int dimes = (cents - quarters * 25) / 10;
    int nickles = (cents - quarters * 25 - dimes * 10) / 5;
    int pennies = cents - quarters * 25 - dimes * 10 - nickles * 5;
    // then summ this pieces together
    int coins_count = quarters + dimes + nickles + pennies;
    printf("%i\n", coins_count);
}
"""

# подключаем функцию гет_флоат
from cs50 import get_float

# запрашиваем значение больше 1 цента
while True:
    dollars = get_float("Change owed: ")
    if dollars > 0.009:
        break

# превращаем доллары в центы и округялем
cents = round(dollars * 100)

# расчитываем количество монет каждого номинала, суммируем и печатаем
quarters = cents // 25  # используется // для того, чтобы отсечь знаки после запятой - в этом фишка
dimes = (cents - quarters * 25) // 10
nickles = (cents - quarters * 25 - dimes * 10) // 5
pennies = cents - quarters * 25 - dimes * 10 - nickles * 5
coins_count = quarters + dimes + nickles + pennies
print(int(coins_count))