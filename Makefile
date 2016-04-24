CC = g++
LDFLAGS = -lSDL2
CFLAGS = -std=c++11 -Wall
SOURCES = main.cc game.cc world.cc
OBJECTS = $(SOURCES:.cc=.o)
EXE = coolkidsrule.out

$(EXE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(CFLAGS)

%.o: 
	$(CC) -c $(CFLAGS) $(@:.o=.cc) -o $@ 

clean:
	rm *.o *.out
