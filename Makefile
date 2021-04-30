CC = g++
CFLAGS = -O3 -Wall
CPPFILE = uciyuki.cpp
OUTFILE = uciyuki

all:
	$(CC) $(CPPFILE) $(CFLAGS) -o $(OUTFILE)

clean:
	rm $(OUTFILE)