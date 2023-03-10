/*
This prompt provides the includes and a main with some driver code.

We are asked to simply reverse the order of a supplied array of integers.

Sample input:
6
16 13 7 2 1 12

Sample output:
12 1 2 7 13 16
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, *arr, i;
    scanf("%d", &num);
    arr = (int*) malloc(num * sizeof(int));
    for(i = 0; i < num; i++) {
        scanf("%d", arr + i);
    }

    // ------------------ code above is provide by the prompt ------------------

    int temp = 0;
    int last = (num - 1);

    for (int i = 0; i < (num / 2); i++) {
        temp = arr[i];
        arr[i] = arr[last];
        arr[last] = temp;
        last--;
    }

    // ------------------ code below is provide by the prompt ------------------

    for(i = 0; i < num; i++)
        printf("%d ", *(arr + i));
    return 0;
}
