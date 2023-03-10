/*
This prompt provides the includes and main with some driver code.

We are asked to print each word of a space separated string received from STDIN.

Sample input:
Lorem ipsum dolor sit amet

Sample output:
Lorem
ipsum
dolor
sit
amet

*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    char *s;
    s = malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);
    s = realloc(s, strlen(s) + 1);

    // ------------------ code above is provide by the prompt ------------------

    char* token = strtok(s, " "); // get pointer for first word after space

    while (token != NULL) {
        printf("%s\n", token);

        token = strtok(NULL, " "); // tokenize by space, checking NULL uses the previous pointer
    }

    // ------------------ code below is provide by the prompt ------------------

    return 0;
}
