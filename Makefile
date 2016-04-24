CC = g++
LD = -lSDL2
OBJS = main.o game.o

coolkidsrule.out: $(OBJS)
	$(CC) -o coolkidsrule.out $(OBJS) $(LD)

%.o: %.c %.h
	$(CC) $<

clean:
	rm *.o *.out
