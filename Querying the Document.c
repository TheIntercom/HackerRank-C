/*
This prompt provides everything with the exception of several empty functions.

We are asked to complete the logic and operation of the following functions:
-- kth_word_in_mth_sentence_of_nth_paragraph : Getter function for a specific word.
-- kth_sentence_in_mth_paragraph : Getter function for specific sentence.
-- kth_paragraph : Getter function for specific paragraph.
-- get_document : Converts a char* into a char**** based on specific punctuation.

The driver code will read an input string as 'p' number of paragraphs, followed by 'q' number of digits for the queries.

Query Default: Specific paragraph. Further requests number of sentences.
Query 2: Specific sentence. Further requests how many words from the start of the sentence.
Query 3 : Specific word.

Sample input:
2
Lorem ipsum dolor sit amet consectetur adipiscing elit.
Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.Ut enim ad minim veniam quis nostrud.
3
1 2 2 5 6
2 1 1 4
3 1 1 1

Sample output:
Sed do eiusmod tempor incididunt.Ut enim ad minim veniam quis.
Lorem ipsum dolor sit
Lorem
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

// ------------------ code above is provide by the prompt ------------------

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) {
    return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

// helper function
char** string_split(char* text, char separator) {
    char** result = malloc(sizeof(char*));
    int token_count = 1; // always at least 1 token

    char* token = strtok(text, &separator);
    *result = token;

    while (token != NULL) {
        token_count++;

        result = realloc(result, sizeof(char*) * token_count);
        token = strtok(NULL, &separator); // NULL checks later use pointer
        result[token_count - 1] = token;
    }

    return result;
}

// helper function
int get_array_length(char** text) {
    int result = 0;

    // this NULL is placed manually at the end of our arrays
    while (text[result] != NULL) {
        result++;
    }

    return result;
}


// text comes in as one big string
char**** get_document(char* text) {
    char**** document = NULL;

    // separate on '\n' for each paragraph
    char** paragraphs = string_split(text, '\n');
    int paragraph_count = get_array_length(paragraphs);

    document = malloc(sizeof(char***) * (paragraph_count + 1));
    document[paragraph_count] = NULL; // set last index equal to NULL as a convention to help 'get_array_length' do some lifting for the user

    int i = 0;
    while (paragraphs[i] != NULL) {
        // separate on '.' for each sentence (no spaces afterwards to make it simpler for me i guess)
        char** sentences = string_split(paragraphs[i], '.');
        int sentence_count = get_array_length(sentences);

        document[i] = malloc(sizeof(char**) * (sentence_count + 1));
        document[i][sentence_count] = NULL;

        int j = 0;
        while (sentences[j] != NULL) {
            // separate on ' ' for each word
            document[i][j] = string_split(sentences[j], ' ');
            j++;
        }

        i++;
    }

    return document;
}

// ------------------ code below is provide by the prompt ------------------

char* get_input_text() {
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
}

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main()
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }
}
