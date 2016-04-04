OS := $(shell uname)

ifeq ($(OS),Darwin)
   CC = clang++
   FLAGS = -Wall -I/usr/local/include/  -L /usr/local/lib/ -lgsl -lgslcblas -lm -std=c++14
else ifeq ($(OS),Linux)
   CC = g++-5
   FLAGS = -lm -std=c++14
endif

DEBUG = -g

Practica1:
	$(CC) -o main main.cpp $(FLAGS)

debug:
	$(CC) -o main main.cpp $(FLAGS) $(DEBUG)
Practica2:
	$(CC) -o main2 mainFinal.cpp $(FLAGS)

clean:
	rm main
