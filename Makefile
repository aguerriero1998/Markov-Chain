OBJS = main.o
CC = gcc
CFLAGS = -Wall -c
LFLAG = -Wall
TARGET = main

link: $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o  
