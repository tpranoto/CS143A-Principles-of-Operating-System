CC = gcc
CFLAGS = -I.
PROGRAM = compute
INPUT = SampleInput

all: compute.c
	$(CC) -o $(PROGRAM) compute.c $(CFLAGS)

run: $(PROGRAM)
	./$(PROGRAM) < $(INPUT)

clean:
	rm $(PROGRAM)
