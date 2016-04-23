coolkidsrule.out: game.o game.h
	g++ -o coolkidsrule.out game.o
%.o: %.c %.h
	g++  $<

