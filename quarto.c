#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quarto.h"
#include "leaderboard.h"
#include "save.h"

void affiche_titre(){
	printf("\e[1;1H\e[2J"); //clear the display
    printf("\e[0;38;5;82m                           _        \n");
    printf("\e[0;38;5;82m  ____ _   _ _____  ____ _| |_ ___  \n");
    printf("\e[0;38;5;178m / _  | | | (____ |/ ___|_   _) _ \\ \n");
    printf("\e[0;38;5;178m| |_| | |_| / ___ | |     | || |_| |\n");
    printf("\e[0;38;5;39m \\__  |____/\\_____|_|      \\__)___/ \n");
    printf("\e[0;38;5;39m    |_|                             \n");
    printf("\n");
    
    //display the leaderboard
    int line;
	struct personne* pers = read_lb(&line);
	trier(pers, line);
	display_lb(pers, line);
	free (pers);
    
    printf("\n\e[0;38;5;82mType 1 to start a new game.\n");
    printf("\e[0;38;5;82mType 2 to load a game.\n");
    int nb_choisi = 3;
    while(!(nb_choisi == 1 || nb_choisi == 2)){
		while(!(scanf("%d",&nb_choisi))){
			getchar();
		}
	}
	if(nb_choisi == 2){
		load();
		exit(0);
	}
	char c=0;
	while (c!='\n') { //clear the buffer to not start the game with an error if the user typed something before pressing enter.
		scanf("%c", &c);
	}
}

void liste_pieces(piece liste_piece[]){
	int n = 1;
	int comp = 0;
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			for(int k=0; k<=n; k++){
				for(int l=0; l<=n; l++){
					liste_piece[comp] = get_piece_from_characteristics(j, i, k, l);
					comp ++;
				}
			}
		}
	}
}

void afficher_piece(piece p){
	if(piece_color(p) == RED){
		if(piece_shape(p) == SQUARE){
			if(piece_size(p) == TALL){
				printf("⬜⬜");
			}
			else{
				printf("⬜  ");
			}
		}
		else{
			if(piece_size(p) == TALL){
				printf("⚪⚪");
			}
			else{
				printf("⚪  ");
			}
		}
	}
	else{
		if(piece_shape(p) == SQUARE){
			if(piece_size(p) == TALL){
				printf("⬛⬛");
			}
			else{
				printf("⬛  ");
			}
		}
		else{
			if(piece_size(p) == TALL){
				printf("⚫⚫");
			}
			else{
				printf("⚫  ");
			}
		}
	}
	if(piece_top(p) == HOLLOW){
		printf("❌");
	}
	else{
		printf("  ");
	}
}

int afficher_pieces_restantes(board game, piece liste_piece[]){
	int comp_piece = 0;
	printf("\e[0;38;5;39m"); //change the color of the displayed text
	for(int i = 0; i< 16; i++){
		if (i%4 == 0 && i !=0){ //With this, pieces are displayed 4 by 4
			printf("||\n");
		}
		if(is_present_on_board(game, liste_piece[i]) == 0){
			printf(" ||%2d|", i+1);
			afficher_piece(liste_piece[i]);
			comp_piece ++;
		}
		else{
			printf(" ||%2d|      ", i+1);
		}
	}
	printf("||\n");
	printf(" ||20|SAVE   ||30|LOAD   ||\n");
	return comp_piece;
}

void affichage(board game){
	printf("\e[0;38;5;178m"); //change the color of the displayed text
    printf("     1      2      3      4\n");
    printf("  ╔══════╦══════╦══════╦══════╗\n");
    
    for (int i=0 ; i < 4; i++){
        printf("%2c║", i+65);
        
        for(int j=0; j<4; j++){
            if(is_occupied(game, i, j)){ //for each column of each line, it searches if there is a need to display a piece
                afficher_piece(get_piece(game, i, j));
                printf("║");
            }
            else{
                printf("      ║");
            }
        }
        printf("\n");
        if(i < 3){
            printf("  ╠══════╬══════╬══════╬══════╣\n");
        }
    }
    printf("  ╚══════╩══════╩══════╩══════╝\n");
    printf("\n");
}

