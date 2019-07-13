options = -Wall -pedantic -std=c++11
exercice = largeur
.PHONY : clean

defautl : labo11

labo11 : labo11.o 
	g++ -o labo11 labo11.o $(options)

test : labo11
	./labo11 | grep -A1 $(exercice)

labo11.o : lab11.cpp graphe.h
	g++ -o labo11.o -c lab11.cpp $(options)

clean : 
	rm -f labo11
	rm -f *.o
