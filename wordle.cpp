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
  try {
    do {
      guess.clear();
      game.reset();
      game.selectSecretWord(rand());
      do {
        do {
          guess = game.getUserGuess();
        } while (!game.confirmUserGuess(guess));

        guess.evaluate(game.secretWord());
        game.addGuess(guess);
      } while (guess != game.secretWord() && game.guessLimit());
      game.endDisplay();
    } while (game.keepPlaying());

    if (!game.settings().debugMode) system("clear");
  }
  catch(const char* errorMessage) {
    if (!game.settings().debugMode) system("clear");
    cout << errorMessage;
  }

  return 0;
}
