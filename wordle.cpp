#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "WordleString.hpp"
#include "WordleGame.hpp"
using namespace std;

int main()
{
  srand(time(NULL));

  WordleGame game;
  WordleString guess;
  string secretWord;
  do {
    guess.clear();
    game.reset();
    secretWord = game.selectSecretWord(rand());
    do {
      do {
        guess = game.getUserGuess();
      } while (!game.confirmUserGuess(guess));

      guess.evaluate(secretWord);
      game.addGuess(guess);
    } while (guess != secretWord);
    game.displayWin(secretWord);
  } while (game.keepPlaying());

  system("clear");

  return 0;
}
