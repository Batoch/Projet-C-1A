#include <stdio.h>
#include <stdlib.h>

void enregistrer(int dateArrive, int dureAttente, int dateDebutService, int dateFinService){
	FILE *fic;


	fic = fopen("fichier.txt", "w");

	fprintf(fic, "%s, %s, %s, %s\n", dateArrive, dureAttente, dateDebutService, dateFinService);


	fclose(fic);
}