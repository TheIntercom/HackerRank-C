/*
The prompt provides the includes and main with driver code.

We are asked to complete the logic and operation of the following functions:
-- lexicographic_sort : Selects larger string based on strength of letters, then number of letters.
-- lexicographic_sort_reverse : Selects smaller string based on strength of letters, then number of letters.
-- sort_by_number_of_distinct_characters : Selects string based on number of unique letters.
-- sort_by_length : Selects string based on total number of characters.
-- string_sort : Takes string array and a function pointer to define sorting behavior.

The driver code will read in 'n' number of words and organize them using each of the sort functions we define.

Sample input:
4
wkue
qoi
sbv
fekls

Sample output:
fekls
qoi
sbv
wkue

wkue
sbv
qoi
fekls

qoi
sbv
wkue
fekls

qoi
sbv
wkue
fekls
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------ code above is provide by the prompt ------------------

int lexicographic_sort(const char* a, const char* b) {
    return (strcmp(a, b) > 0);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return (strcmp(b, a) > 0);
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int char_map_a[26] = {0};
    int char_map_b[26] = {0};

    int disctint_chars_a = 0;
    int disctint_chars_b = 0;

    // ascii in range of 97-122, i can just subtract 97 (or (int) 'a') from the char to offset to 0
    for (int i = 0; i < strlen(a); i++) {
        if (char_map_a[(int) a[i] - 97] == 0) {
            char_map_a[(int) a[i] - 97] = 1;
            disctint_chars_a++;
        }
    }

    for (int i = 0; i < strlen(b); i++) {
        if (char_map_b[(int) b[i] - 97] == 0) {
            char_map_b[(int) b[i] - 97] = 1;
            disctint_chars_b++;
        }
    }

    // if the number of unique characters is the same, return lexicographic result
    if (disctint_chars_a == disctint_chars_b)
        return (strcmp(a, b) > 0);

    return (disctint_chars_a > disctint_chars_b);
}

int sort_by_length(const char* a, const char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);

    // if the number of total characters is the same, return lexicographic result
    if (len_a == len_b)
        return (strcmp(a, b) > 0);

    return (len_a > len_b);
}

void string_sort(char** arr, const int len, int (*cmp_func)(const char* a, const char* b)) {
    char* temp;

    // march through with two
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {

            // if arr[i] bigger
            if (cmp_func(arr[i], arr[j]) > 0) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// ------------------ code below is provide by the prompt ------------------

int main()
{
    int n;
    scanf("%d", &n);

    char** arr;
	arr = (char**)malloc(n * sizeof(char*));

    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }

    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
}
