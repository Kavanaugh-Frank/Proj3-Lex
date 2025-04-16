all:pfig
pfig:prog.tab.c lex.yy.c parse_tree.h
	g++ -o pfig prog.tab.c -ll
prog.tab.c:prog.y parse_tree.h
	bison prog.y
	cat prog.tab.c | sed 's/  __attribute__ ((__unused__))/\/\/ /g' >temp.cc
	mv temp.cc prog.tab.c
lex.yy.c:prog.l
	flex prog.l
