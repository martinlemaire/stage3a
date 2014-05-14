#Makefile de l'executable test

all : Min_Fun.o CrossFun.o MaxFun.o Centroid.o Fuzzy.o ProdFun.o Surface.o MainSurface.o
	gcc -g Min_Fun.o CrossFun.o MaxFun.o Centroid.o Fuzzy.o ProdFun.o Surface.o MainSurface.o -lm -o Surface

MainSurface.o: Fuzzy.c Surface.c
	gcc -g -c MainSurface.c -o MainSurface.o
	
Fuzzy.o : Min_Fun.c MaxFun.c Centroid.c ProdFun.c
	gcc -g -c Fuzzy.c -o Fuzzy.o

Min_Fun.o : Min_Fun.c
	gcc -g -c Min_Fun.c -o Min_Fun.o

MaxFun.o : MaxFun.c CrossFun.c
	gcc -g -c MaxFun.c -o MaxFun.o

CrossFun.o : CrossFun.c
	gcc -g -c CrossFun.c -o CrossFun.o

Centroid.o : Centroid.c
	gcc -g -c Centroid.c -o Centroid.o

ProdFun.o : ProdFun.c
	gcc -g -c ProdFun.c -o ProdFun.o

Surface.o : Surface.c  Fuzzy.c
	gcc -g -c Surface.c -o Surface.o

# suppression des fichiers temporaires
clean:
	rm -rf *.o
 
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
	rm -rf Programme

