# Project-5-Develop-a-Basic-Spell-Checker
I. Dictionary Logic (Dict_lib.c and Dict_lib.h)
These files handle the dictionary management and provide the core functionality for verifying words:

step1: load(const char *dictionary): Loads the dictionary file (ValidWords.txt) into memory.
step2: check(const char *word): Checks if a given word exists in the dictionary.
step3: unload(): Frees the memory allocated for the dictionary.

II. Spell Checking Logic (checking.c)
This file contains the main spell-checking program: 
step1: Reads a text file (text.txt) word by word .
step2: Identifies misspelled words by comparing them against the dictionary using the check() function.
step3: Outputs the misspelled words.

III. Test Framework (test_code.c)
The test framework validates the spell-checker:
1-Reads a test dataset (testdataset.txt) containing input files and their expected outputs.
2-Executes the spell-checker on each input file (testfile1.txt - testfile2.txt - testfile3.txt).
3-Compares the actual output to the expected output.
4-Reports test results, indicating which test cases passed or failed. 
    
    exemple: Running tests...
             Test case 1: Passed
             Test case 2: Failed
             Expected: texxxt twwoo
             Actual: texxxt
             