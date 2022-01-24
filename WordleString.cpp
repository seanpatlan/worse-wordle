#include <sstream>
#include "WordleString.hpp"

/******************************************************************************/
/************************** CONSTRUCTORS/DESTRUCTORS **************************/
/******************************************************************************/

WordleString::WordleString(const std::string& str)
{
  word.clear();
  for (const char& c : str)
    word.push_back(WordleChar(c));
}

WordleString::~WordleString()
{
  word.clear();
}

/******************************************************************************/
/****************************** ACCESS FUNCTIONS ******************************/
/******************************************************************************/

const WordleChar& WordleString::at(const int& i) const
{
  if (i < 0 || i >= word.size())
    return WordleChar('\0');

  return word[i];
}

bool WordleString::repeatedLetters() const
{
  for (int i = 0; i < word.size(); i++)
    for (int j = 0; j < word.size(); j++)
      if (word[i].letter == word[j].letter && i != j)
        return true;
  return false;
}

const std::string WordleString::asString() const
{
  std::string str = "";
  for (const WordleChar& wc : word)
    str += wc.letter;

  return str;
}

const std::string WordleString::print() const
{
  std::stringstream ss;
  for (const WordleChar& wc : word)
    ss << wc.print();
  ss << '\n';
  return ss.str();
}

/******************************************************************************/
/***************************** MODIFIER FUNCTIONS *****************************/
/******************************************************************************/

void WordleString::evaluate(const std::string& secretWord)
{
  if (secretWord.size() != word.size()) return;

  std::string original = "";
  for (const char& c : secretWord)
    original += std::toupper(c);
  std::string wrongSpots = "";

  for (int i = 0; i < word.size(); i++) {
    if (word[i] == original[i]) {
      word[i].color = WordleChar::Color::green;
    }
    else {
      wrongSpots += original[i];
    }
  }

  for (char& c : wrongSpots)
    for (WordleChar& wc : word)
      if (wc.letter == c)
        wc.color = WordleChar::Color::yellow;
}

/******************************************************************************/
/********************************* OPERATORS **********************************/
/******************************************************************************/

void WordleString::operator=(const std::string& str)
{
  word.clear();
  for (const char& c : str)
    add(WordleChar(c));
}

void WordleString::operator+=(const WordleString& ws)
{
  for (const WordleChar& wc : ws)
    add(wc);
}

const bool& WordleString::operator==(const std::string str) const
{
  if (str.size() != word.size()) return false;

  for (int i = 0; i < word.size(); i++)
    if (word[i] != str[i])
      return false;

  return true;
}

std::ostream& operator<<(std::ostream& os, const WordleString& ws)
{
  for (const WordleChar& wc : ws.word)
    os << wc;

  return os;
}

std::istream& operator>>(std::istream& is, WordleString& ws)
{
  std::string s;
  is >> s;
  ws = s;

  return is;
}
