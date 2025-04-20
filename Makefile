YACC = bison -d
LEX = flex
CC = g++

YFILE = tree_builder.y
LFILE = tree_builder.l
YOUTPUT_C = tree_builder.tab.c
YOUTPUT_H = tree_builder.tab.h
LEX_OUTPUT = lex.yy.c
EXEC = tree_builder
SOURCE = source.txt

all: $(EXEC)

# one command to reset the project and test it using the source.txt
test: reset
	./${EXEC} ${SOURCE}

# one command to delete the old file and create more
reset: clean all

$(EXEC): $(YOUTPUT_C) $(LEX_OUTPUT)
	$(CC) -o $(EXEC) $(YOUTPUT_C) $(LEX_OUTPUT) -ll

$(YOUTPUT_C) $(YOUTPUT_H): $(YFILE)
	$(YACC) $(YFILE)

$(LEX_OUTPUT): $(LFILE)
	$(LEX) $(LFILE)

clean:
	rm -f $(YOUTPUT_C) $(YOUTPUT_H) $(LEX_OUTPUT) $(EXEC)
