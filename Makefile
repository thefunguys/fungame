CC = g++
LDFLAGS = -lSDL2 -lGL
CFLAGS = -std=gnu++11
SOURCES = main.cc game.cc world.cc
OBJECTS = $(SOURCES:.cc=.o)
EXE = coolkidsrule.out

$(EXE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) $> -o $@ 

clean:
	rm *.o *.out
