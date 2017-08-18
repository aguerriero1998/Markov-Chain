#include "main.h"


void usage(char * file){
    printf("Usage: %s n-grams corpus-file output-file\n", file);
    printf(" Reads text from the corpus-file and will generate \n");
    printf(" an output file using a markov chain %s will override\n", file);
    printf(" an existing output file or make one if one does not exist");
    printf(" n-grams must be a positive integer negative or non integers\n");
    printf(" will not execute");
}


void grow_word_array(){
    word_array_size *= 2;
    word_array = (char **) realloc(word_array, word_array_size  * sizeof(char *));

}

void tokenize(FILE * corpus){
    char buff[255];
    char *token;

    while(fgets(buff, 255, corpus)){
        token = strtok(buff, " \t\n");
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

void generate_markov_chain(int n_grams){
    
    for(int i = 0; i < num_n_grams; i++){
        n_gram cur_n_gram = n_gram_array[i];
        int len = 0;
        for(int word = 0; word < n_grams - 1; word++) len += strlen(cur_n_gram[word]);
       
        char *key = malloc((len + n_grams-1 ) * sizeof(char));
        strcpy(key, cur_n_gram[0]);
        for(int word = 1; word < n_grams-1; word ++){
            key = strcat(key, " ");
            key = strcat(key, cur_n_gram[word]);
        }
        int hash_key = (int) hash(key);
        printf("String: %s\n",key);
        markov_chain *entry;
        HASH_FIND_INT(m_chain, &hash_key, entry);

        if(entry == NULL){
            printf("Not found. Adding to table\n");
            
            entry = (markov_chain *) malloc(sizeof(markov_chain));
            (entry) -> cur_state = key;
            (entry) -> possible_next = (char **) malloc(sizeof(char *) * 30);
            (entry) -> cur_index = 0;
            (entry) -> possible_next[0] = cur_n_gram[n_grams - 1];
            (entry) -> hash_value = hash_key;

            HASH_ADD_INT(m_chain, hash_value ,entry);
        }else{
            printf("Found %s!\n",(entry)->cur_state);
            (entry)-> cur_index ++;
            (entry) -> possible_next[(entry)->cur_index] = cur_n_gram[n_grams - 1];
            for(i = 0; i<= (entry)->cur_index ; i++){
                printf("%s ",entry->possible_next[i]);
            }
            printf("\n");
        }
        
            printf("\n");
    }

}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 
    return hash;
}

int main(int argc, char ** argv){
    
    if(argc != 4){
        printf("Not enough inputs\n");
        usage(argv[0]);
    }
    
    int n_grams = atoi(argv[1]);
    if(n_grams <= 1){
        printf("%s is not a valid input\n",argv[1]);
        usage(argv[0]);
    }
    FILE *in = fopen(argv[2],"r");
    FILE *out = fopen(argv[3], "w+");

    if(in == NULL){
        printf("The file %s was not found\n", argv[2]);
        usage(argv[0]);
    }
    word_array_size = 200;
    word_array = (char **) malloc(word_array_size * sizeof(char *));
    num_words = 0;

    tokenize(in);
    generate_n_grams(n_grams);
    free(word_array);
    generate_markov_chain(n_grams);

    return 0;
}
