OS := $(shell uname)

ifeq ($(OS),Darwin)
   CC = clang++
   FLAGS = -Wall -I/usr/local/include/  -L /usr/local/lib/ -lgsl -lgslcblas -lm -std=c++14
else ifeq ($(OS),Linux)
   CC = g++-5
   FLAGS = -lm -std=c++14
endif

DEBUG = -g


Practica3:
	$(CC) -o mainFinal mainFinal.cpp $(FLAGS)

clean:
	rm mainFinal
