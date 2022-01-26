#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../lib/json.hpp"
#pragma once

class WordleSettings
{
private:
  // MEMBERS
  nlohmann::json all;
public:
  // config file paths
  static inline const char* SETTINGS_JSON = "configs/settings.json";
  static inline const char* LIST_JSON = "configs/list.json";
  static inline const char* DICT_JSON = "configs/dict.json";

  // string labels for settings file
  static inline const char* WORD_SIZE = "word-size";
  static inline const char* REP_LETTERS = "repeated-letters";
  static inline const char* GUESS_LIMIT = "guess-limit";
  static inline const char* CHECK_GUESS = "check-guess";
  static inline const char* DEBUG_MODE = "debug-mode";

  // CONSTRUCTOR
  WordleSettings()
  {
    all[WORD_SIZE] = 5;
    all[REP_LETTERS] = true;
    all[GUESS_LIMIT] = 6;
    all[CHECK_GUESS] = true;
    all[DEBUG_MODE] = false;
  }

  int wordSize() const { return all[WORD_SIZE]; }
  bool repeatedLetters() const { return all[REP_LETTERS]; }
  int guessLimit() const { return all[GUESS_LIMIT]; }
  bool checkGuess() const { return all[CHECK_GUESS]; }
  bool debugMode() const { return all[DEBUG_MODE]; }

  void print() const
  {
    std::cout << all.dump(2) << '\n';
  }

  void load()
  {
    std::ifstream in(SETTINGS_JSON);
    if (in.good())
      in >> all;
  }

  template<class T>
  void set(const std::string& label, const T& value)
  {
    all[label] = value;
    std::ofstream out(SETTINGS_JSON);
    out << all.dump(2);
  }
};
