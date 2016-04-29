CC = g++
LDFLAGS = -lSDL2 -lGL
CFLAGS = -std=c++11 -Wall
SOURCES = main.cc game.cc world.cc gameobject.cc

OBJECTS = $(SOURCES:.cc=.o)
EXE = coolkidsrule.out

$(EXE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $> -o $@ 

clean:
	rm *.o *.out
