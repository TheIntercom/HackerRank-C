/*
This prompt provides the includes and an empty main.

We are asked to count the number of times a digit (0-9) appears in a supplied string
and print the results, separated by spaces.

Sample input:
a11472o5t6

Sample output:
0 2 1 0 1 1 1 1 0 0
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    // ------------------ code above is provide by the prompt ------------------

    char* input = malloc(sizeof(char) * 1024); // only needs 1000 but you know how it goes
    scanf("%s", input);

    int i = 0;
    int n = 0;

    int frequency_table[10] = {0};

    while (input[i]) {
        n = (int) input[i] - (int) '0'; // numbers are organized in ascii so we can just subtract '0' to get the difference

        if (n >= 0 && n <= 9)
            frequency_table[n]++;

        i++;
    }

    for (int i = 0; i < 10; i++)
        printf("%d ", frequency_table[i]);

    printf("\n");

    // ------------------ code below is provide by the prompt ------------------

    return 0;
}
