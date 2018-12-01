#include <stdio.h>
#include <stdlib.h>

void enregilecturestrer(){
	FILE *fic;
    float taillemoyfileattente
    int taillemaxfile
    float debitmoyen            //nombre moyen de client par minute
    int tauxclientnonservis
    


	fic = fopen("fichier.txt", "w");


    while(fic != NULL)
    {
        fscanf(fic, "%s, %s, %s, %s", &dateArrive, &dureAttente, &dateDebutService, &dateFinService);
        fseek(fic, +1, SEEK_CUR);


        
    }




	fprintf(fic, "%s, %s, %s, %s\n", dateArrive, dureAttente, dateDebutService, dateFinService);


	fclose(fic);
}