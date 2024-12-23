#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Dict_lib.h"

// Function to run the spellcheck program on a given file and compare against the expected output
bool run_test(FILE *file, int test_case_num) {
    char input_filename[100], expected_output[1024];
    char actual_output[1024] = {0};  // To hold the actual output
    FILE *input_file;

    // Read input filename and expected output
    if (fscanf(file, "%s", input_filename) != 1) {
        if (feof(file)) {
            printf("End of file reached.\n");
            return false;  // End of file reached
        }
        printf("Test case %d: Error reading input file name\n", test_case_num);
        return false;
    }

    // Debug print to check the filename
    printf("Test case %d: Reading file %s\n", test_case_num, input_filename);

    // Read expected output, ensuring to read a full line
    if (fscanf(file, " %[^\n]", expected_output) != 1) {  // Notice the space before %[^\n] to ignore any leading whitespace
        printf("Test case %d: Error reading expected output\n", test_case_num);
        return false;
    }

    // Debug print to check expected output
    printf("Test case %d: Expected output: %s\n", test_case_num, expected_output);

    // Open input text file
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Test case %d: Could not open file %s\n", test_case_num, input_filename);
        return false;
    }

    // Run the spell checker program (same logic as in `spellcheck.c` but redirect output)
    int  words = 0, misspellings = 0;
    char word[LENGTH + 1];

    // Read words from input file and check for misspellings
    while (fscanf(input_file, "%s", word) != EOF) {
        words++;
        if (!check(word)) {
            misspellings++;
            strcat(actual_output, word);  // Append misspelled word
            strcat(actual_output, "\n");
        }
    }

    fclose(input_file);

    // Compare actual output with expected output
    if (strcmp(actual_output, expected_output) == 0) {
        printf("Test case %d: Passed\n", test_case_num);
        return true;
    } else {
        printf("Test case %d: Failed\n", test_case_num);
        printf("Expected:\n%s\n", expected_output);
        printf("Actual:\n%s\n", actual_output);
        return false;
    }
}

int main() {
    FILE *file = fopen("testdataset.txt", "r");
    if (file == NULL) {
        perror("Error opening dataset file");
        return 1;
    }

    int test_case_num = 0;
    int passed = 0, failed = 0;

    printf("Running tests...\n");

    // Loop through all test cases in the dataset file
    while (!feof(file)) {
        test_case_num++;
        if (!run_test(file, test_case_num)) {
            failed++;
        } else {
            passed++;
        }
    }

    fclose(file);

    // Print test results
    printf("\nTotal tests: %d | Passed: %d | Failed: %d\n", passed + failed, passed, failed);

    return (failed == 0) ? 0 : 1;  // Return non-zero exit code if any test failed
}
