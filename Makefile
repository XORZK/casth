IN=src/main.cpp

default:
	clang++ -std=c++17 $(IN) -o main && ./main test.casth