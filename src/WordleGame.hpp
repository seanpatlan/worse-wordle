#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include "WordleString.hpp"
#include "WordleSettings.hpp"
#pragma once

class WordleGame
{
public:
  // TYPE DEFINITIONS
  typedef unsigned int uint;
private:
  // MEMBERS
  uint wsz; // word size
  std::string sw; // secret word
  std::vector<std::string> wordList;
  std::vector<WordleString> guesses;
  std::set<char> wrongLetters;
  std::unordered_set<std::string> validWords;
  WordleSettings gameSettings;
public:
  // ACCESS FUNCTIONS
  const uint& wordSize() const { return wsz; }
  uint guessCount() const { return guesses.size(); }
  const std::string& secretWord() const { return sw; }
  const WordleSettings& settings() const { return gameSettings; }
  bool inWordList(const std::string& word) const;
  bool guessLimit() const;
  bool goodGuess(const WordleString& ws) const;
  std::string printGuesses() const;
  std::string printWrongLetters() const;

  // GAMEPLAY FUNCTIONS
  void setWordSize();
  void loadWordList();
  void selectSecretWord(uint r);
  WordleString getUserGuess();
  bool confirmUserGuess(const WordleString& ws);
  void addGuess(const WordleString& ws);
  void endDisplay();
  bool keepPlaying();
  void reset();
};
