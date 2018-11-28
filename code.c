#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "enregistrement.h"

//biblio mathematique ajouter -lm a la compilation
//intervalle d ouveture en temps: 8h30 a 17h30 -> 540min

typedef struct _Client {int date_arrivee;
						int duree_attente;
						int date_fin;
						struct _Client* suivant;	} Client;


typedef struct {Client* tete;} ListeCient;

/* justifictation: 
On utilise une liste chainee afin de pouvoir ajouter des clients sans limite de taille
*/


void insertion(Client* pNouveau_client, ListeCient* pMa_liste);
double aleatoire(int a, int b);
void calcule(int min, int max, ListeCient* pMa_liste); //calcules les caracteistiques des clients de la liste



//--------------------------------------------------------------------

int main(){
	int temps = 0;
	double lambda = 0.1;
	int min; int max;

	srand(time(NULL)); // initialisation de rand pour avoir des valeur alatoire

	ListeCient ma_liste;
	ma_liste.tete = NULL;


	while(temps < 510){	//540 -30 min -> interdiction d arriver 30min avant la fermeture

		//creation d un client:
		Client* pNouveau_client = malloc(sizeof(Client)); //reserve de la place memoire
		//actualisation du temps au fils de la journee:
		

		temps += (int) - log(1-aleatoire(0,1))/lambda; //variable aleatoire exponentielle
		pNouveau_client->date_arrivee = temps;

		insertion(pNouveau_client,&ma_liste);
	}
	printf('Liste chainée créée!');

	calcule(min, max, &ma_liste);

	return 0;
}


void insertion(Client* pNouveau_client, ListeCient* pMa_liste){
//insertion en fin de liste

	Client* ptr_courant;
	ptr_courant->suivant = pMa_liste->tete;

	//parcours de la liste:
	while(ptr_courant->suivant != NULL){		
		ptr_courant = ptr_courant->suivant;	
	}
	

	//pour tester le deriner element:
	ptr_courant->suivant = pNouveau_client;
	pNouveau_client->suivant = NULL;
}


double aleatoire(int a, int b){	//retourne un nombre aleatoire entre a et b
	return(rand()/RAND_MAX * (b-a) + a);
	//return(1);
}



void calcule(int min, int max, ListeCient* pMa_liste){

	Client* ptr_courant; Client* ptr_precedent;
	ptr_courant->suivant = pMa_liste->tete;

	//getsion du premier client:
	ptr_courant->duree_attente = 0;
	ptr_courant->date_fin = ptr_courant->date_arrivee + aleatoire(min, max);

	//passage au maillot suivant:
	ptr_precedent = ptr_courant;
	ptr_courant = ptr_courant->suivant;

	//parcours de la liste:
	do{ //execute le bloc et le repete si la condition est vrai

		ptr_courant->duree_attente = ptr_precedent->date_fin - ptr_courant->date_arrivee;
		ptr_courant->date_fin = ptr_precedent->date_fin + aleatoire(min, max);

		//passage au maillot suivant:
		ptr_precedent = ptr_courant;
		ptr_courant = ptr_courant->suivant;
	}
	while(ptr_courant->suivant != NULL);

	//pour tester le deriner element:
	ptr_courant->duree_attente = ptr_precedent->date_fin - ptr_courant->date_arrivee;
	ptr_courant->date_fin = ptr_precedent->date_fin + aleatoire(min, max);
	
}