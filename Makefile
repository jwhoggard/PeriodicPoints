CXXFLAGS =  -g -O3 -Wall -Wextra -Wuninitialized -pedantic -Wshadow -std=c++14


OBJS = Window.o testFunc testWindow cellTest seek testRootFinder

all: ${OBJS}

testFunc: func.o

cellTest: Window.o func.o

testWindow: Window.o func.o

Window.o: Window.h func.o

func.o: func.h

seek: Window.o func.o

RootFinder.o: RootFinder.h

testRootFinder: RootFinder.o


clean:
	rm -rf ${OBJS} *.o *.dSYM *~
