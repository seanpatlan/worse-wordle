#include <fstream>
#include <sstream>
#include <iostream>
#include "WordleResponse.hpp"
#include "WordleGame.hpp"

/******************************************************************************/
/****************************** ACCESS FUNCTIONS ******************************/
/******************************************************************************/

bool WordleGame::inWordList(const std::string& word) const
{
  for (const std::string& s : wordList)
    if (WordleString(word) == s)
      return true;
  return false;
}

bool WordleGame::guessLimit() const
{
  return (gameSettings.guessLimit == 0) ||
         (guesses.size() < gameSettings.guessLimit);
}

std::string WordleGame::printGuesses() const
{
  std::string s = "";
  for (const WordleString& ws : guesses) s += ws.print();
  return s;
}

std::string WordleGame::printWrongLetters() const
{
  if (wrongLetters.empty()) return "";

  std::string msg = "Wrong letters: ";
  for (const char& c : wrongLetters)
    msg += WordleChar(c).print();
  msg += "\n";

  return msg;
}

/******************************************************************************/
/***************************** GAMEPLAY FUNCTIONS *****************************/
/******************************************************************************/

void WordleGame::setWordSize()
{
  if (gameSettings.wordSize == 0) {
    std::string msg = "Would you like to play with 4, 5, 6, or 7 letter words?\n";
    wsz = WordleResponse::getIntResponse(msg, 4, 7, gameSettings.debugMode);
  }
  else
    wsz = gameSettings.wordSize;
}

void WordleGame::loadWordList()
{
  WordleString ws;

  wordList.clear();
  std::ifstream lin("csv/" + std::to_string(wsz) + "-list.csv");
  while (lin >> ws) {
    if (gameSettings.repeatedLetters)
      wordList.push_back(ws.asString());
    else if (!ws.repeatedLetters())
      wordList.push_back(ws.asString());
  }

  if (wordList.empty())
    throw std::string("ERROR: (") + __func__ + ") Word list is empty";

  validWords.clear();
  std::ifstream din("csv/" + std::to_string(wsz) + "-dict.csv");
  while (din >> ws) {
    if (gameSettings.repeatedLetters)
      validWords.insert(ws.asString());
    else if (!ws.repeatedLetters())
      validWords.insert(ws.asString());
  }

  if (validWords.empty())
    throw std::string("ERROR: (") + __func__ + ") Dictionary is empty";
}

void WordleGame::selectSecretWord(uint r)
{
  if (wordList.empty())
    throw std::string("ERROR: (") + __func__ + ") Word list is empty";
  else
    sw = wordList[ r % wordList.size() ];
}

WordleString WordleGame::getUserGuess()
{
  std::string guessString;
  do {
    if (!gameSettings.debugMode) system("clear");

    std::string msg = printWrongLetters();
    if (!wrongLetters.empty()) msg += '\n';
    msg += printGuesses();
    if (!guesses.empty()) msg += '\n';

    if (!guessString.empty()) {
      if (guessString == WordleResponse::INVALID_SIZE)
        msg += "Guess must be " + std::to_string(wsz) + " letters\n\n";
      else
        msg += "Not a valid word\n\n";
    }

    msg += "Guess #" + std::to_string(guessCount()+1) + '\n';
    guessString = WordleResponse::getStringResponse(msg, wsz, gameSettings.debugMode);
  } while (guessString == WordleResponse::INVALID_SIZE ||
          validWords.find(WordleString(guessString).asString()) == validWords.end());

  return WordleString(guessString);
}

bool WordleGame::confirmUserGuess(const WordleString& ws)
{
  std::string msg = "";
  msg += printWrongLetters();
  if (!wrongLetters.empty()) msg += '\n';
  msg += printGuesses();
  if (!guesses.empty()) msg += '\n';
  msg += ws.print();
  msg += "(Colors are currently hidden)\n\nConfirm this guess?\n";

  return WordleResponse::getBoolResponse(msg, 'y', 'n', gameSettings.debugMode);
}

void WordleGame::addGuess(const WordleString& ws)
{
  guesses.push_back(ws);

  for (int i = 0; i < ws.size(); i++)
    if (ws[i].color == WordleChar::Color::white)
      wrongLetters.insert(ws[i].letter);
}

void WordleGame::endDisplay()
{
  std::string msg = sw + "\n\n";
  msg += printGuesses();
  if (guesses.back() == sw) {
    msg += "\nCongrats! You got it in ";
    msg += std::to_string(guessCount());
    if (gameSettings.guessLimit != 0)
      msg += "/" + std::to_string(gameSettings.guessLimit);
    msg += " guesses!\n\n";
  }
  else {
    msg += "\nSorry! You've used ";
    msg += std::to_string(guessCount()) + '/';
    msg += std::to_string(gameSettings.guessLimit);
    msg += " guesses!\n\n";
  }
  msg += "Press enter to continue...\n";

  WordleResponse::waitForEnter(msg, gameSettings.debugMode);
}

bool WordleGame::keepPlaying()
{
  std::string msg = "Enter 'y' to keep playing, enter 'q' to quit\n";
  return WordleResponse::getBoolResponse(msg, 'y', 'q', gameSettings.debugMode);
}

void WordleGame::reset()
{
  guesses.clear();
  wrongLetters.clear();

  gameSettings.load();
  setWordSize();
  loadWordList();
}
