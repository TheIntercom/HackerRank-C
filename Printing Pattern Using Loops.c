/*
This prompt provides the includes and main with minimal driver code.

We are asked to create a text pattern given a single number from STDIN.
The inner most cell of this pattern should be '1' where the walls further from
the center increasing in value until we reach 'n'.

Sample input:
5

Sample output:
5 5 5 5 5 5 5 5 5
5 4 4 4 4 4 4 4 5
5 4 3 3 3 3 3 4 5
5 4 3 2 2 2 3 4 5
5 4 3 2 1 2 3 4 5
5 4 3 2 2 2 3 4 5
5 4 3 3 3 3 3 4 5
5 4 4 4 4 4 4 4 5
5 5 5 5 5 5 5 5 5
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    // ------------------ code above is provide by the prompt ------------------

    int limit = ((2 * n) - 1); // maximum length and width of our square shaped pattern
    int current_num; // the delta for how much to remove from 'n' as we move towards the center

    for (int row = 0; row < limit; row++) {
        for (int col = 0; col < limit; col++) {
            // sets lower limit
            current_num = (row < col) ? row : col;

            // adjust relative to row
            // if lower limit beyond halfway point the delta should decrease in value
            current_num = (current_num < (limit - row)) ? current_num : (limit - row - 1);

            // now relative to column
            current_num = (current_num < (limit - col)) ? current_num : (limit - col - 1);

            printf("%d ", n - current_num);
        }

        printf("\n");
    }

    // ------------------ code below is provide by the prompt ------------------

    return 0;
}
