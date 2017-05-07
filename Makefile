CC = g++
LDFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -ltmxlite
CFLAGS = -std=c++14 -Wall -J2 -I vendor/Selene/include
SOURCES = main.cc game.cc world.cc gameobject.cc player.cc sprite.cc keymap.cc boundary.cc shadermanager.cc rat.cc dialog.cc music.cc kid.cc bigredbutton.cc


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
