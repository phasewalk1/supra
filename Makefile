saleen: main.o new.o
		g++ -std=c++17 -o saleen src/main.o src/new.o

main.o: src/main.cpp src/new.hpp
		g++ -std=c++17 -c src/main.cpp -o src/main.o

new.o: src/new.cpp src/new.hpp
		g++ -std=c++17 -c src/new.cpp -o src/new.o

clean:
		rm -f src/*.o

wipe:
		rm saleen

