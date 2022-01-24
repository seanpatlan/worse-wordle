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
  bool debugMode;
  int guessLimit;

  // CONSTRUCTOR
  WordleSettings() :
    wordSize(0),
    repeatedLetters(false),
    debugMode(false),
    guessLimit(0)
  {}

  // max size of I/O buffer
  static inline const int BUF_MAX = 128;

  // string labels for settings.txt
  static inline const char* WORD_SIZE = "word-size";
  static inline const char* REP_LETTERS = "repeated-letters";
  static inline const char* DEBUG_MODE = "debug-mode";
  static inline const char* GUESS_LIMIT = "guess-limit";

  template<class T>
  std::ostream& put(std::ostream& os, const std::string& label, const T& value)
  {
    os << label << ": " << value << ",\n";
    return os;
  }

  std::istream& get(std::istream& is, char *label, char *value)
  {
    char *buf = new char[BUF_MAX];
    is.getline(buf, BUF_MAX);

    *label = '\0';
    *value = '\0';
    std::stringstream ss(buf);
    ss.getline(label, BUF_MAX, ':');

    while (ss.peek() == ' ') ss.ignore();

    int i = 0;
    while (i < BUF_MAX && ss.peek() != ',' && !std::isspace(ss.peek()))
      ss.get(value[i++]);
    value[i] = '\0';
    delete[] buf;

    return is;
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
    std::ifstream ifs("settings.txt");
    char *label = new char[BUF_MAX];
    char *value = new char[BUF_MAX];

    while (get(ifs, label, value))
      set(label, value);

    delete[] label, value;
  }

};
