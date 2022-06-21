#include <stdio.h>
#include <stdlib.h>
#include "leaderboard.h"

struct personne* read_lb(int* longueur){
	FILE* fichier = fopen("leaderboard.txt","r");
	
	int win, lose, line = 0;
	int comp = 0;
	char ch ='a';
	
	//get the number of line in the file (which is used to know the number of player in the leaderboard)
	while(!feof(fichier)){
		ch = fgetc(fichier);
		if(ch == '\n'){
			line++;
		}
	}
	*longueur = line;
	
	struct personne* joueurs = malloc(line*sizeof(struct personne));
	fclose(fichier);
	
	//open again the file from the start
	fichier = fopen("leaderboard.txt","r");
	//retrieve data on players (stored in struct)
	while(!feof(fichier)){
		///name retrieval
		struct personne pers;
		
		fscanf(fichier, "%[^\n]%*c", pers.nom);
		///number of win/lost game retrieval
		fscanf(fichier, "%d", &win);
		fscanf(fichier, "%d", &lose);
		
		pers.partieG = win;
		pers.partieP = lose;
		
		joueurs[comp] = pers;
		comp ++;
	}
	fclose(fichier);
	return joueurs;
}

void has_win(struct personne* pers, int indice){
	pers[indice].partieG += 1; 
}

void has_lost(struct personne* pers, int indice){
	pers[indice].partieP += 1; 
}

void write_lb(struct personne* liste_pers, int taille){
	FILE* fichier = fopen("leaderboard.txt","w");
	
	for(int i = 0; i< taille; i+=2){
		fprintf(fichier, "%s\n", liste_pers[i].nom );
		fprintf(fichier, "%d %d\n", liste_pers[i].partieG, liste_pers[i].partieP);
	}
	fclose(fichier);
}

void add_lb(struct personne pers){
	FILE* fichier = fopen("leaderboard.txt","a");
	
	fprintf(fichier, "%s\n", pers.nom );
	fprintf(fichier, "%d %d\n", pers.partieG, pers.partieP);
	
	fclose(fichier);
}

void trier(struct personne *p, int taille){
	struct personne tmp; int nb_ech = 1;
	while(nb_ech){
		nb_ech = 0;
		for(int i=0; i<taille-1; i++){
			if(p[i].partieG-p[i].partieP < p[i+1].partieG-p[i+1].partieP){ //sort by the score (= win-lose)
				tmp = p[i];
				p[i] = p[i+1];
				p[i+1] = tmp;
				nb_ech = 1;
			}
		}
	}
}

void display_lb(struct personne* p, int line){
	printf("\e[0;38;5;178m"); //change the color of the displayed text
	printf("╔══════════════════════════════════════════════════════════════╗\n");
	printf("║_.~\"~._.~\"~._.~\"~._.~\"~._Leaderboard_.~\"~._.~\"~._.~\"~._.~\"~.. ║\n");
	printf("╠══════╦════════════════════════════════╦═══════╦══════╦═══════╣\n");
	printf("║ Rank ║              Name              ║ Score ║ Wins ║ Loses ║\n");
	printf("╠══════╬════════════════════════════════╬═══════╬══════╬═══════╣\n");
	
	for(int i=0; i<line; i = i+2){
		printf("║ %4d ║ %30s ║ %5d ║ %4d ║ %5d ║\n", (i/2)+1, p[i].nom, p[i].partieG-p[i].partieP, p[i].partieG, p[i].partieP);
	}
	
	printf("╚══════╩════════════════════════════════╩═══════╩══════╩═══════╝\n");
}
