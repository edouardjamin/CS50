/**
* recover.c
*
* Computer Science 50
* Problem Set 4
*
* Recovers JPEGs from a forensic image.
*/

#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // open the JPEG file
    FILE* file = fopen("card.raw", "r");

    // initiate the counter
    int counter = 0;

    // initiate buffer
    BYTE buffer[512];

    // three-digit decimal number from 000 on up
    char lname[10];

    // declare a temp file
    FILE* temp = NULL;

    // repeat until the end of the card
    while(!feof(file))
    {
      // check if it is the begging of a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            if (temp != NULL)
                fclose(temp);

            // label the files with three digits
            sprintf(lname, "%03d.jpg", counter);

            // next file in line
            temp = fopen(lname, "w");

            // update the counter
            counter++;

            // create a new file
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
      else if (counter > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, temp);
      }

        fread(buffer, sizeof(buffer), 1, file);

    }

    // close file
    fclose(file);

    // that's all folks
    return 0;
}
