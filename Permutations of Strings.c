#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char ** a, char ** b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/

    // maximum numbers of permutations is 'n!'
    // minus the first permutation and all duplicates

    int j = n - 1; // last index of array

    // move index towards start until we find an element that
    // breaks a descending sort
    while (j > 0 && strcmp(s[j - 1], s[j]) >= 0) {
        j--;
    }

    // already final permutation if the whole set is descending
    if (j <= 0) {
        return 0;
    }

    int k = n - 1; // new index

    // moves index towards start of suffix until we find an element
    // that breaks ascending order
    while (strcmp(s[k], s[j - 1]) <= 0) {
        k--;
    }

    // fix the descending sort
    swap(&s[k], &s[j - 1]);

    // then we reverse the rest of the elements in the suffix
    k = n - 1;
    while (j < k) {
        swap(&s[j], &s[k]);
        j++;
        k--;
    }

    return 1;
}
