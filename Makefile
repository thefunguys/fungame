CC = g++
LDFLAGS = -lSDL2 -lSDL2_image -lGL
CFLAGS = -std=c++11 -Wall
SOURCES = main.cc game.cc world.cc gameobject.cc player.cc sprite.cc keymap.cc split.cc bountry.cc


OBJECTS = $(SOURCES:.cc=.o)
EXE = coolkidsrule.out

$(EXE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(CFLAGS)

%.o: %.cc
	$(CC) -c $(CFLAGS) $(@:.o=.cc) -o $@ 

clean:
	rm *.o *.out
