#ifndef _SAVE_H_
#define _SAVE_H_

#include "board.h"
#include "quarto.h"

/**
 * @file save.c
 * @brief Quarto game project extension.
 * @author DENNETIERE Célia, LEBRASSEUR Thibaud TD1, TP2.
 */


 /**
  * @brief Ask the user to enter a filename, then save the game into this file.
  * 
  * @param game : the current game that has to be saved
  * @param num_tour : number of rounds in order to know who will start the game when loading the game.
  * @param noms : get the registered players names.
  * 
  */
void sauvegarder(board game, int num_tour, char noms[2][30]);


 /**
  * @brief Ask the user to enter the name of a savefile, then load the game into the current game (it erases the current game).
  * 
  */
void load();

/**@}*/

#endif /*_SAVE_H_*/
