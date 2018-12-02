#include <stdio.h>
#include <stdlib.h>
#include "lecture.h"







void tableaudebord(Metriques metriques){              //metriques est un tableau de taille 5
	FILE *fic;
    float taillemoyfileattente = metriques.taillemoyfileattente;
    int taillemaxfile = metriques.taillemaxfile;
    float debitmoyen = metriques.debitmoyen;
    int tauxclientnonservis = metriques.tauxclientnonservis;
    float tempsreponsemoy = metriques.tempsreponsemoy;

    


	fic = fopen("tableaudebord.txt", "w");

	fprintf(fic, "Metriques journalieres:\n\n");
    fprintf(fic, "Taille moyenne de la file d'attente: %f personnes\n", taillemoyfileattente);
    fprintf(fic, "Taille maximum de la file d'attente: %d personnes\n", taillemaxfile);
    fprintf(fic, "Debit moyen: %f personnes\n", debitmoyen);
    fprintf(fic, "Taux de clients non servis: %d personnes\n", tauxclientnonservis);
    fprintf(fic, "Temps de traitement moyen: %f minutes\n", tempsreponsemoy);


	fclose(fic);
}