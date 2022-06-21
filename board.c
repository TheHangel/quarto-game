#include "board.h"
#include <stdlib.h>
#include <stdio.h>

struct piece_t{
	enum size taille;
	enum shape forme;
	enum color couleur;
	enum top surface;
};

struct board_t{
	piece plateau[DIMENSION][DIMENSION];
};

board new_game(){
	board jeu = (struct board_t*)malloc(sizeof(struct board_t));
	for(int i =0; i < DIMENSION; i++){
		for(int j =0; j < DIMENSION; j++){
			jeu->plateau[i][j] = NULL; //it initializes each piece
		}
	}
	return jeu;
}

board copy_game(board original_game){
	board copie = (struct board_t*)malloc(sizeof(struct board_t));
	for (int i =0; i < DIMENSION; i++){
		for (int j =0; j < DIMENSION; j++){
			copie->plateau[i][j] = original_game->plateau[i][j];
		}
	}
	return copie;
}

void destroy_game(board game){
	free(game->plateau);
}

bool is_occupied(board game, int line, int column){
	return !(game->plateau[line][column] == NULL);
}

piece get_piece(board game, int line, int column){
	piece p = game->plateau[line][column];
	return p;
}

enum size piece_size(piece a_piece){
	if(a_piece == NULL){ //this avoids "segmentation fault" errors
		return 0;
	}
	return a_piece->taille;
}

enum shape piece_shape(piece a_piece){
	if(a_piece == NULL){
		return 0;
	}
	return a_piece->forme;
}

enum color piece_color(piece a_piece){
	if(a_piece == NULL){
		return 0;
	}
	return a_piece->couleur;
}

enum top piece_top(piece a_piece){
	if(a_piece == NULL){
		return 0;
	}
	return a_piece->surface;
}

bool has_winner(board game){
	//NO-SE diagonal check
	int i = 1;
	if(get_piece(game, i, i)!=NULL && get_piece(game, i+1, i+1)!=NULL && get_piece(game, i+2, i+2)!=NULL && get_piece(game, i-1, i-1)!=NULL){ //if one of the piece equals NULL, 
																																			  //the line can't check win condition
		if(piece_color(game->plateau[0][0]) == piece_color(game->plateau[i][i]) &&
		   piece_color(game->plateau[0][0]) == piece_color(game->plateau[i+1][i+1]) &&
		   piece_color(game->plateau[0][0]) == piece_color(game->plateau[i+2][i+2])){ //test if the color of all the pieces of the diagonal are the same
			return 1;
		}
		if(piece_shape(game->plateau[0][0]) == piece_shape(game->plateau[i][i]) &&
		   piece_shape(game->plateau[0][0]) == piece_shape(game->plateau[i+1][i+1]) &&
		   piece_shape(game->plateau[0][0]) == piece_shape(game->plateau[i+2][i+2])){
			return 1;
		}
		if(piece_top(game->plateau[0][0]) == piece_top(game->plateau[i][i]) &&
		   piece_top(game->plateau[0][0]) == piece_top(game->plateau[i+1][i+1]) &&
		   piece_top(game->plateau[0][0]) == piece_top(game->plateau[i+2][i+2])){
			return 1;
		}
		if(piece_size(game->plateau[0][0]) == piece_size(game->plateau[i][i]) &&
		   piece_size(game->plateau[0][0]) == piece_size(game->plateau[i+1][i+1]) &&
		   piece_size(game->plateau[0][0]) == piece_size(game->plateau[i+2][i+2])){
			return 1;
		}
	}
	//NE-SO diagonal check
	if(get_piece(game, i-1, i+2)!=NULL && get_piece(game, i, i+1)!=NULL && get_piece(game, i+1, i)!=NULL && get_piece(game, i+2, i-1)!=NULL){
		if(piece_color(game->plateau[0][3]) == piece_color(game->plateau[i][i+1]) &&
		   piece_color(game->plateau[0][3]) == piece_color(game->plateau[i+1][i]) &&
		   piece_color(game->plateau[0][3]) == piece_color(game->plateau[i+2][i-1])){
			return 1;
		}
		if(piece_shape(game->plateau[0][3]) == piece_shape(game->plateau[i][i+1]) &&
		   piece_shape(game->plateau[0][3]) == piece_shape(game->plateau[i+1][i]) &&
		   piece_shape(game->plateau[0][3]) == piece_shape(game->plateau[i+2][i-1])){
			return 1;
		}
		if(piece_top(game->plateau[0][3]) == piece_top(game->plateau[i][i+1]) &&
		   piece_top(game->plateau[0][3]) == piece_top(game->plateau[i+1][i]) &&
		   piece_top(game->plateau[0][3]) == piece_top(game->plateau[i+2][i-1])){
			return 1;
		}
		if(piece_size(game->plateau[0][3]) == piece_size(game->plateau[i][i+1]) &&
		   piece_size(game->plateau[0][3]) == piece_size(game->plateau[i+1][i]) &&
		   piece_size(game->plateau[0][3]) == piece_size(game->plateau[i+2][i-1])){
			return 1;
		}
	}
	
	for(i=0; i< DIMENSION; i++){
		
		//Line check
		if(get_piece(game, i, i) != NULL){ //if this piece equals NULL, the line nor the column can fufill a win condition, there is no need to test them
			if(get_piece(game, i, 0)!=NULL && get_piece(game, i, 1)!=NULL && get_piece(game, i, 2)!=NULL && get_piece(game, i, 3)!=NULL){
				int line = i;
				int column = 1;
				if(piece_color(game->plateau[line][0]) == piece_color(game->plateau[line][column]) &&
				   piece_color(game->plateau[line][0]) == piece_color(game->plateau[line][column+1]) &&
				   piece_color(game->plateau[line][0]) == piece_color(game->plateau[line][column+2])){ //test if the color of all the pieces of the diagonal are the same
					return 1;
				}
				if(piece_shape(game->plateau[line][0]) == piece_shape(game->plateau[line][column]) &&
				   piece_shape(game->plateau[line][0]) == piece_shape(game->plateau[line][column+1]) &&
				   piece_shape(game->plateau[line][0]) == piece_shape(game->plateau[line][column+2])){
					return 1;
				}
				if(piece_top(game->plateau[line][0]) == piece_top(game->plateau[line][column]) &&
				   piece_top(game->plateau[line][0]) == piece_top(game->plateau[line][column+1]) &&
				   piece_top(game->plateau[line][0]) == piece_top(game->plateau[line][column+2])){
					return 1;
				}
				if(piece_size(game->plateau[line][0]) == piece_size(game->plateau[line][column]) &&
				   piece_size(game->plateau[line][0]) == piece_size(game->plateau[line][column+1]) &&
				   piece_size(game->plateau[line][0]) == piece_size(game->plateau[line][column+2])){
					return 1;
				}
			}
			
			//Column check
			if(get_piece(game, 0, i)!=NULL && get_piece(game, 1, i)!=NULL && get_piece(game, 2, i)!=NULL && get_piece(game, 3, i)!=NULL){
				int line = 1;
				int column = i;
				if(piece_color(game->plateau[0][column]) == piece_color(game->plateau[line][column]) &&
				   piece_color(game->plateau[0][column]) == piece_color(game->plateau[line+1][column]) &&
				   piece_color(game->plateau[0][column]) == piece_color(game->plateau[line+2][column])){
					return 1;
				}
				if(piece_shape(game->plateau[0][column]) == piece_shape(game->plateau[line][column]) &&
				   piece_shape(game->plateau[0][column]) == piece_shape(game->plateau[line+1][column]) &&
				   piece_shape(game->plateau[0][column]) == piece_shape(game->plateau[line+2][column])){
					return 1;
				}
				if(piece_top(game->plateau[0][column]) == piece_top(game->plateau[line][column]) &&
				   piece_top(game->plateau[0][column]) == piece_top(game->plateau[line+1][column]) &&
				   piece_top(game->plateau[0][column]) == piece_top(game->plateau[line+2][column])){
					return 1;
				}
				if(piece_size(game->plateau[0][column]) == piece_size(game->plateau[line][column]) &&
				   piece_size(game->plateau[0][column]) == piece_size(game->plateau[line+1][column]) &&
				   piece_size(game->plateau[0][column]) == piece_size(game->plateau[line+2][column])){
					return 1;
				}
			}
		}
	}
	return 0;
}

