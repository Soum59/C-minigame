#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int code[4];
int code2[4];
int code3[4];

/* Renvoie le chiffre minimum du code */
int minimum(int code[4])
{
    int min = code[0];

    for (int i = 1; i < 4; i++)
    {
        if (code[i] < min)
            min = code[i];
    }

    return min;
}

/* Crée un code aléatoire */
void password(int code[4])
{
    for (int i = 0; i < 4; i++)
        code[i] = rand() % 10;
}

/* Renvoie l'indice du chiffre minimum */
int indice_minimum(int code[4])
{
    int indice = 0;

    for (int i = 1; i < 4; i++)
    {
        if (code[i] < code[indice])
            indice = i;
    }

    return indice;
}

/* Renvoie l'indice du chiffre maximum */
int indice_maximum(int code[4])
{
    int indice = 0;

    for (int i = 1; i < 4; i++)
    {
        if (code[i] > code[indice])
            indice = i;
    }

    return indice;
}

/* Crée le deuxième code à partir du premier */
/* Chaque chiffre est changé par son complément à 10*/ 
void password2(int code2[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (code[i] != 0)
            code2[i] = 10 - code[i];
        else
            code2[i] = 0;
    }
}

/* Crée le troisième code à partir du deuxième*/
/* Tous les chiffres inferieurs à 5 sont multipliés par 2 et tous les autres sont divisés puis tronqués*/
void password3(int code3[4])
{
	for (int i = 0; i<4; i++)
	{
		if (code2[i] != 0)
		{
			if (code2[i] < 5)
				code3[i] = code2[i] * 2;
			else
				code3[i] = code2[i] / 2;
		}
		else
			code3[i] = 0;
	}
}

/* Affiche les indices correspondant aux chiffres */
void devinette(int code[4])
{
    char indices[4][100];

    for (int i = 0; i < 4; i++)
    {
        if (code[i] == 0)
            strcpy(indices[i], "V I D E");
        else if (code[i] == 1)
            strcpy(indices[i], "C'est vrai.");
        else if (code[i] == 2)
            strcpy(indices[i],
                   "Le dindon fait dodo dans des draps de diamant.");
        else if (code[i] == 3)
            strcpy(indices[i], "Très triangulaire.");
        else if (code[i] == 4)
            strcpy(indices[i], "Carrément.");
        else if (code[i] == 5)
            strcpy(indices[i], "Regarde ta main... ou ton pied.");
        else if (code[i] == 6)
            strcpy(indices[i],
                   "Si tu parles de lui et de son voisin, ça va mal aller.");
        else if (code[i] == 7)
            strcpy(indices[i], "Jackpot.");
        else if (code[i] == 8)
            strcpy(indices[i], "Symétrie.");
        else
            strcpy(indices[i], "Cousin de 6.");
    }

    printf("Indice 1 : %s\n", indices[0]);
    printf("Indice 2 : %s\n", indices[1]);
    printf("Indice 3 : %s\n", indices[2]);
    printf("Indice 4 : %s\n", indices[3]);
}

/* Convertit les quatre chiffres en une chaîne */
void convertir_code(int code[4], char resultat[5])
{
    for (int i = 0; i < 4; i++)
        resultat[i] = '0' + code[i];

    resultat[4] = '\0';
}

/* Demande un code au joueur et vérifie sa réponse */
int verifier_code(int code_secret[4])
{
    char attendu[5];
    char reponse[100];

    convertir_code(code_secret, attendu);

    while (1)
    {
        printf("\n\n ~ ~ ~ ~ ~ Ta réponse ici : ");

        if (scanf("%99s", reponse) != 1)
            return 0;

        if (strcmp(reponse, attendu) == 0)
            return 1;

        printf("Ah. Réessaie, c'est pas ça.\n");
    }
}

