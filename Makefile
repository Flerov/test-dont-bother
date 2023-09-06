CC = gcc

CFLAGS = -std=c17 -O3 -Wall -Wextra -pedantic

MAIN_BINARIES = $(basename $(wildcard *.c))

OBJECT = $(addsuffix .o, $(basename $(filter-out %Main.c, $(wildcard *.c))))

.PHONY: all compile clean

all: compile


compile: $(MAIN_BINARIES)


clean:
	rm -f *.o
	rm -f $(MAIN_BINARIES)


%Main: %Main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARIES)


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


