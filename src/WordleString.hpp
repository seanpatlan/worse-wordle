#include <iostream>
#include <string>
#include "WordleChar.hpp"
#pragma once

class WordleString
{
public:
  // TYPE DEFINITIONS
  typedef unsigned short int size_t;
  class iterator
  {
  private:
    WordleChar* ptr;
  public:
    iterator(WordleChar* _ptr) : ptr(_ptr) {}

    WordleChar& operator*() { return *ptr; }
    const WordleChar& operator*() const { return *ptr; }
    WordleChar* operator->() { return ptr; }
    const WordleChar* operator->() const { return ptr; }
    WordleChar& operator[](size_t i) { return *(ptr+i); }
    const WordleChar& operator[](size_t i) const { return *(ptr+i); }
    iterator operator+(size_t i) const { return iterator(ptr+i); }
    iterator operator-(size_t i) const { return iterator(ptr-i); }
    bool operator==(const iterator& it) const { return ptr == it.ptr; }
    bool operator!=(const iterator& it) const { return !(*this == it); }
    iterator& operator++() { ptr++; return *this; }
    iterator& operator--() { ptr--; return *this; }
    iterator& operator++(int) {
      iterator temp(ptr);
      ++(*this);
      return temp;
    }
    iterator& operator--(int) {
      iterator temp(ptr);
      --(*this);
      return temp;
    }
  };

  // STATIC MEMBERS
  const static inline size_t INIT_CAP = 8;
private:
  // MEMBERS
  WordleChar* word;
  size_t sz;
  size_t cap = INIT_CAP;

  // HELPER FUNCTIONS
  void reallocate(size_t n);
public:
  // CONSTRUCTORS/DESTRUCTORS
  WordleString() : sz(0), word(new WordleChar[INIT_CAP]) {}
  WordleString(const std::string& s);
  WordleString(const WordleString& ws);
  WordleString(WordleString&& ws) noexcept;
  ~WordleString();

  // ACCESS FUNCTIONS
  size_t size() const { return sz; }
  size_t capacity() const { return cap; }
  bool empty() const { return sz == 0; }
  const WordleChar& at(size_t i) const;
  iterator begin() { return std::move(iterator(word)); }
  const iterator begin() const { return std::move(iterator(word)); }
  iterator end() { return std::move(iterator(word+sz)); }
  const iterator end() const { return std::move(iterator(word+sz)); }
  bool repeatedLetters() const;
  bool contains(char c) const;
  std::string asString() const;
  std::string colorString() const;
  std::string print() const;
  bool matchesPattern(const WordleString& other, const std::string& colors) const;

  // MODIFIER FUNCTIONS
  WordleString& add(WordleChar wc);
  WordleString& clear();
  WordleString& whiteOut();
  WordleString& setColors(std::string colors);
  WordleString& evaluate(WordleString ws);
  WordleString& evaluate(const std::string& str) { return evaluate(WordleString(str)); }

  // OPERATORS
  void operator=(const std::string& s);
  void operator=(const WordleString& ws);
  void operator=(WordleString&& ws);
  void operator+=(const WordleChar& wc) { add(wc); }
  const WordleChar& operator[](uint i) const { return at(i); }
  bool operator==(const WordleString& ws) const;
  bool operator==(const std::string& s) const;
  bool operator!=(const WordleString& ws) const { return !(*this == ws); }
  bool operator!=(const std::string& s) const { return !(*this == s); }
  friend std::ostream& operator<<(std::ostream& out, const WordleString& ws);
  friend std::istream& operator>>(std::istream& in, WordleString& ws);
};