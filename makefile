cc = gcc
OBJC= lex.yy.o Grammar.tab.o vector.o tree.o
Grammar_run:$(OBJC) 
	gcc -o $@ $^ -g -Wall 
vector.o:vector.c vector.h
	gcc -c $< -g -Wall
lex.yy.o:lex.yy.c Grammar.tab.h
	gcc -c  $< -g 
Grammar.tab.o:Grammar.tab.c Grammar.tab.h vector.h tree.h
	gcc -c  $< -g 
tree.o:tree.c tree.h
	gcc -c  $< -g -Wall
lex.yy.c:Grammar.l Grammar.tab.h
	flex Grammar.l
Grammar.tab.c Grammar.tab.h:Grammar.y
	bison -d Grammar.y -v #--debug 
clean:
	rm -rf lex.yy.c Grammar.tab.c Grammar.tab.h *.out *.output *.o Grammar_run Grammar.debug
