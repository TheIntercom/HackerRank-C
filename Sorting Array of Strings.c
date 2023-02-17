// strcmp:
// >0 'a' bigger
// <0 'b' bigger

// these sorts will try to follow something similar:
// 1 'a' bigger
// 0 'b' bigger

int lexicographic_sort(const char* a, const char* b) {
    return (strcmp(a, b) > 0);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return (strcmp(b, a) > 0);
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    // "The strings consists of lower-case English Alphabets only."
    // ascii in range of 97-122, i can just subtract 97 (or (int)'a') from the char
    // to map it to our arrays

    // all missing/undeclared elements are set to 0 in this compiler
    // so 0 for first element sets everything to 0
    int char_map_a[26] = {0};
    int char_map_b[26] = {0};

    int disctint_chars_a = 0;
    int disctint_chars_b = 0;

    for (int i = 0; i < strlen(a); i++) {
        if (char_map_a[(int)a[i] - 97] == 0) {
            char_map_a[(int)a[i] - 97] = 1;
            disctint_chars_a++;
        }
    }

    for (int i = 0; i < strlen(b); i++) {
        if (char_map_b[(int)b[i] - 97] == 0) {
            char_map_b[(int)b[i] - 97] = 1;
            disctint_chars_b++;
        }
    }

    if (disctint_chars_a == disctint_chars_b)
        return (strcmp(a, b) > 0);

    return (disctint_chars_a > disctint_chars_b);
}

int sort_by_length(const char* a, const char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);

    if (len_a == len_b)
        return (strcmp(a, b) > 0);

    return (len_a > len_b);
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)) {
    char* temp;

    // march through with two
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {

            // if arr[i] bigger
            if (cmp_func(arr[i], arr[j]) > 0) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
