#include <string>
#include <fstream>
#include "src/WordleResponse.hpp"
#include "src/WordleSettings.hpp"

int main()
{
  WordleSettings s;
  s.load();

  std::string msg;
  std::ofstream ofs(WordleSettings::FILE_NAME);

  // debug mode setting
  if (s.debugMode) {
    msg = "Would you like to continue in debug mode?\n";
    if (WordleResponse::getBoolResponse(msg, 'y', 'n', true))
      s.put<bool>(ofs, WordleSettings::DEBUG_MODE, true);
    else {
      s.debugMode = false;
      s.put<bool>(ofs, WordleSettings::DEBUG_MODE, false);
    }
  }
  else
    s.put<bool>(ofs, WordleSettings::DEBUG_MODE, false);

  msg = "Would you like to use standard Wordle settings?\n";
  if (WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode)) {
    s.repeatedLetters = true;
    s.put<bool>(ofs, WordleSettings::REP_LETTERS, s.repeatedLetters);
    s.wordSize = 5;
    s.put<int>(ofs, WordleSettings::WORD_SIZE, s.wordSize);
    s.guessLimit = 6;
    s.put<int>(ofs, WordleSettings::GUESS_LIMIT, s.guessLimit);
  }
  else {
    // check guess settings
    msg = "Would you like the game to check that your guess is a valid dictionary word?\n";
    msg += "Node: This means that any non-dictionary guesses will be rejected\n";
    s.checkGuess = WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode);
    s.put<bool>(ofs, WordleSettings::CHECK_GUESS, s.checkGuess);

    // repeated letters setting
    msg = "Would you like to allow words with repeated letters?\n";
    s.repeatedLetters = WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode);
    s.put<bool>(ofs, WordleSettings::REP_LETTERS, s.repeatedLetters);

    // word size setting
    msg = "Would you like to pre-set the game's word length?\n";
    msg += "Note: If you pre-set the word length, you will not be able to change it between games.\n";
    if (WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode)) {
      msg = "Enter the word size you'd like to use.\n";
      msg += "Note: It must be a number between 4 and 7.\n";
      s.wordSize = WordleResponse::getIntResponse(msg, 4, 7, s.debugMode);
      s.put<int>(ofs, WordleSettings::WORD_SIZE, s.wordSize);
    }
    else
      s.put<int>(ofs, WordleSettings::WORD_SIZE, 0);

    // guess limit setting
    msg = "Would you like to set a guess limit?\n";
    if (WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode)) {
      msg = "Please enter the guess limit you'd like to use.\n";
      msg += "(Or enter 0 not to use one)\n";
      s.guessLimit = WordleResponse::getIntResponse(msg, 0, UINT_MAX, s.debugMode);
    }
    else
      s.guessLimit = 0;
    s.put<int>(ofs, WordleSettings::GUESS_LIMIT, s.guessLimit);
  }

  // all done
  msg = "Game settings have been updated!\n\nPress enter to close this program...\n";
  WordleResponse::waitForEnter(msg, s.debugMode);
  if (!s.debugMode) system("clear");

  return 0;
}
