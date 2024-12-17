#include <stdio.h>
#include <stdlib.h>

// Prototype for the main function of the spellchecker
int main(int argc, char *argv[]);

void run_test(const char *test_file, const char *expected_output_file) {
    // Redirect input to test file
    FILE *input = freopen(test_file, "r", stdin);
    if (input == NULL) {
        fprintf(stderr, "Could not open test file: %s\n", test_file);
        return;
    }

    // Redirect output to a temporary file
    FILE *output = freopen("temp_output.txt", "w", stdout);
    if (output == NULL) {
        fprintf(stderr, "Could not redirect output\n");
        return;
    }

    // Run the main function
    printf("Running test with file: %s\n", test_file);
    char *argv[] = {"spellchecker", NULL};
    main(1, argv);
    // Reset stdin and stdout
    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);

    // Compare output with the expected result
    FILE *temp_output = fopen("temp_output.txt", "r");
    FILE *expected_output = fopen(expected_output_file, "r");
    if (temp_output == NULL || expected_output == NULL) {
        fprintf(stderr, "Could not open output files for comparison\n");
        return;
    }

    // Perform comparison line by line
    char temp_line[256], expected_line[256];
    int line_number = 0;
    int passed = 1;
    while (fgets(temp_line, sizeof(temp_line), temp_output) != NULL &&
           fgets(expected_line, sizeof(expected_line), expected_output) != NULL) {
        line_number++;
        if (strcmp(temp_line, expected_line) != 0) {
            printf("Mismatch on line %d:\nExpected: %sGot: %s\n", line_number, expected_line, temp_line);
            passed = 0;
        }
    }

    // Check if files ended at the same time
    if (!feof(temp_output) || !feof(expected_output)) {
        printf("File lengths do not match\n");
        passed = 0;
    }

    if (passed) {
        printf("Test passed for file: %s\n", test_file);
    } else {
        printf("Test failed for file: %s\n", test_file);
    }

    // Close files and clean up
    fclose(temp_output);
    fclose(expected_output);
    remove("temp_output.txt");
}

int main() {
    // Add your test cases here
    run_test("test_cases1.txt", "expected_output1.txt");
    run_test("test_cases2.txt", "expected_output2.txt");
    run_test("test_cases3.txt", "expected_output3.txt");

    return 0;
}