int demande_piece(board game, int num_tour, char noms[2][30]){
	int id = 40; int nb_fois = 0; char c; int has_saved = 0; //nb_fois is used to know if the user made a mistake when choosing the piece
	
	printf("\e[0;38;5;39m"); //change the color of the displayed text
	
	//We check if the number selected is between 1 and the number of pieces (16), (we stay in the loop while it's not)
	while (!(id <= NB_PIECE && id >= 1)){
			
			if(id == 20){ //Check to save
				has_saved = 1; //it's used to avoid displaying the "ERROR" text right after the game is saved
				sauvegarder(game, num_tour, noms);
			}
			else if(id == 30){ //Check to load
				has_saved = 1;
				printf("Are you sure ? This will erase the current game.(y/n)");
				
				char choix_load;
				getchar(); //Check the player answer
				scanf("%c", &choix_load);
				
				if(choix_load == 'y' || choix_load == 'Y'){
					load(game);
				}
			}
			if(nb_fois > 0 && has_saved == 0){
				printf("ERROR, please select a correct number between 1 and 16 !\n");
			}
			printf("Choose a piece : ");

			//We check if the value is a character or a integer, if it's not tell the user that the value is not accepted (ERROR)
			while(!(scanf("%d",&id))){
				getchar();
				
				if(has_saved == 0){
					printf("ERROR, please select a correct number between 1 and 16 !\n");
				}
				//dump most of the memory (exept one that will be cleared by getchar())
				while ((c = getchar()) != '\n' && c != EOF) { }
				printf("Choose a piece : ");
			}
		nb_fois++;
	}
	printf("\n");
	return id;
}

int demande_colonne(){
	int nb_choisi = 10; int nb_fois = 0; char c; //nb_fois is used to know if the user made a mistake when choosing the column
	
	printf("\e[0;38;5;39m"); //change the color of the displayed text
	
	//We check if the number selected is between 1 and the 4 (we stay in the loop while it's not)
	while (!(nb_choisi <= 4 && nb_choisi >= 1)){
		if(nb_fois > 0){
			printf("ERROR, please select a column between 1 and 4.\n");
		}
		printf("Choose the column : ");
		
		//We check if the value is a character or a integer, if it's not tell the user that the value is not accepted (ERROR)
		while(!(scanf("%d",&nb_choisi))){
			getchar();
			printf("ERROR, please select a column between 1 and 4.\n");
			
			//dump most of the memory
			while ((c = getchar()) != '\n' && c != EOF) { }
			printf("Choose the column : ");
		}
		nb_fois++;
	}
	printf("\n");
	return nb_choisi-1;
}

int demande_ligne(){
    char nb_choisi = 70; int nb_fois = 0; //nb_fois is used to know if the user made a mistake when choosing the line
    int recommence=1; char c;
	
	printf("\e[0;38;5;39m"); //change the color of the displayed text
	
	getchar(); //grab the last char taken by scanf() in oder to clear the buffer
	while (recommence){
		if(nb_fois > 0){ 
			printf("ERROR, please select a line between A and D.\n"); 
		}
		printf("Choose the line : ");
		scanf("%c",&nb_choisi);
		
		recommence=0;
		
		//Check if between A and D or a and d (we stay in the loop while it's not)
		if (!((nb_choisi <= 68 && nb_choisi >= 65)||(nb_choisi <= 100 && nb_choisi >= 97))){
			nb_fois=1;
			recommence=1;
		}
		//dump most of the memory
		c=0;
		while (c!='\n') {
			scanf("%c", &c);
		}
	}

	 //this part transforms the character obtained into the corresponding integer
	int en_moins; 
	if(nb_choisi<=68 && nb_choisi>=65){ 
		en_moins = 65; 
	}
	else{
		en_moins = 97; 
	}
	return nb_choisi-en_moins; 
}

