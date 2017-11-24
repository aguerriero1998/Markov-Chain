#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "uthash.h"

typedef char ** n_gram;

typedef struct{

    char * cur_state;
    char ** possible_next;
    int hash_value;
    int cur_index;
    UT_hash_handle hh;

}markov_chain;

markov_chain *m_chain; 

char **word_array;
int num_words;
int word_array_size;

n_gram *n_gram_array;
int num_n_grams;

void tokenize(FILE * corpus);
void grow_word_array();

void generate_n_grams(int n_grams);

unsigned long hash(char *str);
void generate_markov_chain(int n_grams);
void babble(FILE *out, unsigned int amount, char * state);
char * random_state();
char * next_word(char * curr_state);

char * copy_str(char *string);
void free_word_array();
void free_n_grams(int n_grams);
void free_markov_chain(int n_grams);
