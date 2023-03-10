NAME=compiler.out
CC=gcc
CC_FLAGS=

all: build

build: parser.tab.c lexer.yy.c generator.o asm_printer.o
	$(CC) $(CC_FLAGS) -o $(NAME) parser.tab.c lex.yy.c generator.o asm_printer.o -lfl

parser.tab.c:
	bison -d -o parser.tab.c parser.y

lexer.yy.c:
	flex -o lex.yy.c lexer.flex

generator.o:
	$(CC) $(CC_FLAFS)-c -o generator.o ../src/generator.c
	
asm_printer.o:
	$(CC) $(CC_FLAFS)-c -o asm_printer.o ../src/asm_printer.c
	
clean:
	rm -f *.yy.c
	rm -f *.tab.*
	rm -f *.o
	rm -f compiler.out
