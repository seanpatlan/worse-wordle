CC = g++
CFLAGS = -std=c++11 -w
H_DEPS = src/WordleChar.hpp src/WordleResponse.hpp src/WordleSettings.hpp
GAME_DEPS = src/WordleString.cpp src/WordleGame.cpp

all: wordle.cpp $(GAME_DEPS) settings.cpp $(H_DEPS)
	$(CC) wordle.cpp $(GAME_DEPS) $(CFLAGS) -o wordle
	$(CC) settings.cpp $(CFLAGS) -o settings

wordle: wordle.cpp $(GAME_DEPS) $(H_DEPS)
	$(CC) wordle.cpp $(GAME_DEPS) $(CFLAGS) -o wordle

settings: settings.cpp $(H_DEPS)
	$(CC) settings.cpp $(CFLAGS) -o settings

test: test.cpp $(GAME_DEPS) $(H_DEPS)
	$(CC) test.cpp $(GAME_DEPS) $(CFLAGS) -o test

clean:
	rm -rf wordle list-maker settings test
