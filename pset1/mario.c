// include different libraries
#include <stdio.h>
#include <cs50.h>

// declare the variable


// let the magic happens
int main(void)
{
    int height;
    
    do
    {
        printf("Height of the mario's pyramid: ");
        height = GetInt();
    }
    while (height > 23 || height < 0);
                 
    for (int row = 1; row <= height; row++)
    {
        // print the spaces
        for (int space = 0; space > row - height; space--)
            printf(" ");
                        
        // print the hashes
        for ( int hash = height; hash >= height - row; hash--)
            printf("#");
                        
        // print a new line
        printf("\n");
        }
}
