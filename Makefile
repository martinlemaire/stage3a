#Makefile de l'executable test
all : SinglePoint Surface Benchmark AutoBench SysLin AndSimu autoRule

autoRule : ./Sources/autoRule.c
	gcc -g ./Sources/autoRule.c -o -lm autoRule

SinglePoint : ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/SinglePoint.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/Normalisation.o ./Objects/NormalValues.o ./Objects/SynthMin.o ./Objects/Synth.o
	gcc -g ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/SinglePoint.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/NormalValues.o ./Objects/Normalisation.o ./Objects/SynthMin.o ./Objects/Synth.o -lm -o SinglePoint

Surface : ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/Surface.o ./Objects/MainSurface.o ./Objects/Normalisation.o ./Objects/NormalValues.o
	gcc -g ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/Surface.o ./Objects/MainSurface.o ./Objects/Normalisation.o ./Objects/NormalValues.o -lm -o Surf

Benchmark : ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/Benchmark.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/Normalisation.o ./Objects/NormalValues.o
	gcc -g ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/Benchmark.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/NormalValues.o ./Objects/Normalisation.o -lm -o Bench

AutoBench : ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/AutoBench.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/Normalisation.o ./Objects/NormalValues.o ./Objects/MainAutoBench.o
	gcc -g ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/AutoBench.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/NormalValues.o ./Objects/Normalisation.o ./Objects/MainAutoBench.o -lm -o AutoBench

SysLin : ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/SysLin.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/Normalisation.o ./Objects/NormalValues.o ./Objects/SynthMin.o ./Objects/Synth.o
	gcc -g ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/SysLin.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/NormalValues.o ./Objects/Normalisation.o ./Objects/SynthMin.o ./Objects/Synth.o -lm -o SysLin

AndSimu : ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/AndSimu.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/Normalisation.o ./Objects/NormalValues.o 
	gcc -g ./Objects/Min_Fun.o ./Objects/CrossFun.o ./Objects/MaxFun.o ./Objects/AndSimu.o ./Objects/Centroid.o ./Objects/Fuzzy.o ./Objects/ProdFun.o ./Objects/NormalValues.o ./Objects/Normalisation.o -lm -o AndSimu

./Objects/SinglePoint.o : ./Sources/Min_Fun.c ./Sources/SinglePoint.c ./Sources/MaxFun.c ./Sources/Normalisation.c ./Sources/NormalValues.c
	gcc -g -c ./Sources/SinglePoint.c -o ./Objects/SinglePoint.o

./Objects/MainSurface.o: ./Sources/Fuzzy.c ./Sources/Surface.c
	gcc -g -c ./Sources/MainSurface.c -o ./Objects/MainSurface.o

./Objects/Fuzzy.o : ./Sources/Min_Fun.c ./Sources/MaxFun.c ./Sources/Centroid.c
	gcc -g -c ./Sources/Fuzzy.c -o ./Objects/Fuzzy.o

./Objects/Min_Fun.o : ./Sources/Min_Fun.c
	gcc -g -c ./Sources/Min_Fun.c -o ./Objects/Min_Fun.o

./Objects/MaxFun.o : ./Sources/MaxFun.c ./Sources/CrossFun.c
	gcc -g -c ./Sources/MaxFun.c -o ./Objects/MaxFun.o

./Objects/CrossFun.o : ./Sources/CrossFun.c
	gcc -g -c ./Sources/CrossFun.c -o ./Objects/CrossFun.o

./Objects/Centroid.o : ./Sources/Centroid.c
	gcc -g -c ./Sources/Centroid.c -o ./Objects/Centroid.o

./Objects/ProdFun.o : ./Sources/ProdFun.c
	gcc -g -c ./Sources/ProdFun.c -o ./Objects/ProdFun.o

./Objects/Normalisation.o : ./Sources/Normalisation.c
	gcc -g -c ./Sources/Normalisation.c -o ./Objects/Normalisation.o

./Objects/NormalValues.o : ./Sources/NormalValues.c
	gcc -g -c ./Sources/NormalValues.c -o ./Objects/NormalValues.o

./Objects/Synth.o : ./Sources/Synth.c ./Sources/SynthMin.c
	gcc -g -c ./Sources/Synth.c -o ./Objects/Synth.o

./Objects/SynthMin.o : ./Sources/SynthMin.c
	gcc -g -c ./Sources/SynthMin.c -o ./Objects/SynthMin.o

./Objects/Surface.o : ./Sources/Surface.c ./Sources/Fuzzy.c ./Sources/Normalisation.c ./Sources/NormalValues.c
	gcc -g -c ./Sources/Surface.c -o ./Objects/Surface.o

./Objects/Benchmark.o : ./Sources/Min_Fun.c ./Sources/MaxFun.c ./Sources/Normalisation.c ./Sources/NormalValues.c ./Sources/Benchmark.c
	gcc -g -c ./Sources/Benchmark.c -o ./Objects/Benchmark.o

./Objects/SysLin.o : ./Sources/Synth.c ./Sources/SynthMin.c ./Sources/SysLin.c ./Sources/MaxFun.c ./Sources/Normalisation.c ./Sources/NormalValues.c
	gcc -g -c ./Sources/SysLin.c -o ./Objects/SysLin.o

./Objects/AutoBench.o : ./Sources/Min_Fun.c ./Sources/MaxFun.c ./Sources/Normalisation.c ./Sources/NormalValues.c  ./Sources/AutoBench.c
	gcc -g -c ./Sources/AutoBench.c -o ./Objects/AutoBench.o

./Objects/MainAutoBench.o : ./Sources/MainAutoBench.c ./Sources/AutoBench.c
	gcc -g -c ./Sources/MainAutoBench.c -o ./Objects/MainAutoBench.o

./Objects/AndSimu.o : ./Sources/Fuzzy.c ./Sources/Normalisation.c ./Sources/NormalValues.c ./Sources/AndSimu.c
	gcc -g -c ./Sources/AndSimu.c -o ./Objects/AndSimu.o

# suppression des fichiers temporaires
clean:
	rm -rf ./Objects/*.o
 
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
	rm -rf SinglePoint Surf Bench AutoBench SysLin AndSimu autoRule
