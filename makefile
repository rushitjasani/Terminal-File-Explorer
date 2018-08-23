CC = g++
CFLAGS = -Wall -std=c++14
DEPS = myheader.h global.h
OBJ = global.o listdir.o enableNCanon.o main.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

term: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf *.o
