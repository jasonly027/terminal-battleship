all: ss cc
ss: server.cpp board.cpp
	g++ -std=c++17 -o server server.cpp board.cpp
cc: client.cpp board.cpp
	g++ -std=c++17 -o client client.cpp board.cpp
clean:
	rm server client