#include <stdio.h>
#include <stdlib.h>
#include <math.h>					//biblio mathematique ajouter -lm a la compilation
#include <time.h>
#include <stdbool.h>
#include "miseenpage.h"
#include "lecture.h"

/*utilisation de gdb pour debbuger:
compiler avec l'option -g: gcc -g code.c -lm
puis run le fichier cree a.out et si erreur taper la commande: gdb ./a.out
puis: r -> run et bt -> backtrace
*/

//intervalle d ouveture en temps: 8h30 a 17h30 -> 540min

typedef struct _Client {int date_arrivee;
						int duree_attente;
						int date_fin;
						struct _Client* suivant;	} Client;


typedef struct {Client* pTete;} ListeClient;

/* JUSTIFICATION: 
On utilise une liste chainee afin de pouvoir ajouter des clients sans limite de taille
*/


double aleatoire(double a, double b);
void insertion(Client* pNouveau_client, ListeClient* pMa_liste);
void affichage(ListeClient* pMa_liste);
void calcule(int min, int max, ListeClient* pMa_liste); //calcules les caracteistiques des clients de la liste
void enregistreListeJournaliere(ListeClient* pMa_liste);

//--------------------------------------------------------------------



int main(){
	int temps = 0;
	double lambda = 0.1;
	int min = 5; int max =20;

	srand(time(NULL)); // initialisation de rand pour avoir des valeur alatoire

	ListeClient ma_liste;
	ma_liste.pTete = NULL;
	
	temps += (int) (-log(1-aleatoire(0,1))/lambda); //variable aleatoire exponentielle

	while(temps < 510){	//540 -30 min -> interdiction d arriver 30min avant la fermeture

		//creation d un client:
		Client* pNouveau_client = malloc(sizeof(Client)); //reserve de la place memoire
		//actualisation du temps au fils de la journee:

		pNouveau_client->date_arrivee = temps;
		temps += (int) (-log(1-aleatoire(0,1))/lambda); //variable aleatoire exponentielle

		insertion(pNouveau_client,&ma_liste);
	};

	calcule(min, max, &ma_liste);
	affichage(&ma_liste);
	enregistreListeJournaliere(&ma_liste);
	printf("done.\n");
	Metriques metriques =  enregilecturestrer();

	return 0;
}


double aleatoire(double a, double b){	
//retourne un nombre aleatoire entre a et b
	//return (rand() /RAND_MAX *(b-a) + a);
	return  (double)(rand()%1000) /1000 *(b-a) +a;
}


void insertion(Client* pNouveau_client, ListeClient* pMa_liste){
//insertion en fin de liste

	Client* ptr_courant = pMa_liste->pTete;
	bool est_insere = false;
	pNouveau_client->suivant = NULL;;

	//parcours de la liste:

	if(ptr_courant == NULL){	//cas d'une liste vide
		pMa_liste->pTete = pNouveau_client;	
	}

	else{
		while(!est_insere){

			//racordage au niveau du dernier element:
			if(ptr_courant->suivant == NULL){
				ptr_courant->suivant = pNouveau_client;
				est_insere = true;
			}

			//sinon on continue de parcourir:
			else ptr_courant = ptr_courant->suivant;
		}
	}
}


void affichage(ListeClient* pMa_liste){
//parcours de la liste pour afficher les temps:

	Client *ptr_courant = pMa_liste->pTete;
	
	while(ptr_courant != NULL){
		//printf("In %d\t: Wait %d\t: End %d\t|\n",ptr_courant->date_arrivee,ptr_courant->duree_attente,ptr_courant->date_fin);
		ptr_courant = ptr_courant->suivant;	
	}
}


void calcule(int min, int max, ListeClient* pMa_liste){
//calcules les caracteistiques des clients de la liste

	Client* ptr_courant = pMa_liste->pTete;
	Client* ptr_precedent;

	//getsion du premier client:
	ptr_courant->duree_attente = 0;
	ptr_courant->date_fin = ptr_courant->date_arrivee + aleatoire(min, max);

	//passage au maillot suivant:
	ptr_precedent = ptr_courant;
	ptr_courant = ptr_courant->suivant;
	
	//parcours de la liste:
	while(ptr_courant->suivant != NULL){ 
	//execute le bloc et le repete si la condition est vrai

		ptr_courant->duree_attente = ptr_precedent->date_fin - ptr_courant->date_arrivee;
		if(ptr_courant->duree_attente<0)
			ptr_courant->duree_attente = 0;
				
		ptr_courant->date_fin = ptr_precedent->date_fin + aleatoire(min, max);

		//passage au maillot suivant:
		ptr_precedent = ptr_courant;
		ptr_courant = ptr_courant->suivant;
	}

	//pour tester le dernier element:
	ptr_courant->duree_attente = ptr_precedent->date_fin - ptr_courant->date_arrivee;
	ptr_courant->date_fin = ptr_precedent->date_fin + aleatoire(min, max);
}


void enregistreListeJournaliere(ListeClient* pMa_liste){
	//Conventions d enregistrement:
	//Les dates sont exprimes en minutes ecoulees depuis 8h30
	//pour chaque client, on enregistre sur une ligne les variables suivantes separes d une virgule:
	// date d arrivee, duree d attente, date de debut de service, date de fin de service
	Client *ptr_courant = pMa_liste->pTete;
	int date_debut_service;

	FILE *fic;
	fic = fopen("liste_journaliere_de_clients.txt", "w");

	while(ptr_courant->suivant != NULL){

		date_debut_service = ptr_courant->date_arrivee + ptr_courant->duree_attente;
		fprintf(fic, "%d,%d,%d,%d\n", 	ptr_courant->date_arrivee,
										ptr_courant->duree_attente, 
										date_debut_service,
										ptr_courant->date_fin);
		

		ptr_courant = ptr_courant->suivant;
	}

	date_debut_service = ptr_courant->date_arrivee+ptr_courant->duree_attente;
	fprintf(fic, "%d,%d,%d,%d\n", 	ptr_courant->date_arrivee,
									ptr_courant->duree_attente, 
									date_debut_service,
									ptr_courant->date_fin);

	fclose(fic);

}