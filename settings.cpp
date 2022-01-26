#include <string>
#include <fstream>
#include "src/WordleResponse.hpp"
#include "src/WordleSettings.hpp"

int main()
{
  WordleSettings s;
  s.load();
  std::string msg;

  // debug mode setting
  if (s.debugMode()) {
    msg = "Would you like to continue in debug mode?\n";
    if (WordleResponse::getBoolResponse(msg, 'y', 'n', true))
      s.set<bool>(WordleSettings::DEBUG_MODE, true);
    else {
      s.set<bool>(WordleSettings::DEBUG_MODE, false);
    }
  }
  else
    s.set<bool>(WordleSettings::DEBUG_MODE, false);

  msg = "Would you like to use standard Wordle settings?\n";
  if (WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode())) {
    s.set<bool>(WordleSettings::REP_LETTERS, true);
    s.set<int>(WordleSettings::WORD_SIZE, 5);
    s.set<int>(WordleSettings::GUESS_LIMIT, 6);
  }
  else {
    // check guess settings
    msg = "Would you like the game to check that your guess is a valid dictionary word?\n";
    msg += "Node: This means that any non-dictionary guesses will be rejected\n";
    s.set<bool>(WordleSettings::CHECK_GUESS, WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode()));

    // repeated letters setting
    msg = "Would you like to allow words with repeated letters?\n";
    s.set<bool>(WordleSettings::REP_LETTERS, WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode()));

    // word size setting
    msg = "Would you like to pre-set the game's word length?\n";
    msg += "Note: If you pre-set the word length, you will not be able to change it between games.\n";
    if (WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode())) {
      msg = "Enter the word size you'd like to use.\n";
      msg += "Note: It must be a number between 4 and 7.\n";
      s.set<int>(WordleSettings::WORD_SIZE, WordleResponse::getIntResponse(msg, 4, 7, s.debugMode()));
    }
    else
      s.set<int>(WordleSettings::WORD_SIZE, 0);

    // guess limit setting
    msg = "Would you like to set a guess limit?\n";
    if (WordleResponse::getBoolResponse(msg, 'y', 'n', s.debugMode())) {
      msg = "Please enter the guess limit you'd like to use.\n";
      msg += "(Or enter 0 not to use one)\n";
      s.set<int>(WordleSettings::GUESS_LIMIT, WordleResponse::getIntResponse(msg, 0, UINT_MAX, s.debugMode()));
    }
    else
      s.set<int>(WordleSettings::GUESS_LIMIT, 0);
  }

  // all done
  msg = "Game settings have been updated!\n\nPress enter to close this program...\n";
  WordleResponse::waitForEnter(msg, s.debugMode());
  if (!s.debugMode()) system("clear");

  return 0;
}
