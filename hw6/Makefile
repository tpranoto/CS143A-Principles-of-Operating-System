CC = gcc
CFLAGS = -I.
PROGRAM = banker
INPUT = text_safe.txt

all: banker.c
	$(CC) -o $(PROGRAM) banker.c $(CFLAGS)

run: $(PROGRAM)
	./$(PROGRAM) < $(INPUT)

clean:
	rm $(PROGRAM)
