CXXFLAGS =  -g -O3 -Wall -Wextra -Wuninitialized -pedantic -Wshadow -std=c++14


OBJS = Window.o testFunc testWindow

all: ${OBJS}

testFunc: func.o

testWindow: Window.o

Window.o: Window.h

func.o: func.h


clean:
	rm -rf ${OBJS} *.o *.dSYM *~
