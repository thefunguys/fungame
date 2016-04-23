lib = -lSDL2

coolkidsrule.out: main.o main.h
	g++ -o coolkidsrule.out $< $(lib)
%.o: %.c %.h
	g++  $<

clean:
	rm *.o *.out
