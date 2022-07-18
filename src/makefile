output: main.o contactbst.o contact.o myvector.o myfunctions.o
	g++ main.o contactbst.o contact.o myvector.o myfunctions.o -o output
main.o: main.cpp 
	g++ -c main.cpp
contactbst.o:  contactbst.h contactbst.cpp
	g++ -c contactbst.cpp
contact.o: contact.h contact.cpp
	g++ -c contact.cpp
myvector.o: myvector.h myvector.cpp
	g++ -c myvector.cpp
myfunctions.o: myfunctions.h myfunctions.cpp
	g++ -c myfunctions.cpp

clean:
	rm main.o contactbst.o contact.o myvector.o myfunctions.o output
