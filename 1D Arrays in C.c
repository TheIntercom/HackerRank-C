/*
This prompt provides the includes and an empty main.

We are asked to read a series of space separated numbers from STDIN with the first number being how many numbers to read
and print the sum to STDOUT.

Sample input:
6
16 13 7 2 1 12

Sample output:
51
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    // ------------------ code above is provide by the prompt ------------------

    int n = 0;
    int sum = 0;
    int v = 0;

    scanf("%d", &n); // cast the input as a decimal

    for (int i = 0; i < n; i++) {
        scanf("%d", &v); // implicitly filters the space
        sum += v;
    }

    printf("%d", sum);

    // ------------------ code below is provide by the prompt ------------------

    return 0;
}
