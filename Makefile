build:
	g++ -Wall main.cpp Image.cpp -o main.exe

main: main.o Image.o Image.h
	g++ main.o Image.o -o main.exe

main.o: main.cpp
	g++ -t -c main.cpp

Image.o: Image.h
	g++ -t -c Image.cpp
	
clean:
	rm -rf *.o main
