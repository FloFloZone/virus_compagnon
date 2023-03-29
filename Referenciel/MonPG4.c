#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Définition des constantes
#define NB_COULEUR 6
#define NB_CHOIX 4
#define NB_PROPOSITION 12

// Définition des variables globales
char couleurs[NB_COULEUR][10] = {"rouge", "vert", "bleu", "jaune", "orange", "marron"};
int code[NB_CHOIX];

// Création du code
void creerCode()
{
    srand(time(NULL));
    for (int i = 0; i < NB_CHOIX; i++)
    {
        code[i] = rand() % NB_COULEUR;
    }
}

// Affichage des règles
void regle()
{
    printf("Bienvenue dans le jeu du Mastermind!\n\n");
    printf("Le but du jeu est de deviner la combinaison secrète.\n");
    printf("Le code est composé de %d pions, chacun pouvant être d'une des %d couleurs.\n", NB_CHOIX, NB_COULEUR);
    printf("Après chaque essai, vous saurez combien de pions de votre essai sont de la bonne couleur et à la bonne position (pions noirs) et combien sont de la bonne couleur mais à la mauvaise position (pions blancs).\n");
    printf("Vous avez %d essais pour deviner le code.\n\n", NB_PROPOSITION);
    printf("les couleurs possibles sont: ");
    for (int i = 0; i < NB_COULEUR; i++)
    {
        printf("%s ", couleurs[i]);
    }
    printf("\n\n");
}

// Vérification de la saisie
int compterNbNoir(int essai[])
{
    int nb_noir = 0;
    for (int i = 0; i < NB_CHOIX; i++)
    {
        if (essai[i] == code[i])
        {
            nb_noir++;
        }
    }
    return nb_noir;
}

// Vérification de la saisie
int compterNbBlanc(int essai[])
{
    int nb_blanc = 0;
    int code_count[NB_COULEUR] = {0};
    int compterEssai[NB_COULEUR] = {0};
    for (int i = 0; i < NB_CHOIX; i++)
    {
        code_count[code[i]]++;
        compterEssai[essai[i]]++;
    }
    for (int i = 0; i < NB_COULEUR; i++)
    {
        nb_blanc += (code_count[i] < compterEssai[i]) ? code_count[i] : compterEssai[i];
    }
    nb_blanc -= compterNbNoir(essai);
    return nb_blanc;
}

// Affichage du résultat de l'essai
void print_essai(int essai[])
{
    for (int i = 0; i < NB_CHOIX; i++)
    {
        printf("%s ", couleurs[essai[i]]);
    }
    printf("\n");
}

// Affichage de tous les essais
void print_essaies(int essaies[][NB_CHOIX], int nb_essaies)
{
    for (int i = 0; i < nb_essaies; i++)
    {
        printf("%d: ", i + 1);
        print_essai(essaies[i]);
    }
}

int main()
{
    // Affichage des règles et créations du code à trouver
    creerCode();
    regle();

    // Déclaration des variables
    int essaies[NB_PROPOSITION][NB_CHOIX];
    int nb_essaies = 0;
    int nb_noir = 0;

    // Boucle de jeu
    while (nb_essaies < NB_PROPOSITION && nb_noir < NB_CHOIX)
    {
        int essai[NB_CHOIX];
        printf("Essai #%d: ", nb_essaies + 1);
        // Vérification de la saisie
        for (int i = 0; i < NB_CHOIX; i++)
        {
            char couleur[10];
            scanf("%s", couleur);
            for (int j = 0; j < NB_COULEUR; j++)
            {
                if (strcmp(couleur, couleurs[j]) == 0)
                {
                    essai[i] = j;
                    break;
                }
            }
        }
        // Affichage du résultat de l'essai
        nb_noir = compterNbNoir(essai);
        int nb_blanc = compterNbBlanc(essai);
        printf("%d pions noirs, %d pions blancs\n\n", nb_noir, nb_blanc);
        // Enregistrement de l'essai
        for (int i = 0; i < NB_CHOIX; i++)
        {
            essaies[nb_essaies][i] = essai[i];
        }
        nb_essaies++;
    }
    // Affichage du résultat
    if (nb_noir == NB_CHOIX)
    {
        printf("Bravo! Vous avez gagné!\n");
    }
    else
    {
        printf("Désolé, vous avez perdu. Le code était: ");
        print_essai(code);
    }
    printf("Voici vos essais:\n");
    print_essaies(essaies, nb_essaies);

    return EXIT_SUCCESS;
}