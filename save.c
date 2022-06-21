#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"

#define MAX_SIZE 255

void sauvegarder(board game, int num_tour, char noms[2][30]){
	printf("What is the file name : ");
	char filename[MAX_SIZE] = "";
	scanf("%s", filename);
	FILE *file = fopen(filename, "w");
	
	fprintf(file, "%d\n", num_tour);
	fprintf(file, "%s\n", noms[0]);
	fprintf(file, "%s\n", noms[1]);
	
	//for each not "null" piece, its caracteristics are written in this exact order : the size, shape, color and top
	for(int l=0; l<DIMENSION; l++){
		for(int c=0; c<DIMENSION; c++){
			if(get_piece(game, l, c) != NULL){
				fprintf(file, "%d", piece_size(get_piece(game, l, c)));
				fprintf(file, "%d", piece_shape(get_piece(game, l, c)));
				fprintf(file, "%d", piece_color(get_piece(game, l, c)));
				fprintf(file, "%d ", piece_top(get_piece(game, l, c)));
			}
			else{
				fprintf(file, "N "); // 'N' means "no piece" in the file
			}
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

void load(){
	char str[MAX_SIZE];
	char buffer;
	
label_error_file:
	while(buffer != '\n'){
		scanf("%c", &buffer);
	}

	printf("What is the file to load ? ");
	scanf("%[^\n]%*c", str);
	FILE* fichier = fopen(str,"r");
	
	if(fichier == NULL){ //if the file can't be found or open
		printf("ERROR, ");
		while ( getchar() != '\n' );
		goto label_error_file;
	}

	int nbtour, i = 0;
	char c =0;

	//Get the number of rounds
	fscanf(fichier, "%d", &nbtour);
	c = fgetc(fichier);
	//c = fgetc(fichier);

	//Get players names
	char noms[2][30];

	for(int j=0; j<=1; j++){
		while((c = fgetc(fichier)) !='\n'){
			if(c !=13){
				noms[j][i] = c;
				i++;
			}
		}
		noms[j][i] ='\0';
		i = 0;
	}

	//Get saved board
	board game = new_game();

	int var1, var2, var3, var4;
	int lin = 0, col = 0;

	while( !feof(fichier)){
		c = fgetc(fichier);
		if (c==' '){
			col ++;
		}
		else if (c=='1' || c == '0'){
			//get each caracteristics of the piece to place
			var1 = c -'0';
			var2 = fgetc(fichier) - '0';
			var3 = fgetc(fichier) - '0';
			var4 = fgetc(fichier) - '0';
			piece p = get_piece_from_characteristics(var1, var2, var3, var4);
			place_piece(game, lin, col, p);
		}
		else if(c != 'N'){ //if there is a new row
			lin ++;
			col = 0;
		}
	}
	fclose(fichier);

	//Start a new game using the data from the file
	//Reading the file works like initialisation() from quarto.c but using the data from the file.
	quarto(game, noms, nbtour);
	exit(0);
}
