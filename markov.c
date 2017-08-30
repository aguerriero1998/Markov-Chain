#include "markov.h"

void tokenize(FILE * input){
    //tokenized the input file into individual words
    
    char buff[255];
    char *token;

    while(fgets(buff, 255, input)){
        token = strtok(buff, " \t\n\r\v\f");
        while(token != NULL){
            if(num_words + 1 == word_array_size){
                grow_word_array();
            }
            char *ptr = (char *) malloc(strlen(token) * sizeof(char));
            strcpy(ptr, token);
            word_array[num_words] = ptr;
            num_words ++;
            token = strtok(NULL, " \t\n");
        }
    }

    

    return;
}

void grow_word_array(){
    word_array_size *= 2;
    word_array = (char **) realloc(word_array, word_array_size  * sizeof(char *));
}


void generate_n_grams(int n_grams){
    //total number of n_grams
    num_n_grams = num_words + 1 - n_grams;
    
    //n_grams is an array of arrays of strings size: number of n_grams * sizeof(array of strings)
    //sizeof(array of strings) == sizeof(char *) * number of words in each n gram
    n_gram_array = (n_gram *) malloc(num_n_grams * sizeof(char *) * n_grams);
    
    for(int index = 0; index < num_words; index ++){

        n_gram cur_n_gram = (n_gram) malloc( sizeof(char *) * n_grams);
        
        for(int ith_word = 0; ith_word < n_grams; ith_word++){
            if(index + n_grams - 1 >= num_words) break;
           
            char *str = word_array[index + ith_word];
            cur_n_gram[ith_word] = str;
        
        }
        n_gram_array[index] = cur_n_gram;
    }


    return;
}