int main(void)
{
    srand(time(NULL));

    printf("╔══════════════════════════════════╗\n"
           "║        ~  COFFRE FORT  ~         ║\n"
           "║                                  ║\n"
           "║   Trois codes.                   ║\n"
           "║   Trois énigmes.                 ║\n"
           "║   Un coffre légendaire.          ║\n"
           "║                                  ║\n"
           "║         Bonne chance !           ║\n"
           "╚══════════════════════════════════╝\n");

    printf("Appuie sur ENTRE pour commencer !");
    getchar();

    printf("\n\n          GAME START !          \n");

    /* Génération du premier code */
    password(code);
    while (minimum(code) > 4)
	    password(code);

    /* Génération du deuxième code */
    password2(code2);

    /* Génération du troisième code*/
    password3(code3);

    /* TEST CODE 1*/
    /*printf("%d%d%d%d\n", code[0], code[1], code[2], code[3]);*/

    /* TEST CODE 2 */
    /*printf("%d%d%d%d\n", code2[0], code2[1], code2[2], code2[3]);*/

    /* TEST CODE 3*/
    /*printf("%d%d%d%d\n", code3[0], code3[1], code3[2], code3[3]);*/

    /* Premier défi */
    printf("\nPour ce premier niveau, le code à quatre "
           "chiffres peut être déchiffré à l'aide de ces devinettes.\n"
           "Peux-tu les déchiffrer ?\n\n");

    devinette(code);

    if (!verifier_code(code))
        return 1;

    printf("\nBiennn, t'as réussi !\n\n");

    /* Deuxième défi */
    printf("Le prochain défi ne te donnera pas d'indices "
           "aussi explicites...\n"
           "Essaie de comprendre la transformation du code précédent ! Tu ne dois que donner son 'complement' le premier code.\n\n");

    if (!verifier_code(code2))
        return 1;

    printf("\nBravooo, encore réussi !\n");

    /* Troisième et dernier défi */
	printf("Pour ce dernier défi tu vas calculer de tête"
			"(Attention pas de calculatrice hein)\n les petits chiffres sont doublés et les"
		       	"grands sont divisés par 2\n\n");
	
	if (!verifier_code(code3))
		return 1;
	printf("\nTu as enfin fini tous les défis ! Tu obtiens donc ce coffre légendaire !\n");



	printf("*******************************************************************************\n"
	"          |                   |                  |                     |\n"
	" _________|________________.=\"\"_;=.______________|_____________________|_______\n"
	"|                   |  ,-\"_,=\"\"     `\"=.|                  |\n"
	"|___________________|__\"=._o`\"-._        `\"=.______________|___________________\n"
	"          |                `\"=._o`\"=._      _`\"=._                     |\n"
	" _________|_____________________:=._o \"=._.\"_.-=\"'\"=.__________________|_______\n"
	"|                   |    __.--\" , ; `\"=._o.\" ,-\"\"\"-._ \".   |\n"
	"|___________________|_._\"  ,. .` ` `` ,  `\"-._\"-._   \". '__|___________________\n"
	"          |           |o`\"=._` , \"` `; .\". ,  \"-._\"-._; ;              |\n"
	" _________|___________| ;`-.o`\"=._; .\" ` '`\"\\` . \"-._ /________________|_______\n"
	"|                   | |o;    `\"-.o`\"=._``  '` \" ,__.--o;   |\n"
	"|___________________|_| ;     (#) `-.o `\"=.`_.--\"_o.-; ;___|___________________\n"
	"____/______/______/___|o;._    \"      `\".o|o_.--\"    ;o;____/______/______/____\n"
	"/______/______/______/`\"=._o--._        ; | ;        ; ;/______/______/______/_\n"
	"____/______/______/______/__\"=._o--._   ;o|o;     _._;o;____/______/______/____\n"
	"/______/______/______/______/____\"=._o._; | ;_.--\"o.--\"_/______/______/______/_\n"
	"____/______/______/______/______/_____= .o|o_.--\"\"___/______/______/______/____\n"
	"/______/______/______/______/______/______/______/______/______/______/_______/\n"
	"*******************************************************************************\n");

    return 0;
}
