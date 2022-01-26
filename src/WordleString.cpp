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

/******************************************************************************/
/****************************** ACCESS FUNCTIONS ******************************/
/******************************************************************************/

const WordleChar& WordleString::at(uint i) const
{
  if (i >= word.size())
    return WordleChar();

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

std::string WordleString::asString() const
{
  std::string str = "";
  for (const WordleChar& wc : word)
    str += wc.letter;

  return str;
}

std::string WordleString::print() const
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

void WordleString::whiteOut()
{
  for (WordleChar& wc : word)
    wc.color = WordleChar::Color::white;
}

void WordleString::evaluate(WordleString secretWord)
{
  if (secretWord.size() != word.size()) return;

  secretWord.whiteOut();
  WordleString wrongSpots;
  for (int i = 0; i < word.size(); i++) {
    if (word[i] == secretWord[i])
      word[i].color = WordleChar::Color::green;
    else
      wrongSpots += secretWord[i];
  }

  for (const WordleChar& cWrong : wrongSpots)
    for (WordleChar& cWord : word)
      if (cWord.color != WordleChar::Color::green && cWord == cWrong)
        cWord.color = WordleChar::Color::yellow;
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

bool WordleString::operator==(const std::string str) const
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
