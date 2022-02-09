#include <string>
#include <vector>
#include <iostream>
#include "WordleChar.hpp"
#pragma once

class WordleString
{
public:
  // TYPE DEFINITIONS
  typedef unsigned short int uint;
  typedef std::vector<WordleChar>::iterator iterator;
  typedef std::vector<WordleChar>::const_iterator const_iterator;
private:
  // MEMBERS
  std::vector<WordleChar> word;

public:
  // CONSTRUCTORS/DESTRUCTORS
  WordleString() {}
  WordleString(const std::string& str);

  // ACCESS FUNCTIONS
  uint size() const { return word.size(); }
  bool empty() const { return word.empty(); }
  const WordleChar& at(uint i) const;
  iterator begin() { return word.begin(); }
  const_iterator begin() const { return word.begin(); }
  iterator end() { return word.end(); }
  const_iterator end() const { return word.end(); }
  const std::vector<WordleChar>& allLetters() const { return word; }
  bool repeatedLetters() const;
  std::string asString() const;
  std::string print() const;

  // MODIFIER FUNCTIONS
  void add(const WordleChar& wc) { word.push_back(wc); }
  void clear() { word.clear(); }
  void whiteOut();
  void evaluate(WordleString ws);
  void evaluate(const std::string& str) { evaluate(WordleString(str)); }

  // OPERATORS
  void operator=(const std::string& s);
  void operator+=(const WordleChar& wc) { add(wc); }
  const WordleChar& operator[](uint i) const { return at(i); }
  bool operator==(const std::string str) const;
  bool operator!=(const std::string str) const { return !(*this == str); }
  friend std::ostream& operator<<(std::ostream& os, const WordleString& ws);
  friend std::istream& operator>>(std::istream& is, WordleString& ws);
};
