all:
	g++ wordle.cpp WordleString.cpp WordleGame.cpp -w -o wordle
	g++ settings.cpp -w -o settings

wordle:
	g++ wordle.cpp WordleString.cpp WordleGame.cpp -w -o wordle

settings:
	g++ settings.cpp -w -o settings

test:
	g++ test.cpp WordleString.cpp WordleGame.cpp -w -o t

clean:
	rm -rf wordle list-maker settings t
