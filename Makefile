objects = tennis.o lex.yy.o

tennis: $(objects)
	gcc -o tennis $(objects)


lex.yy.o : lex.yy.c tennis.h
	gcc -c lex.yy.c

tennis.o : tennis.c tennis.h 
	gcc -c tennis.c
	
lex.yy.c : tennis.lex
	flex tennis.lex
	
clean :
	rm $(objects) lex.yy.c tennis


	


	


