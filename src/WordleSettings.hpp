#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#pragma once

struct WordleSettings
{
  // MEMBERS
  int wordSize;
  bool repeatedLetters;
  int guessLimit;

  // FOR DEBUGGING
  bool debugMode;

  // CONSTRUCTOR
  WordleSettings() :
    wordSize(5),
    repeatedLetters(true),
    guessLimit(6),
    debugMode(false)
  {}

  // max size of I/O buffer
  static inline const int BUF_MAX = 128;
  static inline const char* FILE_NAME = "config/settings.txt";

  // string labels for settings.txt
  static inline const char* WORD_SIZE = "word-size";
  static inline const char* REP_LETTERS = "repeated-letters";
  static inline const char* GUESS_LIMIT = "guess-limit";
  static inline const char* DEBUG_MODE = "debug-mode";

  template<class T>
  std::ostream& put(std::ostream& out, const std::string& label, const T& value)
  {
    out << label << ": " << value << ",\n";
    return out;
  }

  std::istream& get(std::istream& in, std::string& label, std::string& value)
  {
    std::string s;
    getline(in, s);

    label.clear();
    value.clear();

    auto it = s.begin();
    while (it != s.end() && *it != ':')
      label += *(it++);

    while (it != s.end() && (*it == ':' || *it == ' ')) it++;

    while (it != s.end() && *it != ',' && !std::isspace(*it))
      value += *(it++);

    return in;
  }

  void set(const std::string& label, const std::string& value)
  {
    if (value.empty()) return;

    if (label == WORD_SIZE)
      wordSize = std::stoi(value);
    else if (label == REP_LETTERS)
      repeatedLetters = value != "0";
    else if (label == DEBUG_MODE)
      debugMode = value != "0";
    else if (label == GUESS_LIMIT)
      guessLimit = std::stoi(value);
  }

  void load()
  {
    std::ifstream ifs(FILE_NAME);
    std::string label;
    std::string value;

    while (get(ifs, label, value))
      set(label, value);
  }

};
