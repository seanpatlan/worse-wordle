#include <vector>
#include <unordered_set>
#include "WordleString.hpp"

/******************************************************************************/
/************************** CONSTRUCTORS/DESTRUCTORS **************************/
/******************************************************************************/

WordleString::WordleString(const std::string& s) :
  sz(s.size()),
  cap(WordleString::INIT_CAP)
{
  while (cap < sz) cap += cap/2;

  word = new WordleChar[cap];
  for (size_t i = 0; i < sz; i++)
    word[i] = std::move(WordleChar(s[i]));
}

WordleString::WordleString(const WordleString& ws) :
  sz(ws.sz),
  cap(ws.cap)
{
  word = new WordleChar[cap];
  for (size_t i = 0; i < sz; i++)
    word[i] = ws.word[i];
}

WordleString::WordleString(WordleString&& ws) noexcept :
  sz(ws.sz),
  cap(ws.cap),
  word(ws.word)
{
  ws.sz = 0;
  ws.cap = INIT_CAP;
  ws.word = nullptr;
}

WordleString::~WordleString()
{
  delete[] word;
}

/******************************************************************************/
/****************************** HELPER FUNCTIONS ******************************/
/******************************************************************************/

void WordleString::reallocate(size_t n)
{
  while (cap < n) cap += cap/2;
  WordleChar* newWord = new WordleChar[cap];

  for (int i = 0; i < sz; i++)
    newWord[i] = word[i];
  
  delete[] word;
  word = newWord;
}

/******************************************************************************/
/****************************** ACCESS FUNCTIONS ******************************/
/******************************************************************************/

const WordleChar& WordleString::at(size_t i) const
{
  if (i >= sz)
    throw std::string("WordleString: Referenced element out of range");
  
  return word[i];
}

bool WordleString::repeatedLetters() const
{
  for (int i = 0; i < sz; i++)
    for (int j = 0; j < sz; j++)
      if (word[i].letter == word[j].letter && i != j)
        return true;
  
  return false;
}

bool WordleString::contains(char c) const
{
  for (size_t i = 0; i < sz; i++)
    if (word[i].letter == c)
      return true;
  
  return false;
}

std::string WordleString::asString() const
{
  std::string s;
  for (int i = 0; i < sz; i++)
    s += word[i].letter;
  
  return s;
}

std::string WordleString::print() const
{
  std::string s;
  for (int i = 0; i < sz; i++)
    s += word[i].print();
  s += '\n';
  return s;
}

std::string WordleString::colorString() const
{
  std::string s;
  for (size_t i = 0; i < sz; i++)
    s += word[i].colorString()[0];
  
  return s;
}

bool WordleString::matchesPattern(const WordleString& answer, const std::string& colors) const
{
  if (sz != answer.size() || sz != colors.size()) return false;

  std::vector<char> whites, yellows;
  whites.reserve(sz);
  yellows.reserve(sz);
  std::unordered_set<char> wrongSpots(sz);

  for (int i = 0; i < sz; i++)
    switch (colors[i]) {
      case 'w': {
        if (word[i].letter == answer[i].letter)
          return false;
        else {
          whites.emplace_back(word[i].letter);
          wrongSpots.insert(answer[i].letter);
          break;
        }
      }
      case 'y': {
        if (word[i].letter == answer[i].letter)
          return false;
        else {
          yellows.emplace_back(word[i].letter);
          wrongSpots.insert(answer[i].letter);
          break;
        }
      }
      case 'g': {
        if (word[i].letter != answer[i].letter)
          return false;
      }
    }
  
  for (const char& w : whites)
    if (wrongSpots.find(w) != wrongSpots.end())
      return false;

  for (const char& y : yellows)
    if (wrongSpots.find(y) == wrongSpots.end())
      return false;

  return true;
}

/******************************************************************************/
/***************************** MODIFIER FUNCTIONS *****************************/
/******************************************************************************/

WordleString& WordleString::add(WordleChar wc)
{
  if (sz+1 > cap)
    reallocate(sz+1);
  
  word[sz++] = wc;

  return *this;
}

WordleString& WordleString::clear()
{
  delete[] word;
  cap = INIT_CAP;
  sz = 0;
  word = new WordleChar[cap];

  return *this;
}

WordleString& WordleString::whiteOut()
{
  for (int i = 0; i < sz; i++)
    word[i].setColor('w');

  return *this;
}

WordleString& WordleString::setColors(std::string colors)
{
  if (sz != colors.size()) return *this;

  for (int i = 0; i < sz; i++)
    word[i].setColor(colors[i]);
  
  return *this;
}

WordleString& WordleString::evaluate(WordleString secretWord)
{
  if (secretWord.size() != sz) return *this;

  secretWord.whiteOut();
  std::vector<WordleChar> wrongSpots;
  wrongSpots.reserve(sz);
  for (size_t i = 0; i < sz; i++) {
    if (word[i] == secretWord[i])
      word[i].color = WordleChar::green;
    else
      wrongSpots.emplace_back(secretWord[i]);
  }

  for (const WordleChar& cWrong : wrongSpots)
    for (size_t i = 0; i < sz; i++)
      if (word[i].color != WordleChar::green && word[i] == cWrong)
        word[i].setColor('y');
  
  return *this;
}

/******************************************************************************/
/********************************* OPERATORS **********************************/
/******************************************************************************/

void WordleString::operator=(const std::string& s)
{
  delete[] word;
  sz = s.size();
  cap = INIT_CAP;
  while (cap < sz) cap += cap/2;

  word = new WordleChar[cap];
  for (size_t i = 0; i < sz; i++)
    word[i] = std::move(WordleChar(s[i]));
}

void WordleString::operator=(const WordleString& ws)
{
  if (this != &ws) {
    delete[] word;
    sz = ws.sz;
    cap = ws.cap;

    word = new WordleChar[cap];
    for (size_t i = 0; i < sz; i++)
      word[i] = ws.word[i];
  }
}

void WordleString::operator=(WordleString&& ws)
{
  if (this != &ws) {
    delete[] word;
    sz = ws.sz;
    cap = ws.cap;
    word = ws.word;

    ws.sz = 0;
    ws.cap = INIT_CAP;
    ws.word = nullptr;
  }
}

bool WordleString::operator==(const WordleString& ws) const
{
  if (sz != ws.size()) return false;

  for (int i = 0; i < sz; i++)
    if (word[i] != ws.at(i))
      return false;
  
  return true;
}

bool WordleString::operator==(const std::string& s) const
{
  if (sz != s.size()) return false;

  for (int i = 0; i < sz; i++)
    if (word[i].letter != s[i])
      return false;
  
  return true;
}

std::ostream& operator<<(std::ostream& out, const WordleString& ws)
{
  for (size_t i = 0; i < ws.sz; i++)
    out << ws.word[i];

  return out;
}

std::istream& operator>>(std::istream& in, WordleString& ws)
{
  std::string s;
  in >> s;
  ws = std::move(WordleString(s));

  return in;
}

/******************************************************************************/
/********************************** ITERATOR **********************************/
/******************************************************************************/