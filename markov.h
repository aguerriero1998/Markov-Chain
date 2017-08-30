#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ** n_gram;

char **word_array;
int num_words;
int word_array_size;

n_gram *n_gram_array;
int num_n_grams;

void tokenize(FILE * corpus);
void grow_word_array();

void generate_n_grams(int n_grams);
