COMPILER = g++
COMPILER_FLAG = -std=c++20 -fmodules-ts

default: all

run: all
	./main.out

all: main.out

main.out:  module1.o module2.o module3.o main.o
	${COMPILER} $^ -o main.out

%.o: %.cpp gcm.cache
	${COMPILER} -c  ${COMPILER_FLAG} $<

gcm.cache:
	${COMPILER} -c  ${COMPILER_FLAG} -x c++-system-header iostream string

clean:
	@-rm main.out
	@-rm module1.o
	@-rm module2.o
	@-rm module3.o
	@-rm main.o
	@-rm -r gcm.cache
