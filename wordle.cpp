#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>
#include "WordleString.hpp"
using namespace std;

int getWordleSize()
{
  char c = '\0';
  while (c < '4' || c > '7') {
    system("clear");
    cout << "Would you like to play with 4, 5, 6, or 7 letter words? ";
    cin >> c;
  }

  return static_cast<int>(c) - 48;
}

vector<string> getWordList(const int& sz)
{
  ifstream ifs(to_string(sz) + "-list.txt");
  vector<string> words;

  string s;
  while (ifs >> s) words.push_back(s);

  return words;
}

bool keepPlaying()
{
  string str;
  while (true) {
    cout << "\nEnter 'y' to keep playing, enter 'q' to quit... ";
    cin >> str;

    if (str == "y" || str == "Y") return true;
    if (str == "q" || str == "Q") return false;
  }
}

int main()
{
  srand(time(NULL));

  int wordleSize = getWordleSize();
  vector<string> wordList = getWordList(wordleSize);

  int guessCount;
  WordleString guess(wordleSize);
  unordered_set<char> previousGuesses;

  string str;
  do {
    guess.clear();
    previousGuesses.clear();
    string secretWord = wordList[ rand() % wordList.size() ];

    system("clear");
    guessCount = 0;
    while (guess != secretWord) {
      cout << "Enter your guess here:\n";
      cin >> guess;
      guess.evaluate(secretWord);

      cout << "\nGuess #" << ++guessCount << '\n';
      guess.printResult();

      cout << "Previous letters: ";
      if (previousGuesses.empty()) cout << "(none)";
      for (char c : previousGuesses)
        WordleChar(c).print();
      cout << "\n\n";

      str = guess.wrongGuesses();
      for (char c : str)
        previousGuesses.insert(c);
    }

    guess.clear();
    cout << "\nCongrats! Completed in " << guessCount << " guesses!\n";
  } while (keepPlaying());

  return 0;
}
