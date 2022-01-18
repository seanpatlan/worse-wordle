#include <string>
#include <iostream>
#pragma once

struct WordleChar {
  enum LetterStatus {wrong = 47, inWord = 43, inSpot = 42};

  char letter;
  LetterStatus status;

  WordleChar() : letter('\0'), status(wrong) {}
  WordleChar(char c) : letter(std::toupper(c)), status(wrong) {}

  void print() {
    std::cout << "\033[1;30;" << status << "m " << letter << " \033[0m";
  }

  bool operator==(const char& c) { return letter == c; }
  bool operator!=(const char& c) { return letter != c; }
};

class WordleString
{
private:
  WordleChar *word;
  int sz;
  int WORD_SIZE;

public:
  // CONSTRUCTORS/DESTRUCTORS
  WordleString(int wSize) :
    word(new WordleChar[wSize]),
    sz(0),
    WORD_SIZE(wSize)
  {}
  WordleString(const std::string& str);
  WordleString(const WordleString& ws);
  ~WordleString();

  // ACCESS FUNCTIONS
  const int& size() const { return sz; }
  const char& at(const int& i) const;
  const WordleChar::LetterStatus& statusAt(const int& i) const;
  const int& wordSize() const { return WORD_SIZE; }
  const std::string wrongGuesses() const;
  const std::string asString() const;
  void printResult() const;
  void printStatus() const;

  // MODIFIER FUNCTIONS
  void add(const char& c);
  void add(const std::string& str);
  void clear();
  void evaluate(const std::string& str);

  // OPERATORS
  bool operator==(const std::string str);
  bool operator!=(const std::string str);
  WordleString operator+(const WordleString& ws);
  WordleString operator+(const std::string& str);
  WordleString operator+(const char& c);
  void operator+=(const WordleString& ws);
  void operator+=(const std::string& str);
  void operator+=(const char& c);
  void operator=(const std::string& s);
  const char& operator[](const int& i) const;
  friend std::ostream& operator<<(std::ostream& os, const WordleString& ws);
  friend std::istream& operator>>(std::istream& is, WordleString& ws);
};
