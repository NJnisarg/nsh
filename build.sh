yacc -d nsh.y
lex nsh.l
gcc lex.yy.c y.tab.c -o nsh