#include "markov.h"
#include "Unity/src/unity.h"




void test_tokenize(){
    char * tokenized[] = {"This", "is", "a", "string", "to", "test", "n-gram", "markov", "chain", "word", "predition", "on"};

    FILE * test_input = fopen("test.txt", "r");

    if(test_input == 0){
        printf("Test file not found. Aborting test.\n");
        return;
    }
    
    word_array_size = 5; // word array dynamically grows
    word_array = (char **) malloc(word_array_size * sizeof(char *));
    num_words = 0;

    tokenize(test_input);

    TEST_ASSERT_EQUAL_INT(12, num_words);
    TEST_ASSERT_EQUAL_STRING_ARRAY( tokenized, word_array, num_words );

    fclose(test_input);

}

void test_n_grams(){
    char * expected_array[] = {"This", "is", "a",
                             "is", "a", "string", 
                             "a", "string", "to", 
                             "string", "to", "test",
                             "to", "test", "n-gram",
                             "test", "n-gram", "markov",
                             "n-gram", "markov", "chain",
                             "markov", "chain", "word",
                             "chain", "word", "predition",
                             "word", "predition", "on"};

    FILE * test_input = fopen("test.txt", "r");

    if(test_input == 0){
        printf("Test file not found. Aborting test.\n");
        return;
    }

    generate_n_grams(3);

    TEST_ASSERT_EQUAL_INT(10, num_n_grams);

    for(int i = 0; i < num_n_grams; i++){
        TEST_ASSERT_EQUAL_STRING_ARRAY( expected_array + 3 * (i), n_gram_array[i], 3 );
    }

}

int main(){


    UNITY_BEGIN();
    RUN_TEST(test_tokenize);
    RUN_TEST(test_n_grams);
    UNITY_END();

}


