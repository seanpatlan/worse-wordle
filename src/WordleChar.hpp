#include <iostream>
#pragma once

struct WordleChar
{
  // TYPE DEFINITIONS
  enum Color { white = 47, yellow = 43, green = 42, red = 41 };

  // MEMBERS
  char letter;
  Color color;

  // CONSTRUCTORS/DESTRUCTORS
  WordleChar() : letter('\0'), color(white) {}
  WordleChar(char c) : color(white)
  {
    c = std::toupper(c);
    if ((c >= 'A' && c <= 'Z') || c == '_')
      letter = c;
    else
      letter = '*';
  }

  // ACCESS FUNCTIONS
  std::string print() const
  {
    return "\033[1;30;" + std::to_string(color) + "m " + letter + " \033[0m";
  }

  std::string colorString() const
  {
    switch (color) {
      case white:
        return "white";
      case yellow:
        return "yellow";
      case green:
        return "green";
      default:
        return "undefined";
    }
  }

  // MODIFIER FUNCTIONS
  void setColor(char c)
  {
    switch (c) {
      case 'w': {
        color = white;
        break;
      }
      case 'y': {
        color = yellow;
        break;
      }
      case 'g': {
        color = green;
        break;
      }
      default: {
        color = red;
        break;
      }
    } 
  }

  // OPERATORS
  bool operator==(const WordleChar& wc) const
  {
    return (letter == wc.letter) && (color == wc.color);
  }

  bool operator==(const char& c) const
  {
    return letter == c;
  }

  bool operator!=(const WordleChar& wc) const
  {
    return !(*this == wc);
  }

  bool operator!=(const char& c) const
  {
    return !(*this == c);
  }

  void operator=(const char& c)
  {
    color = Color::white;
    letter = c;
  }

  friend std::ostream& operator<<(std::ostream& os, const WordleChar& wc)
  {
    os << wc.letter;
    return os;
  }

  friend std::istream& operator>>(std::istream& is, WordleChar& wc)
  {
    char c;
    is >> c;
    wc = WordleChar(c);

    return is;
  }
};
