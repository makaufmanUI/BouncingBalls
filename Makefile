all:
	g++ -std=c++20 -I src/include -L src/lib -o main main.cpp -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-system -lsfml-window