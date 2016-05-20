CC = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -std=c++11 -Wall
SOURCES = main.cc game.cc world.cc gameobject.cc player.cc sprite.cc keymap.cc split.cc boundary.cc shadermanager.cc rat.cc


EXE = coolkidsrule.out
SRCDIR = src
OBJDIR = build
OBJECTS = $(SOURCES:%.cc=$(OBJDIR)/%.o)

$(EXE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm build/*.o
