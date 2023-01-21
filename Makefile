saleen: main.o init.o
		g++ -std=c++17 -o saleen src/main.o src/init.o

main.o: src/main.cpp src/init.hpp
		g++ -std=c++17 -c src/main.cpp -o src/main.o

init.o: src/init.cpp src/init.hpp
		g++ -std=c++17 -c src/init.cpp -o src/init.o

clean:
		rm -f src/*.o

wipe:
		rm saleen