void demander_nom(char noms[2][30]){
	//Start with filled names in order to enter the while loop
	strcpy(noms[0], "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	strcpy(noms[1], "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	
	printf("\e[0;38;5;82mWelcome to Quarto ! Type the nickname for both players.\n");
	printf("\n");
	
	for(int i = 0; i < 2; i++){
		while(strlen(noms[i]) >= 30){
			printf("Player %d type your nickname : ", i+1);
			scanf("%[^\n]%*c", noms[i]);
			if(strlen(noms[i]) >= 30){
				printf("The typed nickname is too long (30 max), please retry.\n");
				strcpy(noms[1], "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");		//Fill the nickname again because if Player 1 inputed
																		//a name too  long, Player 2's name  is filled with a
																		//bit of Player 1's name
			}
			printf("\n");
		}
	}
	printf("\e[1;1H\e[2J");
}

void choix_piece(board game, piece liste_piece[], int num_tour, char nom[2][30]){
	printf("Player ");
	printf("%s\n", nom[num_tour%2]);
	
	int id = demande_piece(game, num_tour, nom);
	piece p = liste_piece[id -1];
	
label_error_pos: //Usage of a label to not increase "num_tour" value
	printf("Player ");
	printf("%s\n", nom[(num_tour+1)%2]);
	
	int pos_line = demande_ligne();
	int pos_colonne = demande_colonne();
	
	enum return_code res = place_piece(game, pos_line, pos_colonne, p);
	
	if(res != SUCCESS){
		printf("\e[1;1H\e[2J"); //This string clears the terminal
		affichage(game);
		afficher_pieces_restantes(game, liste_piece);
		printf("\n"); 
		if(res == POSITION){
			printf("\e[0;38;5;39mThe current position is not available. Please try another position.\n");
			goto label_error_pos;
		}
		else if(res == PIECE){
			printf("\e[0;38;5;39mThe current Piece is already on board. Please try another piece.\n");
			choix_piece(game, liste_piece, num_tour, nom);
		}
		printf("\n");
	}
}

void initialisation(){
	printf("\e[1;1H\e[2J");
	
	board game = new_game();
	
	char noms[2][30];
	demander_nom(noms);
	
	int num_tour = 0;
	
	quarto(game, noms, num_tour);
}

void quarto(board game, char noms[][30], int num_tour){
	printf("\e[1;1H\e[2J");
	
	piece liste_piece[NB_PIECE];
	liste_pieces(liste_piece);
	
	int verif_egalite = NB_PIECE;
	
	printf("\e[0;38;5;82mRound n°%d : \n", num_tour+1);
	printf("\n");
	
	//Part where the game loop until someone win or there is no more piece available
	while(has_winner(game) == 0 && verif_egalite > 1){
		affichage(game);
		verif_egalite = afficher_pieces_restantes(game, liste_piece);
		printf("\n");
		choix_piece(game, liste_piece, num_tour, noms);
		num_tour++;
		printf("\e[1;1H\e[2J");
		printf("\e[0;38;5;82mRound n°%d : \n", num_tour+1);
		printf("\n");
	}
	affichage(game);
	verif_egalite = afficher_pieces_restantes(game, liste_piece);
	printf("\n");
	
	if(!(verif_egalite)){
		printf("\e[0;38;5;160mTie!");
	}
	else{
		printf("\e[0;38;5;160m");
		printf("%s", noms[num_tour%2]);
		printf(" won the game\n");
		
		//update the leaderboard
		struct personne pers_a, pers_b;
		int taille, add_pers_a = 0, add_pers_b = 0;
		struct personne* liste_pers = read_lb(&taille);
		
		for(int j = 0; j< 2; j++){
			int found = 0; //it's used to know if the player's name is already registered in the leaderboard
			for(int i = 0; i< taille; i+= 2){
				if(strcmp(noms[(num_tour+j)%2], liste_pers[i].nom) == 0){
					if(j == 0){ //When j = 0, it's the player that has won 
						has_win(liste_pers, i);
					}
					if(j == 1){ //Otherwise it's the one that has lost
						has_lost(liste_pers, i);
					}
					found = 1;
					break;
				}
			}
			if(found == 0){ //if it's a new player
				if(j == 0){
					strcpy(pers_a.nom, noms[(num_tour+j)%2]);
					pers_a.partieG = 1;
					pers_a.partieP = 0;
					add_pers_a = 1;
				}
				if(j == 1){
					strcpy(pers_b.nom, noms[(num_tour+j)%2]);
					pers_b.partieG = 0;
					pers_b.partieP = 1;
					add_pers_b = 1;
				}
			}
		}
		if(add_pers_a == 0 || add_pers_b == 0){ //if both players are knew, there is no need to rewrite the leaderboard
			write_lb(liste_pers, taille);
		}
		if (add_pers_a == 1){
			add_lb(pers_a);
		}
		if(add_pers_b == 1){
			add_lb(pers_b);
		}
		free (liste_pers);
	}
	printf("\n");
	
	destroy_game(game);
}

int retry(){
	char reponse;
	char c=0;
	getchar();
	printf("\e[0;38;5;39mDo you want to retry ?(y/n)");
	scanf("%c", &reponse);
	if(reponse == 'y' || reponse == 'Y'){
		c=0;
		while (c!='\n') {
			scanf("%c", &c);
		}
		return 1;
	}
	else if(reponse == 'n' || reponse == 'N'){
		return 0;
	}
	else{
		c=0;
		while (c!='\n') {
			scanf("%c", &c);
		}
		retry();
		return 0;
	}
}

int main(int args, char **argv){
	affiche_titre();
	int playagain = 1;
	while(playagain){
		initialisation();
		playagain = retry();
	}
	return 0;
}
