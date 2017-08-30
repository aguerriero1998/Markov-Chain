OBJS = main.o markov.o
TEST_OBJS = markov.o unit_tests.o Unity/src/unity.o
TEST = tests
CC = gcc
CFLAGS = -Wall -c
LFLAG = -Wall
TARGET = main

link: $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

tests: $(TEST_OBJS)
	$(CC) $(LFLAGS) $(TEST_OBJS) -o $(TEST)

unit_tests.o: unit_tests.c
	$(CC) $(CFLAGS) unit_tests.c

unity.o: Unity/src/unity.c Unity/src/unity.h
	$(CC) $(CFLAGS) Unity/src/unity.c

main.o: main.c markov.h
	$(CC) $(CFLAGS) main.c

markov.o: markov.c
	$(CC) $(CFLAGS) markov.c

clean:
	rm *.o	
