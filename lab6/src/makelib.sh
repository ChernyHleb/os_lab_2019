rm -f ModFact.o libModFact.a
gcc -o ModFact.o -c ModFact.c
ar rcs libModFact.a ModFact.o
rm -f ModFact.o