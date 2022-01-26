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
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  for (const std::string& s : wordList)
    if (WordleString(word) == s)
      return true;
  return false;
}

bool WordleGame::guessLimit() const
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  return (gameSettings.guessLimit() == 0) ||
         (guesses.size() < gameSettings.guessLimit());
}

bool WordleGame::goodGuess(const WordleString& ws) const
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  if (ws == WordleResponse::INVALID_SIZE)
    return false;

  if (gameSettings.checkGuess()) {
    if (validWords.empty())
      throw std::string("ERROR: (") + __func__ + ") Dictionary is empty";
    else
      return (validWords.find(ws.asString()) != validWords.end());
  }

  return true;
}

std::string WordleGame::printGuesses() const
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  std::string s = "";
  for (const WordleString& ws : guesses) s += ws.print();
  return s;
}

std::string WordleGame::printWrongLetters() const
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

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
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  if (gameSettings.wordSize() == 0) {
    std::string msg = "Would you like to play with 4, 5, 6, or 7 letter words?\n";
    wsz = WordleResponse::getIntResponse(msg, 4, 7, gameSettings.debugMode());
  }
  else
    wsz = gameSettings.wordSize();
}

void WordleGame::loadWordList()
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  WordleString ws;

  wordList.clear();
  std::ifstream lin("csv/" + std::to_string(wsz) + "-list.csv");
  while (lin >> ws) {
    if (gameSettings.repeatedLetters())
      wordList.push_back( ws.asString() );
    else if (!ws.repeatedLetters())
      wordList.push_back( ws.asString() );
  }

  if (wordList.empty())
    throw std::string("ERROR: (") + __func__ + ") Word list is empty";

  validWords.clear();
  std::ifstream din("csv/" + std::to_string(wsz) + "-dict.csv");
  while (gameSettings.checkGuess() && din >> ws)
    validWords.insert(ws.asString());

  if (gameSettings.checkGuess() && validWords.empty())
    throw std::string("ERROR: (") + __func__ + ") Dictionary is empty";
}

void WordleGame::selectSecretWord(uint r)
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  if (wordList.empty())
    throw std::string("ERROR: (") + __func__ + ") Word list is empty";
  else
    sw = wordList[ r % wordList.size() ];
}

WordleString WordleGame::getUserGuess()
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  WordleString guess;
  do {
    if (!gameSettings.debugMode()) system("clear");

    std::string msg = printWrongLetters();
    if (!wrongLetters.empty()) msg += '\n';
    msg += printGuesses();
    if (!guesses.empty()) msg += '\n';

    if (!guess.empty()) {
      if (guess == WordleResponse::INVALID_SIZE)
        msg += "Guess must be " + std::to_string(wsz) + " letters\n\n";
      else
        msg += "Not a valid word\n\n";
    }

    msg += "Guess #" + std::to_string(guessCount()+1) + '\n';
    guess = WordleResponse::getStringResponse(msg, wsz, gameSettings.debugMode());
  } while (!goodGuess(guess));

  return guess;
}

bool WordleGame::confirmUserGuess(const WordleString& ws)
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  std::string msg = "";
  msg += printWrongLetters();
  if (!wrongLetters.empty()) msg += '\n';
  msg += printGuesses();
  if (!guesses.empty()) msg += '\n';
  msg += ws.print();
  msg += "(Colors are currently hidden)\n\nConfirm this guess?\n";

  return WordleResponse::getBoolResponse(msg, 'y', 'n', gameSettings.debugMode());
}

void WordleGame::addGuess(const WordleString& ws)
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  guesses.push_back(ws);

  for (int i = 0; i < ws.size(); i++)
    if (ws[i].color == WordleChar::Color::white)
      wrongLetters.insert(ws[i].letter);
}

void WordleGame::endDisplay()
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  std::string msg = sw + "\n\n";
  msg += printGuesses();
  if (guesses.back() == sw) {
    msg += "\nCongrats! You got it in ";
    msg += std::to_string(guessCount());
    if (gameSettings.guessLimit() != 0)
      msg += "/" + std::to_string(gameSettings.guessLimit());
    msg += " guesses!\n\n";
  }
  else {
    msg += "\nSorry! You've used ";
    msg += std::to_string(guessCount()) + '/';
    msg += std::to_string(gameSettings.guessLimit());
    msg += " guesses!\n\n";
  }
  msg += "Press enter to continue...\n";

  WordleResponse::waitForEnter(msg, gameSettings.debugMode());
}

bool WordleGame::keepPlaying()
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  std::string msg = "Enter 'y' to keep playing, enter 'q' to quit\n";
  return WordleResponse::getBoolResponse(msg, 'y', 'q', gameSettings.debugMode());
}

void WordleGame::reset()
{
  if (gameSettings.debugMode()) std::cout << "__" << __func__ << "__\n";

  guesses.clear();
  wrongLetters.clear();

  gameSettings.load();
  setWordSize();
  loadWordList();
}
