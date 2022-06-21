#ifndef _QUARTO_H_
#define _QUARTO_H_

#include "save.h"
#include "board.h"

#define NB_PIECE DIMENSION*DIMENSION

/**
 * @file quarto.c
 * @brief Quarto game project.
 * @author DENNETIERE Célia, LEBRASSEUR Thibaud TD1, TP2.
 */

/**
 * @brief display the title of the game.
 * 
 * Getchar() and the while is a way to clear the buffer and not start a game with an error if the user type something before pressing enter. 
 */
void affiche_titre();

/**
 * @brief create an array of all the pieces of the game.
 *
 * The principle is that it fills the array with the total pieces of the game (NOT just the available one).
 *
 * @param liste_piece : the array in which the piece will be put inside.
 */
void liste_pieces(piece liste_piece[]);

/**
 * @brief display the piece given (according to its characteristics).
 *
 * @param p : the piece to display
 */
void afficher_piece(piece p);

/**
 * @brief display only the pieces available to place.
 *
 * The principle is that it tests for each piece if is_present() on board returns false, then the piece can be played.
 *
 * @param game : the board on which the request is made
 * @param liste_piece : the list of all the pieces of the game
 * @return the number of pieces left to play.
 */
int afficher_pieces_restantes(board game, piece liste_piece[]);

/**
 * @brief display the board of the game with the pieces played on it.
 * 
 * Show special pieces : 'SAVE' and 'LOAD' in order to save and load a game.
 *
 * @param game the board on which the request is made.
 */
void affichage(board game);

/**
 * @brief Ask the player which piece they want to give to the other player.
 *
 * Check if the value entered is between 1 and 16, if it's a character or integer and clear buffer, to only show one single error per carriage return from scanf()
 *
 * @return the id of the piece chosen.
 */
int demande_piece();

/**
 * @brief Ask the player in which column they want to place their piece.
 *
 * Check if the value entered is between 1 and 4, 
 * if it's a character or integer and clear buffer, to only show one single error per carriage return from scanf()
 * 
 * Check if the value entered is 20 or 30, in order to save and load.
 * Save and load only work during the demande_piece() function, not in demande_colonne() or demande_ligne().
 *
 * @return the number of the column chosen.
 */
int demande_colonne();

/**
 * @brief Ask the player in which line they want to place their piece.
 *
 * A, B, C, D and a, b, c, d both work (by using values from the ASCII table)
 *
 * @return the number of the line chosen.
 */
int demande_ligne();

 /**
  * @brief Ask to 2 players to enter their nickname
  * 
  * @param noms : nicknames will be placed this characters array.
  * 
  */
void demander_nom(char noms[2][30]);

/**
 * @brief ask the players witch piece to place and its position. 
 * 
 * It also test the possible errors link to a piece (if it is already 
 * placed or if the space is already occupied.
 * It uses the functions described just above to work and also the 
 * number of round to know which player is playing at the moment.
 *
 * @param game : the board on which the request is made
 * @param liste_piece : the list of all the pieces of the game
 * @param num_tour : the numbers of round that already have passed
 * @param noms : players nicknames
 */
void choix_piece(board game, piece liste_piece[], int num_tour, char nom[2][30]);

 /**
  * @brief function that initiate :
  * 	the board
  * 	the players names
  * 	the num_tour
  * 
  * 	and start the game.
  */

void initialisation();

/**
 * @brief the main function that runs the game and proceed to manage the rounds.
 *
 * It uses all the implemented functions to display the game, asking the
 * players the piece and position they want to play it. It manages their 
 * turns of play. It also manage the end of the game (tie or win for one of the player).
 */
void quarto(board game, char noms[][30], int num_tour);

/**
 * @brief Ask the players if they to retry a game.
 *
 * The numbers that are compared are the ASCII value of y, Y, n, N.
 * 
 * It checks if the character entred is a y or Y, then call quarto() to rerun
 * If it's a n or N then, exit the function, after, this programm will close.
 * We clear the scanf buffer before entering a new game to not damage the next game, and when it's wrong typped.
 * 
 * @return the answer of the user by an int (0 : no, 1 : yes).
 */
int retry();

/**@}*/

#endif /*_QUARTO_H_*/
