#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Dict_lib.h"

#define LENGTH 45  // Maximum length for a word

// Function to run the spellcheck program on a given file and compare against the expected output
bool run_test(FILE *file, int test_case_num) {
    char input_filename[100], expected_output[1024], actual_output[1024] = {0};
    FILE *input_file;

    // Read input filename
    if (fscanf(file, "%s", input_filename) != 1) {
        if (feof(file)) {
            printf("End of file reached.\n");
            return false;  // End of file reached
        }
        printf("Test case %d: Error reading input file name\n", test_case_num);
        return false;
    }

    printf("Test case %d: Reading file %s\n", test_case_num, input_filename);

    // Read expected output (list of misspelled words)
    if (fscanf(file, " %[^\n]", expected_output) != 1) {  // Read until the end of the line
        printf("Test case %d: Error reading expected output\n", test_case_num);
        return false;
    }
    printf("Test case %d: Expected output: %s\n", test_case_num, expected_output);

    // Open input text file
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Test case %d: Could not open file %s\n", test_case_num, input_filename);
        return false;
    }

    // Spell-checking logic
    char word[LENGTH + 1];
    while (fscanf(input_file, "%s", word) != EOF) {
        if (!check(word)) {
            strcat(actual_output, word);  // Append misspelled word
            strcat(actual_output, " ");  // Separate words with space
        }
    }
    fclose(input_file);

    // Remove trailing space from actual_output
    if (strlen(actual_output) > 0 && actual_output[strlen(actual_output) - 1] == ' ') {
        actual_output[strlen(actual_output) - 1] = '\0';
    }

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

    int passed = 0, failed = 0;
    int num_test_cases = 3;  // Number of test cases (or replace with a dynamic count)

    printf("Running tests...\n");

    for (int test_case_num = 1; test_case_num <= num_test_cases; test_case_num++) {
        if (!run_test(file, test_case_num)) {
            failed++;
        } else {
            passed++;
        }
    }

    fclose(file);

    printf("\nTotal tests: %d | Passed: %d | Failed: %d\n", passed + failed, passed, failed);

    return (failed == 0) ? 0 : 1;  // Return non-zero exit code if any test failed
}
