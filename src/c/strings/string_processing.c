#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Manual string operations
size_t my_strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char* my_strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}

char* my_strcat(char* dest, const char* src) {
    char* original_dest = dest;
    while (*dest != '\0') {
        dest++;
    }
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}

// Character array manipulation
void reverse_string(char* str) {
    size_t len = my_strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void to_uppercase(char* str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void to_lowercase(char* str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

// Parsing and tokenization
int count_words(const char* str) {
    int count = 0;
    int in_word = 0;

    while (*str) {
        if (isspace(*str)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

char** split_string(const char* str, const char delimiter, int* count) {
    // First count the number of tokens
    *count = 1;
    for (const char* p = str; *p; p++) {
        if (*p == delimiter) (*count)++;
    }

    // Allocate array of pointers
    char** tokens = (char**)malloc(*count * sizeof(char*));
    if (!tokens) return NULL;

    // Split the string
    int token_index = 0;
    const char* start = str;
    const char* current = str;

    while (*current) {
        if (*current == delimiter) {
            size_t len = current - start;
            tokens[token_index] = (char*)malloc(len + 1);
            if (!tokens[token_index]) {
                // Cleanup on failure
                for (int i = 0; i < token_index; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                return NULL;
            }
            my_strcpy(tokens[token_index], start);
            tokens[token_index][len] = '\0';
            token_index++;
            start = current + 1;
        }
        current++;
    }

    // Handle the last token
    size_t len = current - start;
    tokens[token_index] = (char*)malloc(len + 1);
    if (!tokens[token_index]) {
        // Cleanup on failure
        for (int i = 0; i < token_index; i++) {
            free(tokens[i]);
        }
        free(tokens);
        return NULL;
    }
    my_strcpy(tokens[token_index], start);
    tokens[token_index][len] = '\0';

    return tokens;
}

// Test function
void test_string_processing() {
    printf("Testing String Processing Functions:\n");
    printf("--------------------------------\n");

    // Test my_strlen
    const char* test_str = "Hello, World!";
    printf("String length of '%s': %zu\n", test_str, my_strlen(test_str));

    // Test my_strcpy
    char dest[50];
    my_strcpy(dest, test_str);
    printf("Copied string: %s\n", dest);

    // Test my_strcat
    char cat_dest[50] = "Hello, ";
    my_strcat(cat_dest, "World!");
    printf("Concatenated string: %s\n", cat_dest);

    // Test reverse_string
    char rev_str[] = "Hello";
    reverse_string(rev_str);
    printf("Reversed string: %s\n", rev_str);

    // Test case conversion
    char case_str[] = "Hello World";
    to_uppercase(case_str);
    printf("Uppercase: %s\n", case_str);
    to_lowercase(case_str);
    printf("Lowercase: %s\n", case_str);

    // Test word counting
    const char* sentence = "Hello World! This is a test.";
    printf("Number of words in '%s': %d\n", sentence, count_words(sentence));

    // Test string splitting
    const char* split_str = "Hello,World,This,is,a,test";
    int token_count;
    char** tokens = split_string(split_str, ',', &token_count);
    printf("Split string into %d tokens:\n", token_count);
    for (int i = 0; i < token_count; i++) {
        printf("Token %d: %s\n", i + 1, tokens[i]);
        free(tokens[i]);
    }
    free(tokens);

    printf("\n");
}

int main() {
    test_string_processing();
    return 0;
}