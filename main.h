#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"

typedef char ** n_gram;

typedef struct{
    char * cur_state;
    char ** possible_next;
    int hash_value;
    int cur_index;
    UT_hash_handle hh;
}markov_chain;

markov_chain *m_chain = NULL; 

char **word_array;
int num_words;
int word_array_size;

n_gram *n_gram_array;
int num_n_grams;


int main(int argc, char ** argv);
void usage(char *file);
void tokenize(FILE * corpus);
void generate_n_grams(int n_grams);
unsigned long hash(char *str);
void generate_markov_chain(int n_grams);
