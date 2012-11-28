

CC = g++
CFLAGS = -c -Wall
LDFLAGS = -lSDL -lSDL_ttf
INC = -I/usr/include/SDL
SOURCES = main.cpp ball.cpp paddel.cpp world.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = pong

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(INC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXE)
