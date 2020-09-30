cc=gcc
dir=obj/
DIR_RUN=Run/
OBJC=$(dir)vector.o $(dir)lex.yy.o $(dir)Grammar.tab.o $(dir)tree.o $(dir)Main_act.o
$(DIR_RUN)Grammar_run:$(OBJC) 
	gcc -o $@ $^ -g -Wall 
$(dir)vector.o:vector.c vector.h
	gcc -c -o $@ $< -g -Wall     
$(dir)lex.yy.o:lex.yy.c Grammar.tab.h 
	gcc -c -o $@ $< -g 
$(dir)Grammar.tab.o:Grammar.tab.c Grammar.tab.h vector.h tree.h Main_act.h
	gcc -c -o $@ $< -g -Wall 
$(dir)tree.o:tree.c tree.h
	gcc -c -o $@ $< -g -Wall 
$(dir)Main_act.o:Main_act.c Main_act.h 
	gcc -c -o $@ $< -g -Wall 
lex.yy.c:Grammar.l Grammar.tab.h Main_act.h
	flex Grammar.l
Grammar.tab.c Grammar.tab.h:Grammar.y Main_act.h
	bison -d Grammar.y -v #--debug 
clean:
	rm -rf lex.yy.c Grammar.tab.c Grammar.tab.h *.out *.output *.o Grammar_run Grammar.debug $(OBJC)
