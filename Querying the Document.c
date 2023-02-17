// the constraints mention the paragraph input cannot be 0
// but neglects to mention the same for sentences or words
// adding '- 1' to everything here just works
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
    int token_count = 1; // always going to be at least 1 token

    char* token = strtok(text, &separator);
    *result = token;

    while (token != NULL) {
        token_count++;
        result = realloc(result, sizeof(char*) * token_count);
        token = strtok(NULL, &separator);
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
