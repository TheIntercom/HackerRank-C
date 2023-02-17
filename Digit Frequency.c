#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char* input;
    input = malloc(sizeof(char) * 1024); // only needs 1000 but you know how it goes
    scanf("%s", input);

    int i = 0;
    int n = 0;

    int frequency_table[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    while (input[i] != NULL) {
        n = (int)input[i] - (int)'0'; // numbers are organized in ascii so we can just subtract '0' to get the difference

        if (n >= 0 && n <= 9) {
            // printf("%s ", int_lookup[n]);
            frequency_table[n] += 1;
        }

        i++;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", frequency_table[i]);
    }

    printf("\n");

    return 0;
}
