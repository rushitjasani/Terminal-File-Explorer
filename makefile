CC = g++
CFLAGS = -Wall -std=c++14
DEPS = myheader.h global.h
OBJ = global.o SplitFilename.o copy_file_dir.o create_file_dir.o delete_file_dir.o move.o rename.o snapshot.o command_mode.o listdir.o enableNCanon.o main.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

term: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf *.o term
