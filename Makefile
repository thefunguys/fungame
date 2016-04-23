lib = -lSDL2
objs = main.o game.o

coolkidsrule.out: $(objs)
	g++ -o coolkidsrule.out $(objs) $(lib)
%.o: %.c %.h
	g++  $<

clean:
	rm *.o *.out
