vpath %.cc ./src
vpath %.h ./src
vpath %.o ./out
vpath % ./out
vpath %.hpp ./lib
CC= g++ -std=c++11 -g

.PHONY: build rebuild run test clean
build: fs
rebuild: clean fs
run: fs
	./out/fs

fs: main.o FileSystem.o Dir.o File.o
	$(CC) -o ./out/fs ./out/main.o ./out/File.o ./out/Dir.o ./out/FileSystem.o

main.o: main.cc FileSystem.h
	$(CC) -c ./src/main.cc -o ./out/main.o

FileSystem.o: FileSystem.cc FileSystem.h
	$(CC) -c ./src/FileSystem.cc -o ./out/FileSystem.o

Dir.o: Dir.cc Dir.h
	$(CC) -c ./src/Dir.cc -o ./out/Dir.o

File.o: File.cc File.h
	$(CC) -c ./src/File.cc -o ./out/File.o

test: test.out
	./out/test.out

test.out: test.o FileSystem.o Dir.o File.o
	$(CC) -o ./out/test.out ./out/test.o ./out/File.o ./out/Dir.o ./out/FileSystem.o

test.o: test.cc
	$(CC) -c ./src/test.cc -o ./out/test.o

clean:
	rm ./out/* -r
