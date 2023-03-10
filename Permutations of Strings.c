/*
This prompt provides the includes and main with some driver code.

We are asked to manipulate a lexicographically ordered string array (char**) into all unique permutations.
The 'next_permutation' function should 'return 1' if there are more permutations left to configure and
'return 0' once we reach the final permuation.

Sample input:
3
a
bc
bc

Sample output:
a bc bc
bc a bc
bc bc a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------ code above is provide by the prompt ------------------

// helper function to swap the address of two strings
void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

int next_permutation(int n, char** s) {
    int j = n - 1; // last index of array

    // strcmp wants smaller string towards end of array
    // move j towards 0 to get position of the first string that breaks a descending sort
    while (j > 0 && strcmp(s[j - 1], s[j]) >= 0) {
        j--;
    }

    // already final permutation if the whole set is in descending order
    if (!j)
        return 0;

    int k = n - 1; // last index again

    // move k towards j - 1 to get position of the second string that breaks a descending sort
    while (strcmp(s[j - 1], s[k]) >= 0) {
        k--;
    }

    // fix the descending sort
    swap(&s[j - 1], &s[k]);

    k = n - 1; // one last time

    // then reverse the order of all the elements after j for next permutation
    while (j < k) {
        swap(&s[j], &s[k]);
        j++;
        k--;
    }

    return 1;
}

// ------------------ code below is provide by the prompt ------------------

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
