CC = g++
CFLAGS = -Wall -std=c++14
DEPS = myheader.h global.h
OBJ = listdir.o main.o global.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

term: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf *.o
