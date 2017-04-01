CC=g++
FLAGS=-std=c++11 -O2 -Wall

aleksey: aleksey.cpp
	$(CC) $^ $(FLAGS) -o $@
kinan: kinan.cpp
	$(CC) $^ $(FLAGS) -o $@
dima: dima.cpp
	$(CC) $^ $(FLAGS) -o $@
timur: timur.cpp
	$(CC) $^ $(FLAGS) -o $@
