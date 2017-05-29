CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

card1: cardtest1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o cardtest1.c -o cardtest1 -lm -g

card2: cardtest2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o cardtest2.c -o cardtest2 -lm -g

card3: cardtest3.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o cardtest3.c -o cardtest3 -lm -g

card4: cardtest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o cardtest4.c -o cardtest4 -lm -g

unit1: a5unittest1.c rngs.o dominion.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o a5unittest1.c -o a5unittest1 -lm -g

unit2: a5unittest2.c rngs.o dominion.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o a5unittest2.c -o a5unittest2 -lm -g

unit3: a5unittest3.c rngs.o dominion.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o a5unittest3.c -o a5unittest3 -lm -g

unit4: a5unittest4.c rngs.o dominion.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o a5unittest4.c -o a5unittest4 -lm -g

mytests: card1 card2 card3 card4 unit1 unit2 unit3 unit4

unittestresults.out: 
	echo "----------------------------- UNIT TESTS --------------------------" &> unittestresults.out
	./a5unittest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./a5unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./a5unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./a5unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo "----------------------------- END UNIT TESTS --------------------------------" >> unittestresults.out
	echo "----------------------------- CARD TESTS ------------------------------------" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo "----------------------------- END OF CARD TESTS -----------------------------" >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

rand_test_helper.o: rand_test_helper.c rand_test_helper.h
	gcc -c rand_test_helper.c -g $(CFLAGS)		
	
randadvcard: a5randomtestadventurer.c dominion.o rngs.o rand_test_helper.o
	gcc -o randadvcard -g a5randomtestadventurer.c dominion.o rngs.o rand_test_helper.o -std=c99 -fprofile-arcs -ftest-coverage -lm

randtestcard2: a5randomtestcard2.c dominion.o rngs.o rand_test_helper.o
	gcc -o randtestcard2 -g a5randomtestcard2.c dominion.o rngs.o rand_test_helper.o -std=c99 -fprofile-arcs -ftest-coverage -lm
		
randtestcard1: a5randomtestcard1.c dominion.o rngs.o rand_test_helper.o
	gcc -o randtestcard1 -g a5randomtestcard1.c dominion.o rngs.o rand_test_helper.o -std=c99 -fprofile-arcs -ftest-coverage -lm
	
a5randomtestcard1.out:
	echo "----------------------------------- RANDOM TEST CARD 1 ------------------------------------------------" &> a5randomtestcard1.out
	./randtestcard1 >> a5randomtestcard1.out
	gcov -b -f dominion.c >> a5randomtestcard1.out
	echo "----------------------------------- END OF RANDOM TEST CARD 1 -----------------------------------------" >> a5randomtestcard1.out

a5randomtestcard2.out:
	echo "----------------------------------- RANDOM TEST CARD 2 ------------------------------------------------" &> a5randomtestcard2.out
	./randtestcard2 >> a5randomtestcard2.out
	gcov -b -f dominion.c >> a5randomtestcard2.out
	echo "----------------------------------- END OF RANDOM TEST CARD 2 -----------------------------------------" >> a5randomtestcard2.out
	
a5randomtestadventurer.out:
	echo "----------------------------------- RANDOM TEST ADVENTURER ------------------------------------------------" &> a5randomtestadventurer.out
	./randadvcard >> a5randomtestadventurer.out
	gcov -b -f dominion.c >> a5randomtestadventurer.out
	echo "----------------------------------- END OF RANDOM ADVENTURER -----------------------------------------" >> a5randomtestadventurer.out

myrandomtests: randadvcard randtestcard1 randtestcard2
		
all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o *.exe playdom test player player.exe randtestcard1 randtestcard2 randadvcard rand_test_helper testInit *.gcov *.gcda *.gcno *.so a5unittest1 a5unittest2 a5unittest3 a5unittest4 cardtest1 cardtest2 cardtest3 cardtest4
