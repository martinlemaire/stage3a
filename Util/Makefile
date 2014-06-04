#Makefile pour Util

all : formatage RuleChanger LibFormat

formatage : formatage.c
	gcc formatage.c -o formatage

RuleChanger : RuleChanger.c
	gcc RuleChanger.c -o RuleChanger -lm

LibFormat : LibFormat.c
	gcc LibFormat.c -o LibFormat

mrproper : 
	rm -rf LibFormat RuleChanger formatage
