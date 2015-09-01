// include some useful libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // verify if the user enter the correct key within the command line
    if (argc != 2)
    {
        printf("Usage: ./vigenere <keyword>\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]))
        {
        }
        else
        {
            printf("Unvalide keyword\n");
            return 1;
        }
    }

    // get the keyword (in a string) and its length
    string keyword = argv[1];
    int keylen = strlen(keyword);

    // prompt the user the message
    string message = GetString();

    int messlen = strlen(message);

    int k = 0;

    // initiate variable for ASCII maths
    int upper = 65;
    int lower = 97;

    for (int i = 0; i < messlen; i++)
    {

        // convert each keyword char into a number (group)
        int keyAlpha = 0;
        if (isalpha(message[i]))
        {
            // modulo is used to divide each letter into a group
            int group = k % keylen;
            if (isupper(keyword[group]))
            {
                keyAlpha = keyword[group] - upper;
            }
            // if keyword char is lower
            else
            {
                keyAlpha = keyword[group] - lower;
            }
            k++;
        }
        else
        {
          // ignore spaces (k is not updated)
        }

       // verify if i is a letter
        if (isalpha(message[i]))
        {
            // action for upper case letters
            if (isupper(message[i]))
            {
                // ASCII -> Alpha, ASCII maths & Alpha -> ASCII
                int alpha = message[i] - upper;
                int modulo = (alpha + keyAlpha) % 26;
                int code = modulo + upper;
                printf("%c", code);
            }
            else
            {
              // ASCII -> Alpha, ASCII maths & Alpha -> ASCII
                int alpha = message[i] - lower;
                int modulo = (alpha + keyAlpha) % 26;
                int code = modulo + lower;
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
