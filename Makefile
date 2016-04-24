CC = g++
LD = -lSDL2
OBJS = main.o game.o world.o

coolkidsrule.out: $(OBJS)
	$(CC) -o coolkidsrule.out $(OBJS) $(LD)

%.o: %.c %.h
	$(CC) $< $(LD)

clean:
	rm *.o *.out
