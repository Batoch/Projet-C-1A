#include <stdio.h>
#include <stdlib.h>

void enregilecturestrer(){
	FILE *fic;
    float taillemoyfileattente;
    int taillemaxfile;
    float debitmoyen;            //nombre moyen de client par minute
    int tauxclientnonservis;
    float tempsreponsemoy;
    int i = 0;
    int dateArrive;
    int dureAttente;
    int dateDebutService;
    int dateFinService;

	fic = fopen("fichier.txt", "r");

    while(fic != NULL)          //calcul du nombre de clients dans le fichier
    {
        fseek(fic, +1, SEEK_CUR);
        i++;
    }

    fseek(fic, 0, SEEK_CUR);

    int tabdateArrive[i];
    int tabdureAttente[i];
    int tabdateDebutService[i];
    int tabdateFinService[i];

    i = 0;

    while(fic != NULL)
    {
        fscanf(fic, "%d,%d,%d,%d", &dateArrive, &dureAttente, &dateDebutService, &dateFinService);
        fseek(fic, +1, SEEK_CUR);

        tabdateArrive[i] = dateArrive;
        tabdureAttente[i] = dureAttente;
        tabdateDebutService[i] = dateDebutService;
        tabdateFinService[i] = dateFinService;

        i++;


    }


//calcul des metriques
    taillemoyfileattente = 
    
    taillemaxfile =

    debitmoyen = i/510;

    tauxclientnonservis = 


    int somme = 0;
    for(int j, j<i, j++){
        somme += tabdateArrive[i] - tabdateFinService[i];
    }
    tempsreponsemoy = somme/i;





	fclose(fic);

    int metriques[5] = {taillemoyfileattente,taillemaxfile,debitmoyen, tauxclientnonservis, tempsreponsemoy};
    return(metriques);
}
