#include "markov.h"

/* This program generates random text based on an input text using markov chains
 * The markov chain takes n-1 words to be the state and then selects a random word 
 * that was preceeded by the n-1 words in the input text
 * Usage: main n_grams input-file output-file
 */

void usage(char * file){
    printf("Usage: %s n-grams input-file output-file\n", file);
    printf(" Reads text from the input-file and will generate \n");
    printf(" an output file using a markov chain %s will override\n", file);
    printf(" an existing output file or make one if one does not exist");
    printf(" n-grams must be a positive integer negative or non integers\n");
    printf(" will not execute");
}


int main(int argc, char ** argv){
    
    if(argc != 4){
        printf("Not enough inputs\n");
        usage(argv[0]);
        exit(-1);
    }

	srand((unsigned) time(NULL));
    
    int n_grams = atoi(argv[1]);
    if(n_grams <= 1){
        printf("%s is not a valid input\n",argv[1]);
        usage(argv[0]);
        exit(-1);
    }

    FILE *in = fopen(argv[2],"r");
    FILE *out = fopen(argv[3], "w+");

    if(in == NULL){
        printf("The file %s was not found\n", argv[2]);
        usage(argv[0]);
        exit(-1);
    }

    word_array_size = 200;
    word_array = (char **) malloc(word_array_size * sizeof(char *));
    num_words = 0;


    tokenize(in);
    fclose(in);
    if(num_words < n_grams) exit(-1);
    generate_n_grams(n_grams);
    free_word_array();
    generate_markov_chain(n_grams);
    //free_n_grams(n_grams);

	char * rand_words = random_state();

	babble(out, 3999, rand_words);

    fclose(out);
    
    return 0;
}
