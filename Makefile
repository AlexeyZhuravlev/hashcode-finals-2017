CC=g++
FLAGS=-std=c++11

aleksey: aleksey.cpp
	$(CC) $^ $(FLAGS) -o $@
kinan: kinan.cpp
	$(CC) $^ $(FLAGS) -o $@
dima: dima.cpp
	$(CC) $^ $(FLAGS) -o $@
timur: timur.cpp
	$(CC) $^ $(FLAGS) -o $@