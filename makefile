all: 
	g++ main.cpp  -o main -std=c++11
	./main

clean:
	rm ./main
