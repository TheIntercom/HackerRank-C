int main()
{
    int total_number_of_shelves;
    scanf("%d", &total_number_of_shelves);

    int total_number_of_queries;
    scanf("%d", &total_number_of_queries);

    // the prompt led me to believe that i wasn't supposed to be writing out here
    // but once i took a look at what code was actually written for me it all fell into place
    total_number_of_books = (int*) malloc(sizeof(int) * total_number_of_shelves);
    total_number_of_pages = (int**) malloc(sizeof(int*) * total_number_of_shelves);
    for (int i = 0; i < total_number_of_shelves; i++) {
        total_number_of_books[i] = 0;
        total_number_of_pages[i] = (int*) malloc(sizeof(int));
    }

    while (total_number_of_queries--) {
        int type_of_query;
        scanf("%d", &type_of_query);

        if (type_of_query == 1) {
            // Process the query of first type here.
            // x: shelf
            // y: pages
            int x, y;
            scanf("%d %d", &x, &y);

            // the first index of 'total_number_of_pages' is the shelf that holds the book
            // the second index would be the books that holds the pages (at least the page count)
            total_number_of_books[x] += 1; // increase the number of books on shelf 'x'

            int books_on_shelf = total_number_of_books[x];
            total_number_of_pages[x] = (int*) realloc(total_number_of_pages[x], sizeof(int) * (books_on_shelf)); // change size of shelf to hold 'books_on_shelf' amount of books
            total_number_of_pages[x][books_on_shelf - 1] = y; // 0 is a valid shelf/book, set it to page count
