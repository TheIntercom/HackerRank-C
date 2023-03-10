/*
This prompt provides the includes, the structs, and other functions with driver code.

We are asked to complete the logic and operation of the following functions:
-- word.kth_word_in_mth_sentence_of_nth_paragraph : Getter function for a specific word.
-- sentence.kth_sentence_in_mth_paragraph : Getter function for specific sentence.
-- paragraph.kth_paragraph : Getter function for specific paragraph.
-- document.get_document : Converts a char* into a document object based on specific punctuation.

The driver code will read an input string as 'p' number of paragraphs, followed by 'q' number of digits for the queries.

Query Default: Specific paragraph.
Query 2: Specific sentence.
Query 3 : Specific word.

Sample input:
2
Lorem ipsum dolor sit amet consectetur adipiscing elit.
Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.Ut enim ad minim veniam quis nostrud.
3
1 2
2 1 1
3 1 1 1

Sample output:
Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.Ut enim ad minim veniam quis nostrud.
Lorem ipsum dolor sit amet consectetur adipiscing elit
Lorem
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

// ------------------ code above is provide by the prompt ------------------

struct document get_document(char* text) {

    struct document doc;

    // realloc note -> "If ptr is NULL, the behavior is the same as calling malloc(new_size)."
    struct paragraph* current_paragraph = NULL;
    struct sentence* current_sentence = NULL;
    struct word* current_word = NULL;

    doc.data = NULL;
    doc.paragraph_count = 0;

    int start = 0;
    int end = 0;

    for (int i = 0; i < strlen(text); i++) {
        end = i;

        // ' ' (or '.') means we need a new word
        if (text[i] == ' ' || text[i] == '.') {
            if (current_paragraph == NULL) {
                doc.paragraph_count++;
                doc.data = (struct paragraph*) realloc(doc.data, sizeof(struct paragraph) * doc.paragraph_count);

                current_paragraph = doc.data + doc.paragraph_count - 1; // set the offset
                current_paragraph->data = NULL;
                current_paragraph->sentence_count = 0;

                current_sentence = NULL; // new paragraph means new sentence
            }

            if (current_sentence == NULL) {
                current_paragraph->sentence_count++;
                current_paragraph->data = (struct sentence*) realloc(current_paragraph->data, sizeof(struct sentence) * current_paragraph->sentence_count);

                current_sentence = current_paragraph->data + current_paragraph->sentence_count - 1;
                current_sentence->data = NULL;
                current_sentence->word_count = 0;
            }

            current_sentence->word_count++;
            current_sentence->data = (struct word*) realloc(current_sentence->data, sizeof(struct word) * current_sentence->word_count);

            current_word = current_sentence->data + current_sentence->word_count - 1;
            current_word->data = NULL;
            current_word->data = (char*) realloc(current_word->data, sizeof(char) * (end - start + 1)); // +1 for null terminator (size)

            memcpy(current_word->data, text + start, end - start); // copy our substring, -1 because we overwrite this manually (size)
            current_word->data[end - start] = '\0'; // end the substring, -1 because this is an index, not a size
            current_word = NULL; // prepare for next word

            start = end + 1; // start cursor needs to be moved over the ' ' or '.'

            // '.' means we need a new sentence
            if (text[i] == '.') {
                current_sentence = NULL;
            }
        }

        // '\n' means we need a new paragraph
        if (text[i] == '\n') {
            start++; // start cursor needs to be moved over the '\n'

            current_sentence = NULL;
            current_paragraph = NULL;
        }
    }

    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) {
    return Doc.data[m - 1].data[k - 1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1];
}

// ------------------ code below is provide by the prompt ------------------

void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

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

int main()
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }
}
