#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

  	// Complete the code to print the pattern.
    int limit = ((2 * n) - 1);

    for (int row = 0; row < limit; row++) {
        for (int col = 0; col < limit; col++) {
            int current_num = row < col ? row : col; // sets lower limit
            current_num = current_num < (limit - row) ? current_num : (limit - row - 1); // filter relative to current row
            current_num = current_num < (limit - col - 1) ? current_num : (limit - col - 1); // filter relative to current col

            printf("%d ", n - current_num);
        }

        printf("\n");
    }

    return 0;
}
