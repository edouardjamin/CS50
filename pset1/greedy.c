// include libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>

float owed;

int main(void)
{

    // say hello
    printf("O hai! ");

    // asking the user how much money is owed
    do
    {
        printf("How much money is owed? ");
        owed = GetFloat();
    }
    while (owed < 0);

    // covert money owed for float to int
    int owedC; 
    owedC = round(owed * 100);

    // calculate the number of cent used
    int quarter;
    for (quarter = 0; quarter < owedC / 25; quarter++)
    {}
    owedC = (owedC - quarter * 25);

    int dime;
    for (dime = 0; dime < owedC / 10; dime++)
    {}
    owedC = (owedC - dime * 10);

    int nickel;
    for (nickel = 0; nickel < owedC / 5; nickel++)
    {}
    owedC = (owedC - nickel * 5);

    int penny;
    for (penny = 0; penny < owedC / 25; penny++)
    {}
    owedC = (owedC - penny * 25);

    int total = quarter + dime + nickel + penny;

    printf("%d\n", total); 
}
