# Makefile for YACC + LEX project

# Tools
YACC = bison -d
LEX = flex
CC = g++

# Files
YFILE = tree_builder.y
LFILE = tree_builder.l
YOUTPUT_C = tree_builder.tab.c
YOUTPUT_H = tree_builder.tab.h
LEX_OUTPUT = lex.yy.c
EXEC = tree_builder

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(YOUTPUT_C) $(LEX_OUTPUT)
	$(CC) -o $(EXEC) $(YOUTPUT_C) $(LEX_OUTPUT) -ll

# Generate C files from YACC
$(YOUTPUT_C) $(YOUTPUT_H): $(YFILE)
	$(YACC) $(YFILE)

# Generate C file from LEX
$(LEX_OUTPUT): $(LFILE)
	$(LEX) $(LFILE)

# Clean up
clean:
	rm -f $(YOUTPUT_C) $(YOUTPUT_H) $(LEX_OUTPUT) $(EXEC)