bool is_present_on_board(board game, piece a_piece){
	for(int l=0; l<DIMENSION; l++){
		for(int c=0; c<DIMENSION; c++){
			if (a_piece != NULL){
				if (game->plateau[l][c] != NULL){ //A NULL piece is equal to the "0,0,0,0" piece if caracteristics are taken separately, it must be avoided 
					if (piece_size(a_piece) == piece_size(game->plateau[l][c]) &&
						piece_shape(a_piece) == piece_shape(game->plateau[l][c]) &&
						piece_color(a_piece) == piece_color(game->plateau[l][c]) &&
						piece_top(a_piece) == piece_top(game->plateau[l][c])){
							return 1;
					}
				}
			}
			else if(game->plateau[l][c] == a_piece){ //We check this with NULL piece because only if each caracteristics are taken separately, NULL piece equals the "0,0,0,0" piece
				return 1;
			}
		}
	}
	return 0;
}

enum return_code place_piece(board game, int line, int column, piece a_piece){
	if(game->plateau[line][column] != NULL || 	//this place is already occupied
	   line < 0 || line > DIMENSION-1 ||		//the line is out of the board
	   column < 0 || column > DIMENSION-1){		//the column is out of the board
		return POSITION;
	}
	if(is_present_on_board(game, a_piece)){ 	//the selected piece is already placed
		return PIECE;
	}
	game->plateau[line][column] = a_piece;
	return SUCCESS;
}

piece get_piece_from_characteristics(enum size a_size, enum shape a_shape, enum color a_color,  enum top a_top){
	piece p_res = (struct piece_t*)malloc(sizeof(struct piece_t));
	p_res->taille = a_size;
	p_res->forme = a_shape;
	p_res->couleur = a_color;
	p_res->surface = a_top;
	return p_res;
}
