/*
This prompt provides some global variables and some driver code in main.

We are asked to complete the 'type_of_query == 1' section of the query loop in main which is intended to
dynamically store information about books as they are streamed in.
We are given the number of shelves, number of queries, and the queries from STDIN.

The generalized expected format: shelf[x].book[y].page_count

If the driver code can access the expected information from our bookshelf (dynamic array), then we succeed.

Sample input:
5
5
1 0 15
1 0 20
1 2 78
2 2 0
3 0

Sample output:
78
2
*/

#include <stdio.h>
#include <stdlib.h>

/*
 * This stores the total number of books in each shelf.
 */
int* total_number_of_books;

/*
 * This stores the total number of pages in each book of each shelf.
 * The rows represent the shelves and the columns represent the books.
 */
int** total_number_of_pages;

int main()
{
    int total_number_of_shelves;
    scanf("%d", &total_number_of_shelves);

    int total_number_of_queries;
    scanf("%d", &total_number_of_queries);

    // ------------------ code above is provide by the prompt ------------------

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
            // x: shelf
            // y: pages
            int x, y;
            scanf("%d %d", &x, &y);

            // the first index of 'total_number_of_pages' is the shelf that holds the book
            // the second index would be the books that holds the pages (at least the page count)
            total_number_of_books[x]++; // increase the number of books on shelf 'x'

            int books_on_shelf = total_number_of_books[x];
            total_number_of_pages[x] = (int*) realloc(total_number_of_pages[x], sizeof(int) * (books_on_shelf)); // change size of shelf to hold 'books_on_shelf' amount of books
            total_number_of_pages[x][books_on_shelf - 1] = y; // 0 is a valid shelf/book, set it to page count

            // ------------------ code below is provide by the prompt ------------------

        } else if (type_of_query == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", *(*(total_number_of_pages + x) + y));
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", *(total_number_of_books + x));
        }
    }

    if (total_number_of_books) {
        free(total_number_of_books);
    }

    for (int i = 0; i < total_number_of_shelves; i++) {
        if (*(total_number_of_pages + i)) {
            free(*(total_number_of_pages + i));
        }
    }

    if (total_number_of_pages) {
        free(total_number_of_pages);
    }

    return 0;
}
