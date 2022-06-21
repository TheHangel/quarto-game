#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_

#include "quarto.h"

/**
 * @file leaderboard.c
 * @brief Quarto game project extension.
 * @author DENNETIERE Célia, LEBRASSEUR Thibaud TD1, TP2.
 */


/**
 * @brief Represents a player and its number of won and lost game.
 */
struct personne{
	char nom[30];
	int partieG;
	int partieP;
};

/**
 * @brief read the "leaderboard.txt" file and create the struct personne associated with each player.
 *
 * @param longueur : a pointer in with the length of the returned array will be put
 * @return an array with all the saved players (and the number of won and lost games).
 */
struct personne* read_lb(int* longueur);


/**
 * @brief add one to the 'partieG' caracteristics (number of won game).
 *
 * @param pers : an array with all the saved players
 * @param indice : the index of the player that won in the array
 */
void has_win(struct personne* pers, int indice);


/**
 * @brief add one to the 'partieP' caracteristics (number of lost game).
 *
 * @param pers : an array with all the saved players
 * @param indice : the index of the player that lost in the array
 */
void has_lost(struct personne* pers, int indice);


/**
 * @brief write in a "leaderboard.txt" file the new leaderboard (it erase the existing file).
 *
 * @param list_pers : an array with all the saved players
 * @param taille : the length of the array
 */
void write_lb(struct personne* liste_pers, int taille);


/**
 * @brief append at the end of a "leaderboard.txt" file a new player and its scores.
 *
 * @param pers : the player to registered
 */
void add_lb(struct personne pers);


/**
 * @brief sort the array by the score of the players (= win - loss).
 *
 * @param p : an array with all the saved players
 * @param taille : the length of the array
 */
void trier(struct personne *p, int taille);


/**
 * @brief display the leaderboard.
 *
 * @param p : an array with all the saved players
 * @param line : the length of the array
 */
void display_lb(struct personne* p, int line);

/**@}*/

#endif /*_LEADERBOARD_H_*/
