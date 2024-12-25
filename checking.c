#include <stdio.h>    // Standard library for input/output functions
#include <ctype.h>    // Library for character manipulation
#include "Dict_lib.h" //Custom library, likely used for dictionary management with functions like load, check, unload, and size.

int main(int argc, char *argv[]) // The main function takes command-line arguments.
{
    char *filename = (argc == 2) ? argv[1] : "testfile1.txt"; // If the user provides a filename as an argument, it is used. Otherwise, the program uses "testfile1.txt" as the default file.

    printf("File to be checked: %s\n", filename);

    // load dictionary
    if (!load())
    {
        printf("Could not load dictionary\n");
        return 1;
    }

    // open txt file to check
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Couldn't open %s\n", filename);
        unload();
        return 1;
    }

    // get statistics
    printf("\n==========\nMISSPELLED WORDS\n==========\n");
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    // iterate through each word in file
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // allow only alphabetical characters
        if (isalpha(c))
        {
            word[index] = c;
            index++;

            // ignore strings longer than max length
            if (index > LENGTH)
            {
                while ((c = fgetc(file)) != EOF && isalpha(c))
                    ;
                index = 0;
            }
        }
        else if (isdigit(c))
        {
            // ignore
            while ((c = fgetc(file)) != EOF && isalnum(c))
                ;
            index = 0;
        }
        else if (index > 0)
        {
            // got whole word
            word[index] = '\0';
            index = 0;
            words++;

            if (!check(word))
            {
                printf("%s\n", word);
                misspellings++;
            }
        }
    }

    // cleanup

    fclose(file); // close file

    // unload dictionary
    unload(); // unload dictionary

    // print out statistics
    printf("\nDictionary word count: %d", size());
    printf("\nText word count:       %d", words);
    printf("\nMisspelled words:      %d", misspellings);

    return 0;
}