#include <string>
#include <vector>
#include <iostream>
#include "WordleChar.hpp"
#pragma once

class WordleString
{
private:
  // MEMBERS
  std::vector<WordleChar> word;

public:
  // CONSTRUCTORS/DESTRUCTORS
  WordleString() :
    word(std::vector<WordleChar>())
  {}
  WordleString(const WordleString& ws) :
    word(ws.allLetters())
  {}
  WordleString(const std::string& str);
  ~WordleString();

  // ACCESS FUNCTIONS
  const int& size() const { return word.size(); }
  const WordleChar& at(const int& i) const;
  const std::vector<WordleChar>& allLetters() const { return word; }
  const std::string asString() const;
  void print() const;

  // MODIFIER FUNCTIONS
  void add(const WordleChar& wc) { word.push_back(wc); }
  void clear() { word.clear(); }
  void evaluate(const std::string& str);

  // OPERATORS
  void operator=(const std::string& s);
  void operator+=(const WordleString& ws);
  void operator+=(const WordleChar& wc) { add(wc); }
  WordleChar& operator[](const int& i) { return word[i]; }
  const WordleChar& operator[](const int& i) const { return at(i); }
  const bool& operator==(const std::string str) const;
  const bool& operator!=(const std::string str) const { return !(*this == str); }
  friend std::ostream& operator<<(std::ostream& os, const WordleString& ws);
  friend std::istream& operator>>(std::istream& is, WordleString& ws);
};
