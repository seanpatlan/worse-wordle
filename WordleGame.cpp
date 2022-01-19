#include <fstream>
#include "WordleGame.hpp"

/******************************************************************************/
/************************** CONSTRUCTORS/DESTRUCTORS **************************/
/******************************************************************************/

WordleGame::~WordleGame()
{
  guesses.clear();
  wrongLetters.clear();
}

/******************************************************************************/
/****************************** ACCESS FUNCTIONS ******************************/
/******************************************************************************/

const std::string& WordleGame::selectSecretWord(const int& r) const
{
  if (wordList.empty())
    return "";
  else
    return wordList[ r % wordList.size() ];
}

void WordleGame::printGuesses() const
{
    for (const WordleString& ws : guesses)
      ws.print();
}

void WordleGame::printWrongLetters() const
{
  if (wrongLetters.empty()) return;

  std::cout << "Wrong letters: ";
  for (const char& c : wrongLetters)
    WordleChar(c).print();
  std::cout << "\n";

}

/******************************************************************************/
/***************************** GAMEPLAY FUNCTIONS *****************************/
/******************************************************************************/

void WordleGame::setWordSize()
{
  int n = 0;
  std::string s;
  while (n < 4 || n > 7) {
    system("clear");
    std::cout << "Would you like to play with 4, 5, 6, or 7 letter words? ";
    std::cin >> s;
    n = std::stoi(s);
  }

  wsz = n;
}

void WordleGame::loadWordList()
{
  std::ifstream ifs(std::to_string(wsz) + "-list.txt");
  wordList.clear();

  std::string s;
  while (ifs >> s) wordList.push_back(s);
}

WordleString WordleGame::getUserGuess()
{
  std::string guessString;
  do {
    system("clear");
    printWrongLetters();
    if (!wrongLetters.empty()) std::cout << '\n';
    printGuesses();
    if (!guesses.empty()) std::cout << '\n';

    if (!guessString.empty())
      std::cout << "Guess must be " << wsz << " letters\n";

    std::cout << "Guess #" << guessCount()+1 << "\nEnter your guess here:\n";
    std::cin >> guessString;
  } while (guessString.size() != wsz);

  return WordleString(guessString);
}

bool WordleGame::confirmUserGuess(const WordleString& ws)
{
  std::string response;
  while (true) {
    system("clear");
    printWrongLetters();
    if (!wrongLetters.empty()) std::cout << '\n';
    printGuesses();
    if (!guesses.empty()) std::cout << '\n';
    ws.print();

    std::cout << "(Colors are currently hidden)\n\nConfirm this guess? (y/n) ";
    std::cin >> response;

    if (response == "y" || response == "Y") return true;
    if (response == "n" || response == "N") return false;
  }
}

void WordleGame::addGuess(const WordleString& ws)
{
  guesses.push_back(ws);

  for (int i = 0; i < ws.size(); i++)
    if (ws[i].color == WordleChar::Color::white)
      wrongLetters.insert(ws[i].letter);
}

void WordleGame::displayWin(const std::string& secretWord) const
{
  system("clear");
  std::cout << secretWord << "\n\n";
  printGuesses();
  std::cout << "\nCongrats! You got it in " << guessCount() << " guesses!\n\n";
  std::cout << "Press enter to continue...\n";

  // can't figure out how to avoid putting this twice...
  std::cin.ignore();
  std::cin.ignore();
}

bool WordleGame::keepPlaying()
{
  std::string response;
  while (true) {
    system("clear");
    std::cout << "Enter 'y' to keep playing, enter 'q' to quit... ";
    std::cin >> response;

    if (response == "y" || response == "Y") return true;
    if (response == "q" || response == "Q") return false;
  }
}

void WordleGame::reset()
{
  guesses.clear();
  wrongLetters.clear();

  setWordSize();
  loadWordList();
}
