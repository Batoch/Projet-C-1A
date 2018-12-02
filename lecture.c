#include <stdio.h>
#include <stdlib.h>

typedef struct {float taillemoyfileattente;
int taillemaxfile;
float debitmoyen;
 float tauxclientnonservis;
 float tempsreponsemoy;    } Metriques;

Metriques enregilecturestrer(){          //lit le fichier de donnees "fichier.txt" et retourne les metriques 
	FILE *fic;
    float taillemoyfileattente;
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
        //fseek(fic, +1, SEEK_CUR);
        i++;
    }
 //   fseek(fic, 0, SEEK_CUR);

    int tabdateArrive[i];
    int tabdureAttente[i];
    int tabdateDebutService[i];
    int tabdateFinService[i];

    i = 0; //nombre de client dans la journee

    while(fic != NULL)
    {
        fscanf(fic, "%d,%d,%d,%d", &dateArrive, &dureAttente, &dateDebutService, &dateFinService);
       // fseek(fic, +1, SEEK_CUR);

        tabdateArrive[i] = dateArrive;
        tabdureAttente[i] = dureAttente;
        tabdateDebutService[i] = dateDebutService;
        tabdateFinService[i] = dateFinService;

        i++;


    }


    //calcul des metriques

    //----------------------------------------------
    /*Repertorier des tailles max de file par intervalles entre deux fin de service:

    Le but est de creer un tableau qui donne l historique des tailles de files et leur temps d activite.
    On va ponderer les tailles de liste par le temps ou elles sont effectives
    Deux evenements peuvent podifier la taille de la liste:
        - arrivee d un client -> taille de file +1
        - fin de service d un client -> taille de file -1
        => donc au total 2xi evenements
    */
    int tab_taille_file[2*i];
    tab_taille_file[0] = 0; //a louverture la file est vide
    int temps_effectif_file[2*i];

    //On fabriquer un tableau avec tous les evenements dans l ordre historique avec leur date d apparition
    // comtribution et un autre avec leur contribution a la taille de la file courante:

    int compteur_minute;
    int compteur_arrivee = 0;
    int compteur_fin_service = 0;
    for(int j=0; j<2*i; j++){

        //on distigue different cas suivant qu une liste est vide ou non:

        if( compteur_arrivee <i & compteur_fin_service<i){
        //deux listes non vides

            if(tabdateArrive[compteur_arrivee] <= tabdateFinService[compteur_fin_service]){
            //ie if l evenement courant est une arrivee de client

                tab_taille_file[j+1] =tab_taille_file[j] +1; //taille de la prochaine file
                
                temps_effectif_file[j] = tabdateArrive[compteur_arrivee] - compteur_minute;
                //deduction du temps effectifs de la file a l etat precedent
                
                //maj des compteurs:
                compteur_minute += tabdateArrive[compteur_arrivee];
                compteur_arrivee +=1;

            }else{
            //ie l evenement est une sortie de client

                tab_taille_file[j+1] =tab_taille_file[j] -1; 
                
                temps_effectif_file[j] = tabdateFinService[compteur_fin_service] - compteur_minute;        

                compteur_minute += tabdateFinService[compteur_fin_service];
                compteur_fin_service +=1;
            }

        }else{
        //ie if la liste des arrivees a ete parcourue en entier -> que des sorties now
        //par construction du code tabdateArrive est percourue entierement avant tabdateFinService

            tab_taille_file[j+1] =tab_taille_file[j] -1; 
                
                temps_effectif_file[j] = tabdateFinService[compteur_fin_service] - compteur_minute;        

                compteur_minute += tabdateFinService[compteur_fin_service];
                compteur_fin_service +=1;
            
        }
    }
    
    
    //calcule de taillemoyfileattente et taillemaxfile:

    int taillemaxfile = 0;
    taillemoyfileattente = 0; //baricentre des tailles de files pondere par leurs temps effectifs

    for(int j=0; j<2*i; j++){

        taillemoyfileattente += (float) (tab_taille_file[j]*temps_effectif_file[j]);
        if(taillemaxfile < tab_taille_file[j])
            taillemaxfile = tab_taille_file[j];

    }
    taillemoyfileattente /= (float) compteur_minute; //divise par le temps d ouverture total
    
    //----------------------------------------------

    debitmoyen = ((float) i)/510;

    float nbClientsServis;
    /*definition d'un client non servi:
    deuxieme client dont la date de fin de service excede 540*/
    int j =0;
    while( tabdateFinService[j] > 540)
        j++;
    nbClientsServis = (i-(j+1));
    tauxclientnonservis = nbClientsServis/((float) i);


    int somme = 0;
    for(int j=0; j<i; j++){
        somme += tabdateArrive[j] - tabdateFinService[j];
    }
    tempsreponsemoy =((float) somme) /((float) i);





	fclose(fic);

    Metriques metriques= {taillemoyfileattente,taillemaxfile,debitmoyen, tauxclientnonservis, tempsreponsemoy};
    return(metriques);
}
