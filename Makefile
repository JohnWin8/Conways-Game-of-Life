CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -L/usr/X11R6/lib 
EXEC = a4q4
OBJECTS = cell.o main.o grid.o window.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

