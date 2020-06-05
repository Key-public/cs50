#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
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
 
