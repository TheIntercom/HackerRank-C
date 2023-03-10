/*
This prompt provides the includes, the triangle struct, and main with some driver code.

We are asked to sort 'n' number of triangles in ascending order based on their surface area.
The triangles are provided through STDIN as 'n' sets of 3 space separated numbers.

Sample input:
3
7 24 25
5 12 13
3 4 5

Sample output:
3 4 5
5 12 13
7 24 25
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

// ------------------ code above is provide by the prompt ------------------

float get_triangle_area(triangle tr) {
    // heron's formula
    float p = (tr.a + tr.b + tr.c) / 2.0;
    float s = sqrtf(p * (p - tr.a) * (p - tr.b) * (p - tr.c));

    return s;
}

void sort_by_area(triangle* tr, int n) {
    // funny bubble
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            float area_a = get_triangle_area(tr[j]);
            float area_b = get_triangle_area(tr[j + 1]);

            if (area_a > area_b) {
                triangle temp = tr[j];
                tr[j] = tr[j + 1];
                tr[j + 1] = temp;
            }
        }
    }
}

// ------------------ code below is provide by the prompt ------------------

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
