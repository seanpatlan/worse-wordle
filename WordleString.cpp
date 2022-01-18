#include "WordleString.hpp"

// CONSTRUCTORS/DESTRUCTORS

WordleString::WordleString(const std::string& str)
{
  WORD_SIZE = str.size();
  word = new WordleChar[WORD_SIZE];

  for (int i = 0; i < WORD_SIZE; i++)
    word[i] = WordleChar(str[i]);
}

WordleString::WordleString(const WordleString& ws)
{
  WORD_SIZE = ws.wordSize();
  word = new WordleChar[WORD_SIZE];
  sz = ws.size();

  for (int i = 0; i < sz; i++) {
    word[i].letter = ws[i];
    word[i].status = ws.statusAt(i);
  }
}

WordleString::~WordleString()
{
  delete[] word;
}

/******************************************************************************/

// ACCESS FUNCTIONS

const char& WordleString::at(const int& i) const
{
  if (i < 0 || i >= sz)
    return '\0';

  return word[i].letter;
}

const WordleChar::LetterStatus& WordleString::statusAt(const int& i) const
{
  if (i < 0 || i >= sz)
    return WordleChar::LetterStatus::wrong;

  return word[i].status;
}

const std::string WordleString::wrongGuesses() const
{
  std::string str = "";
  for (int i = 0; i < sz; i++)
    if (word[i].status == WordleChar::LetterStatus::wrong)
      str += word[i].letter;

  return str;
}

const std::string WordleString::asString() const
{
  std::string str = "";
  for (int i = 0; i < sz; i++)
    str += at(i);

  return str;
}

void WordleString::printResult() const
{
  for (int i = 0; i < sz; i++)
    word[i].print();
  std::cout << '\n';
}

void WordleString::printStatus() const
{
  std::cout << "Status: (size = " << sz << ")\n";
  for (int i = 0; i < sz; i++)
    std::cout << '\t' << word[i].letter << " : " << word[i].status << '\n';
}

/******************************************************************************/

// MODIFIER FUNCTIONS

void WordleString::add(const char& c)
{
  if (sz < WORD_SIZE)
    word[sz++] = WordleChar(c);
}

void WordleString::add(const std::string& str)
{
  for (char c : str)
    add(c);
}

void WordleString::clear()
{
  sz = 0;
  for (int i = 0; i < WORD_SIZE; i++)
    word[i] = WordleChar();
}

void WordleString::evaluate(const std::string& str)
{
  if (str.size() != sz) return;

  std::string original = "";
  for (char c : str) original += std::toupper(c);
  std::string wrongSpots = "";

  for (int i = 0; i < sz; i++) {
    if (word[i] == original[i]) {
      word[i].status = WordleChar::LetterStatus::inSpot;
    }
    else {
      wrongSpots += original[i];
    }
  }

  for (char c : wrongSpots)
    for (int i = 0; i < sz; i++)
      if (word[i] == c)
        word[i].status = WordleChar::LetterStatus::inWord;
}

/******************************************************************************/

// OPERATORS

bool WordleString::operator==(const std::string str)
{
  if (str.size() != sz) return false;

  for (int i = 0; i < sz; i++)
    if (word[i] != str[i])
      return false;

  return true;
}

bool WordleString::operator!=(const std::string str)
{
  return !(*this == str);
}

WordleString WordleString::operator+(const WordleString& ws)
{
  WordleString newWord(*this);

  int newSize = sz+ws.size() > WORD_SIZE ? WORD_SIZE : sz + ws.size();
  for (int i = sz; i < newSize; i++)
    newWord.add(ws[i-sz]);

  return newWord;
}

WordleString WordleString::operator+(const std::string& str)
{
  WordleString newWord(*this);

  int newSize = sz+str.size() > WORD_SIZE ? WORD_SIZE : sz + str.size();
  for (int i = sz; i < newSize; i++)
    add(str[i-sz]);

  return newWord;
}

WordleString WordleString::operator+(const char& c)
{
  WordleString newWord(*this);
  newWord.add(c);

  return newWord;
}

void WordleString::operator+=(const WordleString& ws)
{
  int newSize = sz+ws.size() > WORD_SIZE ? WORD_SIZE : sz + ws.size();
  for (int i = sz; i < newSize; i++)
    add(ws[i-sz]);

  sz = newSize;
}

void WordleString::operator+=(const std::string& str)
{
  int newSize = sz+str.size() > WORD_SIZE ? WORD_SIZE : sz + str.size();
  for (int i = sz; i < newSize; i++)
    add(str[i-sz]);

  sz = newSize;
}

void WordleString::operator+=(const char& c)
{
  add(c);
}

void WordleString::operator=(const std::string& str)
{
  for (int i = 0; i < str.size() && i < WORD_SIZE; i++) {
    word[i] = WordleChar(str[i]);
    sz++;
  }
}

const char& WordleString::operator[](const int& i) const
{
  return at(i);
}

std::ostream& operator<<(std::ostream& os, const WordleString& ws)
{
  for (int i = 0; i < ws.sz; i++)
    os << ws.word[i].letter;

  return os;
}

std::istream& operator>>(std::istream& is, WordleString& ws)
{
  ws.clear();

  std::string s;
  is >> s;
  ws = s;

  return is;
}
