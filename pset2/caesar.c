// include some useful libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // verify if the user enter the key within the command line
    if (argc != 2)
    {
        printf("Usage: ./caesar <key>\n");
        return 1;
    }

    // transform the key string into an int
    int key = atoi(argv[1]);

    // prompt the user the message
    string message = GetString();

    for (int i = 0, messlen = strlen(message); i < messlen; i++)
    {
        // verify if i is a letter
        if (isalpha(message[i]))
        {
            // action for upper case letters
            if (isupper(message[i]))
            {
                // ASCII -> Alpha, ASCII maths, Alpha -> ASCCI
                int alpha = message[i] - 65;
                int modulo = (alpha + key) % 26;
                int code = modulo + 65;
                printf("%c", code);
            }
            else
            {
                // ASCII -> Alpha, ASCII maths, Alpha -> ASCCI
                int alpha = message[i] - 97;
                int modulo = (alpha + key) % 26;
                int code = modulo + 97;
                printf("%c", code);
            }

        }
        else
        {
            // print only the symbols
            printf("%c", message[i]);
        }
    }

    // print a new line
    printf("\n");
}
