#include <stdio.h>
#include <stdlib.h>

void enregilecturestrer(){          //lit le fichier de donnees "fichier.txt" et retourne les metriques 
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

/*definition d'un client non servi:
deuxieme client dont la date de fin de service excede 540
*/
    int j =0;
    while( tabdateFinService[j] > 540)
        j++;
    nbClientsServis = (i-(j+1));
    tauxclientnonservis = nbClientsServis/i;


    int somme = 0;
    for(int j=0; j<i; j++){
        somme += tabdateArrive[j] - tabdateFinService[j];
    }
    tempsreponsemoy = somme/i;





	fclose(fic);

    float metriques[5] = {taillemoyfileattente,taillemaxfile,debitmoyen, tauxclientnonservis, tempsreponsemoy};
    return(metriques);
}
