float get_triangle_area(triangle tr) {
    float p = (tr.a + tr.b + tr.c) / 2.0; // dividing by int returns int so we use a float
    float s = sqrtf(p * (p - tr.a) * (p - tr.b) * (p - tr.c));

    return s;
}

void sort_by_area(triangle* tr, int n) {
	/**
	* Sort an array a of the length n
	*/

    // lmao funny bubble
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
