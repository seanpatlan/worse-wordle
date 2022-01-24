#include <iostream>
#include <string>
#include "WordleSettings.hpp"
#pragma once

struct WordleResponse
{
  typedef unsigned int uint;

  static inline const char* INPUT_SYMBOL = "\n>> ";
  static inline const char* INVALID_SIZE = "invalid-size";

  static std::string boolInputSymbol(char t, char f)
  {
    return std::string("\n(") + t + "/" + f + ") ";
  }

  static void waitForEnter(const std::string& msg, bool dbg)
  {
    if (!dbg) system("clear");
    std::cout << msg << INPUT_SYMBOL;
    std::cin.ignore(WordleSettings::BUF_MAX, '\n');
  }

  static bool getBoolResponse(const std::string& msg, char t, char f, bool dbg)
  {
    while (true) {
      if (!dbg) system("clear");
      std::cout << msg << boolInputSymbol(t,f);

      char c;
      while (std::isspace(std::cin.peek())) std::cin.ignore();
      std::cin.get(c);
      std::cin.ignore(WordleSettings::BUF_MAX,'\n');

      if (std::toupper(c) == std::toupper(t)) return true;
      if (std::toupper(c) == std::toupper(f)) return false;
    }
  }

  static uint getIntResponse(const std::string& msg, uint min, uint max, bool dbg)
  {
    char *buf = new char[WordleSettings::BUF_MAX];
    int n = -1;
    while (n < 0) {
      if (!dbg) system("clear");
      std::cout << msg << INPUT_SYMBOL;

      std::cin.getline(buf, WordleSettings::BUF_MAX);
      try {
        n = std::stoi(buf);
      } catch (...) {
        n = -1;
      }
      if (n < min || n > max) n = -1;
    }
    delete[] buf;
    return n;
  }

  static std::string getStringResponse(const std::string& msg, uint sz, bool dbg)
  {
    if (!dbg) system("clear");
    std::cout << msg << INPUT_SYMBOL;

    std::string s;
    std::cin >> s;
    std::cin.ignore(WordleSettings::BUF_MAX,'\n');

    if (sz != 0 && s.size() != sz) return INVALID_SIZE;
    return s;
  }
};
