// i wanted to try doing something different than the 4d string array from the other prompt

// handy shortcut i learned with realloc:
// "If ptr is NULL, the behavior is the same as calling malloc(new_size)."

struct document get_document(char* text) {
    // since every struct is essentially a 'word' wrapper it would make sense
    // to parse for words first then work up the chain
    struct document doc;

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
