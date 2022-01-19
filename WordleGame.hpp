#include <string>
#include <vector>
#include <unordered_set>
#include "WordleString.hpp"
#pragma once

class WordleGame
{
private:
  // MEMBERS
  int wsz;
  std::vector<std::string> wordList;
  std::vector<WordleString> guesses;
  std::unordered_set<char> wrongLetters;
public:
  // CONSTRUCTORS/DESTRUCTORS
  WordleGame() :
    wsz(5), // default to 5 letter game
    wordList(std::vector<std::string>()),
    guesses(std::vector<WordleString>()),
    wrongLetters(std::unordered_set<char>())
  {}
  WordleGame(const WordleGame& wg);
  ~WordleGame();

  // ACCESS FUNCTIONS
  const int& wordSize() const { return wsz; }
  const int& guessCount() const { return guesses.size(); }
  const std::string& selectSecretWord(const int& r) const;
  void printGuesses() const;
  void printWrongLetters() const;

  // GAMEPLAY FUNCTIONS
  void setWordSize();
  void loadWordList();
  WordleString getUserGuess();
  bool confirmUserGuess(const WordleString& ws);
  void addGuess(const WordleString& ws);
  void displayWin(const std::string& secretWord) const;
  bool keepPlaying();
  void reset();
};
