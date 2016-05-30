vpath %.cc ./src
vpath %.o ./out
vpath % ./out
vpath %.hpp ./lib

.PHONY: build test



test: test.out
	./out/test.out

test.out: test.o
	clang++ -o ./out/test.out ./out/test.o

test.o: test.cc
	clang++ -c ./src/test.cc -o ./out/test.o

.PHONY:clean
clean:
	rm ./out/* -r
