#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void afficher_menu() {
    printf("\n===============================================\n");
    printf("Bonjour ! Bienvenue dans votre shell interactif, je vais vous guider...\n");
    printf("Commencez par indiquer ce que vous souhaitez faire : \n");
    printf("1 : créer votre compte\n");
    printf("2 : vous connecter\n");
    printf("3 : reafficher le menu\n");
    printf("4 : Quitter le shell\n");
    printf("===============================================\n");
}

int create_account(){
	char id[30];
	char password[25];
	FILE * create_fic =  NULL;
	printf("Entrez votre identifiant :\n=> ");
	scanf("%s", id);

	if((create_fic = fopen(id, "r")) != NULL){
		printf("Un compte existe deja sous ce nom, connectez vous\n");
		return 2;
	}

	if((create_fic = fopen(id, "w")) == NULL){
		printf("Erreur lors de la creation de votre compte, verifiez les droits et votre memoire");
		return 3;
	}
	printf("Choisir un mot de passe sécurisé qui respecte les normes de l'ANSSI :\n=> ");
	scanf("%s", &password);

	printf("Votre compte a ete créé avec succès, vous pouvez vous connecter\n");
	return 2;
}

int main(int argc, char **argv) {
    short int choice = 3;

    while (1) {

        switch (choice) {
            case 1:
                choice = create_account();
		break;
            case 2:
                printf("Vous avez choisi de vous connecter.\n");
                break;
            case 3:
                afficher_menu();
		choice = 0;
                break;
            case 4:
                printf("Au revoir !\n");
                exit(EXIT_SUCCESS);
            default:
		printf("=> ");
		scanf("%hd", &choice);
		fflush(stdin);
                printf("\n");
        }
    }

    exit(EXIT_FAILURE);
}

