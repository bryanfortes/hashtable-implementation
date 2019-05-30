main.x: passserver.o main.o
	g++ -std=c++11 -o main.x main.o passserver.o -lcrypt

passserver.o: passserver.h passserver.cpp hashtable.h hashtable.hpp
	g++ -std=c++11 -c passserver.cpp

main.o: passserver.h hashtable.h main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o
	rm *.x
