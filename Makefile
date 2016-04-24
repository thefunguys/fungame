CC = g++
LD = -lSDL2
OBJS = main.o game.o

coolkidsrule.out: $(OBJS)
	g++ -o coolkidsrule.out $(OBJS) $(LD)

%.o: %.c %.h
	g++ $<

clean:
	rm *.o *.out
