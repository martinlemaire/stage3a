#Makefile de l'executable test

all : Min_Fun.o CrossFun.o MaxFun.o Myfun.o
	gcc -g Min_Fun.o CrossFun.o MaxFun.o Myfun.o -lm -o test

Myfun.o : Min_Fun.c Myfun.c 
	gcc -g -c Myfun.c -o Myfun.o

Min_Fun.o : Min_Fun.c
	gcc -g -c Min_Fun.c -o Min_Fun.o

MaxFun.o : MaxFun.c CrossFun.c
	gcc -g -c MaxFun.c -o MaxFun.o

CrossFun.o : CrossFun.c
	gcc -g -c CrossFun.c -o CrossFun.o

# suppression des fichiers temporaires
clean:
	rm -rf *.o
 
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
	rm -rf Programme
