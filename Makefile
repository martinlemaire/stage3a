#Makefile de l'executable test

SinglePoint : Min_Fun.o CrossFun.o MaxFun.o SinglePoint.o Centroid.o Fuzzy.o ProdFun.o Normalisation.o NormalValues.o SynthMin.o Synth.o
	gcc -g Min_Fun.o CrossFun.o MaxFun.o SinglePoint.o Centroid.o Fuzzy.o ProdFun.o NormalValues.o Normalisation.o SynthMin.o Synth.o -lm -o SinglePoint

Surface : Min_Fun.o CrossFun.o MaxFun.o Centroid.o Fuzzy.o ProdFun.o Surface.o MainSurface.o Normalisation.o NormalValues.o
	gcc -g Min_Fun.o CrossFun.o MaxFun.o Centroid.o Fuzzy.o ProdFun.o Surface.o MainSurface.o Normalisation.o NormalValues.o -lm -o Surf

Benchmark : Min_Fun.o CrossFun.o MaxFun.o Benchmark.o Centroid.o Fuzzy.o ProdFun.o Normalisation.o NormalValues.o
	gcc -g Min_Fun.o CrossFun.o MaxFun.o Benchmark.o Centroid.o Fuzzy.o ProdFun.o NormalValues.o Normalisation.o -lm -o Bench

SysLin : Min_Fun.o CrossFun.o MaxFun.o SysLin.o Centroid.o Fuzzy.o ProdFun.o Normalisation.o NormalValues.o SynthMin.o Synth.o
	gcc -g Min_Fun.o CrossFun.o MaxFun.o SysLin.o Centroid.o Fuzzy.o ProdFun.o NormalValues.o Normalisation.o SynthMin.o Synth.o -lm -o SysLin

SinglePoint.o : Min_Fun.c SinglePoint.c MaxFun.c Normalisation.c NormalValues.c
	gcc -g -c SinglePoint.c -o SinglePoint.o

MainSurface.o: Fuzzy.c Surface.c
	gcc -g -c MainSurface.c -o MainSurface.o

Fuzzy.o : Min_Fun.c MaxFun.c Centroid.c
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

Normalisation.o : Normalisation.c
	gcc -g -c Normalisation.c -o Normalisation.o

NormalValues.o : NormalValues.c
	gcc -g -c NormalValues.c -o NormalValues.o

Synth.o : Synth.c SynthMin.c
	gcc -g -c Synth.c -o Synth.o

SynthMin.o : SynthMin.c
	gcc -g -c SynthMin.c -o SynthMin.o

Surface.o : Surface.c Fuzzy.c Normalisation.c NormalValues.c
	gcc -g -c Surface.c -o Surface.o

Benchmark.o : Min_Fun.c MaxFun.c Normalisation.c NormalValues.c Benchmark.c
	gcc -g -c Benchmark.c -o Benchmark.o

SysLin.o : Synth.c SynthMin.c SysLin.c MaxFun.c Normalisation.c NormalValues.c
	gcc -g -c SysLin.c -o SysLin.o

# suppression des fichiers temporaires
clean:
	rm -rf *.o
 
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
	rm -rf Programme
