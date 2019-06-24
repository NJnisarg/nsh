all: build install

build:	
	yacc -d nsh.y
	lex nsh.l
	gcc lex.yy.c y.tab.c -o nsh

install: nsh
	sudo cp nsh /bin/nsh

clean: lex.yy.c y.tab.h y.tab.c nsh
	rm lex.yy.c
	rm y.tab.h
	rm y.tab.c
	rm nsh
	sudo rm /bin/nsh
