#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include "WordleString.hpp"
#include "WordleSettings.hpp"
#pragma once

class WordleGame
{
private:
  // MEMBERS
  int wsz; // word size
  std::string sw; // secret word
  std::vector<std::string> wordList;
  std::vector<WordleString> guesses;
  std::set<char> wrongLetters;
  std::unordered_set<std::string> validWords;
  WordleSettings gameSettings;
public:
  // CONSTRUCTORS/DESTRUCTORS
  WordleGame() :
    wsz(5), // default to 5 letter game
    sw(""),
    wordList(std::vector<std::string>()),
    guesses(std::vector<WordleString>()),
    wrongLetters(std::set<char>()),
    validWords(std::unordered_set<std::string>()),
    gameSettings(WordleSettings())
  {}
  WordleGame(const WordleGame& wg);
  ~WordleGame();

  // ACCESS FUNCTIONS
  const int& wordSize() const { return wsz; }
  const int& guessCount() const { return guesses.size(); }
  const std::string& secretWord() const { return sw; }
  const WordleSettings& settings() const { return gameSettings; }
  bool inWordList(const std::string& word) const;
  bool guessLimit() const;
  const std::string printGuesses() const;
  const std::string printWrongLetters() const;

  // GAMEPLAY FUNCTIONS
  void setWordSize();
  void loadWordList();
  void selectSecretWord(const int& r);
  WordleString getUserGuess();
  bool confirmUserGuess(const WordleString& ws);
  void addGuess(const WordleString& ws);
  void endDisplay();
  bool keepPlaying();
  void reset();
};
