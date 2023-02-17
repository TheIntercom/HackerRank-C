int sum(int count, ...) {
    va_list ptr;
    va_start(ptr, count);

    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += va_arg(ptr, int);
    }

    va_end(ptr);

    return sum;
}

int min(int count, ...) {
    va_list ptr;
    va_start(ptr, count);

    int min = 0;
    int temp;
    for (int i = 0; i < count; i++) {
        temp = va_arg(ptr, int);
        min = min < temp ? min : temp;
    }

    va_end(ptr);

    return min;
}

int max(int count, ...) {
    va_list ptr;
    va_start(ptr, count);

    int max = 0;
    int temp;
    for (int i = 0; i < count; i++) {
        temp = va_arg(ptr, int);
        max = max > temp ? max : temp;
    }

    va_end(ptr);

    return max;
}
