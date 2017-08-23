#include "main.h"
/* This program generates random text based on an input text using markov chains
 * The markov chain takes n-1 words to be the state and then selects a random word 
 * that was preceeded by the n-1 words in the input text
 * Usage: main n_grams input-file output-file
 *
 *
 */

void usage(char * file){
    printf("Usage: %s n-grams input-file output-file\n", file);
    printf(" Reads text from the input-file and will generate \n");
    printf(" an output file using a markov chain %s will override\n", file);
    printf(" an existing output file or make one if one does not exist");
    printf(" n-grams must be a positive integer negative or non integers\n");
    printf(" will not execute");
}


void grow_word_array(){
    word_array_size *= 2;
    word_array = (char **) realloc(word_array, word_array_size  * sizeof(char *));

}

void tokenize(FILE * input){
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
        //Get length to allocate for key
        for(int word = 0; word < n_grams - 1; word++) len += strlen(cur_n_gram[word]);
       
        char *key = malloc((len + n_grams-1 ) * sizeof(char));
        strcpy(key, cur_n_gram[0]);
        for(int word = 1; word < n_grams-1; word ++){
            key = strcat(key, " ");
            key = strcat(key, cur_n_gram[word]);
        }

        int hash_key = (int) hash(key);
        markov_chain *entry;
        HASH_FIND_INT(m_chain, &hash_key, entry);
        //Add entry if not found
        if(entry == NULL){
            
            entry = (markov_chain *) malloc(sizeof(markov_chain));
            (entry) -> cur_state = key;
            (entry) -> possible_next = (char **) malloc(sizeof(char *) * 30);
            (entry) -> cur_index = 0;
            (entry) -> possible_next[0] = cur_n_gram[n_grams - 1];
            (entry) -> hash_value = hash_key;

            HASH_ADD_INT(m_chain, hash_value ,entry);
        }else{
            //If found adds word to possible next
            (entry)-> cur_index ++;
            (entry) -> possible_next[(entry)->cur_index] = cur_n_gram[n_grams - 1];
        }
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

char * next_word(char * curr_state){
    int hash_key = (int) hash(curr_state);
    markov_chain *entry;
    HASH_FIND_INT(m_chain, &hash_key, entry);

	if(entry != NULL){
		int index = rand();
		index = index & entry->cur_index;
		return entry->possible_next[index];
	}
	return NULL;
}

char * random_state(){


	unsigned int num_states;
	num_states = HASH_COUNT(m_chain);

    if(num_states == 0){
        exit(-1);
    }

	int random = rand() % num_states;
	markov_chain *entry = m_chain;
	int i = 0;
	while(i < random){
		entry = entry->hh.next;
		i++;
	}
	return entry->cur_state;

}

void babble(FILE *output, unsigned int amount, char * state){
	if(amount % 20 == 0){ 
		fputs("\n", output);
	}
	if(amount == 0) return;

	char *next = next_word(state);
	if(next == NULL) return;

	fputs(next, output);
	fputs(" ", output);

	char *split = strchr(state ,' ');
	char *next_state = NULL;

	if(split){
		split ++;
		next_state = malloc((strlen(split) + 2 + strlen(next)) * sizeof(char));
		strcpy(next_state, split);
		strcat(next_state, " ");
		strcat(next_state, next);
	}else{
        next_state = malloc(strlen(next) * sizeof(char));
        strcpy(next_state, next);
	}
	free(state);
	amount = amount - 1;
	babble(output,amount,next_state);

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
    free(word_array);
    generate_markov_chain(n_grams);

	char * rand_words = random_state();
	babble(out, 3999,rand_words);
    fclose(out);


    return 0;
}
