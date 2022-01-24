all:
	g++ wordle.cpp WordleString.cpp WordleGame.cpp -w -o wordle
	g++ settings.cpp -w -o settings

wordle:
	g++ wordle.cpp WordleString.cpp WordleGame.cpp -w -o wordle

list-maker:
	g++ list-maker.cpp WordleString.cpp -w -o list-maker

settings:
	g++ settings.cpp -w -o settings

test:
	g++ test.cpp WordleString.cpp WordleGame.cpp -w -o t

clean:
	rm -rf wordle list-maker settings t
