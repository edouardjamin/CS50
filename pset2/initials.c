// include some libraries
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{

    string name;

  // ask for the user's name
    name = GetString();

    // print the first letter
    printf("%c", toupper(name[0]));

    // print the next letter after a space
    for (int i = 0, nameLenght = strlen(name); i < nameLenght; i++)
    {
        if (isspace(name[i]))
        {
            printf("%c", toupper(name[i + 1]));
        }
      else
        {}
    }

    // print a new line at the end
    printf("\n");
}
