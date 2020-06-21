#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //permet d'afficher des images dans le format voulu (SDL seul ne permet que le format .bmp)
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void InitialisationGrille(SDL_Renderer* renderer, SDL_Window* fenetre);     //Placement des pieces au debut du jeu et lancement de la partie

void affichageGrille(string grille[], string grille_couleur[], SDL_Renderer* renderer, SDL_Window*);        //Affichage de la grille

void TourJ1(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre);       //Tour du joueur 1

void TourJ2(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre);       //Tour du joueur 2

int conversion(string case_jouee);      //Convertit les cases du format "A1" au format "0"

int verification_J1(string grille[], string grille_couleur[], int numero_case, int numero_case_deplacement); //verification d'un deplacement en fonction de la piece

int verification_J2(string grille[], string grille_couleur[], int numero_case, int numero_case_deplacement);

void deplacement(string grille[], string grille_couleur[], int numero_case, int numero_case_deplacement, int type_de_coup); //deplace les pieces dans les tableaux

void VerifVictoire(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre);    //Verification d'une potentielle victoire

void VerifMiseEnEchec(string grille[], string grille_couleur[]);        //Vericfication d'une potentielle mise en echec
    
//fonctions partie IA

void TourJ1_IA(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre);    //Tour du joueur

void Tour_IA(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre);  //Tour de l'IA

int minmax(string grille[], string grille_couleur[], int numero_return);    //Choix des cases que va jouer l'IA

int Valeur_Piece(string grille[], int numero_case); //Donne une valeur à une piece

int VerifVictoire_Simulation(string grille[]);  //Simule une verification de victoire

int VerifMiseEnEchec_Simulation(string grille[], string grille_couleur[]);  //Simule une verification de mise en echec





int main(int argc, char* argv[])    //les arguments sont obligatoires pour faire du SDL
{
    
        SDL_Window* fenetre;    //Declaration de la fenetre 


        SDL_Renderer* renderer; // Déclaration du rendu de la fenetre 

      
        if (SDL_VideoInit(NULL) < 0) // Initialisation de la SDL
        {
            printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
            return EXIT_FAILURE;
        }

        // Création de la fenêtre :
        fenetre = SDL_CreateWindow("Jeu d'Echec", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0); //la fenetre sera centré sur l'écran
        if (fenetre == NULL) // Gestion des erreurs
        {
            printf("Erreur lors de la creation d'une fenetre : %s", SDL_GetError());
            return EXIT_FAILURE;
        }

        // Création du rendu :
        renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer
        if (renderer == NULL) // Gestion des erreurs
        {
            printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
            return EXIT_FAILURE;
        }

        

        
        //On lance le jeu
        InitialisationGrille(renderer, fenetre);
        
        SDL_Delay(10000); //temps d'attente de 10 sec (ne devrait normalement jamais s'activer car on entre dans le jeu avec la fonction precedente)




        
    // Destruction du renderer et de la fenêtre :
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(fenetre);
        SDL_Quit(); // On quitte la SDL
    
}



void InitialisationGrille(SDL_Renderer* renderer, SDL_Window* fenetre)
{



    //On initialise les coordonnées
    //A
    string A1 = "T1B";
    string A1_couleur = "blanc";
    string A2 = "P1B";
    string A2_couleur = "blanc";
    string A3 = "   ";
    string A3_couleur = "aucune";
    string A4 = "   ";
    string A4_couleur = "aucune";
    string A5 = "   ";
    string A5_couleur = "aucune";
    string A6 = "   ";
    string A6_couleur = "aucune";
    string A7 = "P1N";
    string A7_couleur = "noir";
    string A8 = "T1N";
    string A8_couleur = "noir";

    //B
    string B1 = "C1B";
    string B1_couleur = "blanc";
    string B2 = "P2B";
    string B2_couleur = "blanc";
    string B3 = "   ";
    string B3_couleur = "aucune";
    string B4 = "   ";
    string B4_couleur = "aucune";
    string B5 = "   ";
    string B5_couleur = "aucune";
    string B6 = "   ";
    string B6_couleur = "aucune";
    string B7 = "P2N";
    string B7_couleur = "noir";
    string B8 = "C1N";
    string B8_couleur = "noir";

    //C
    string C1 = "F1B";
    string C1_couleur = "blanc";
    string C2 = "P3B";
    string C2_couleur = "blanc";
    string C3 = "   ";
    string C3_couleur = "aucune";
    string C4 = "   ";
    string C4_couleur = "aucune";
    string C5 = "   ";
    string C5_couleur = "aucune";
    string C6 = "   ";
    string C6_couleur = "aucune";
    string C7 = "P3N";
    string C7_couleur = "noir";
    string C8 = "F1N";
    string C8_couleur = "noir";

    //D
    string D1 = "ReB";
    string D1_couleur = "blanc";
    string D2 = "P4B";
    string D2_couleur = "blanc";
    string D3 = "   ";
    string D3_couleur = "aucune";
    string D4 = "   ";
    string D4_couleur = "aucune";
    string D5 = "   ";
    string D5_couleur = "aucune";
    string D6 = "   ";
    string D6_couleur = "aucune";
    string D7 = "P4N";
    string D7_couleur = "noir";
    string D8 = "ReN";
    string D8_couleur = "noir";

    //E
    string E1 = "RoB";
    string E1_couleur = "blanc";
    string E2 = "P5B";
    string E2_couleur = "blanc";
    string E3 = "   ";
    string E3_couleur = "aucune";
    string E4 = "   ";
    string E4_couleur = "aucune";
    string E5 = "   ";
    string E5_couleur = "aucune";
    string E6 = "   ";
    string E6_couleur = "aucune";
    string E7 = "P5N";
    string E7_couleur = "noir";
    string E8 = "RoN";
    string E8_couleur = "noir";

    //F
    string F1 = "F2B";
    string F1_couleur = "blanc";
    string F2 = "P6B";
    string F2_couleur = "blanc";
    string F3 = "   ";
    string F3_couleur = "aucune";
    string F4 = "   ";
    string F4_couleur = "aucune";
    string F5 = "   ";
    string F5_couleur = "aucune";
    string F6 = "   ";
    string F6_couleur = "aucune";
    string F7 = "P6N";
    string F7_couleur = "noir";
    string F8 = "F2N";
    string F8_couleur = "noir";

    //G
    string G1 = "C2B";
    string G1_couleur = "blanc";
    string G2 = "P7B";
    string G2_couleur = "blanc";
    string G3 = "   ";
    string G3_couleur = "aucune";
    string G4 = "   ";
    string G4_couleur = "aucune";
    string G5 = "   ";
    string G5_couleur = "aucune";
    string G6 = "   ";
    string G6_couleur = "aucune";
    string G7 = "P7N";
    string G7_couleur = "noir";
    string G8 = "C2N";
    string G8_couleur = "noir";

    //H
    string H1 = "T2B";
    string H1_couleur = "blanc";
    string H2 = "P8B";
    string H2_couleur = "blanc";
    string H3 = "   ";
    string H3_couleur = "aucune";
    string H4 = "   ";
    string H4_couleur = "aucune";
    string H5 = "   ";
    string H5_couleur = "aucune";
    string H6 = "   ";
    string H6_couleur = "aucune";
    string H7 = "P8N";
    string H7_couleur = "noir";
    string H8 = "T2N";
    string H8_couleur = "noir";

    //échequier
    string grille[64];

    //on relier les coordonnées avec les numeros de cases
    grille[0] = A1;
    grille[1] = A2;
    grille[2] = A3;
    grille[3] = A4;
    grille[4] = A5;
    grille[5] = A6;
    grille[6] = A7;
    grille[7] = A8;

    grille[8] = B1;
    grille[9] = B2;
    grille[10] = B3;
    grille[11] = B4;
    grille[12] = B5;
    grille[13] = B6;
    grille[14] = B7;
    grille[15] = B8;

    grille[16] = C1;
    grille[17] = C2;
    grille[18] = C3;
    grille[19] = C4;
    grille[20] = C5;
    grille[21] = C6;
    grille[22] = C7;
    grille[23] = C8;

    grille[24] = D1;
    grille[25] = D2;
    grille[26] = D3;
    grille[27] = D4;
    grille[28] = D5;
    grille[29] = D6;
    grille[30] = D7;
    grille[31] = D8;

    grille[32] = E1;
    grille[33] = E2;
    grille[34] = E3;
    grille[35] = E4;
    grille[36] = E5;
    grille[37] = E6;
    grille[38] = E7;
    grille[39] = E8;

    grille[40] = F1;
    grille[41] = F2;
    grille[42] = F3;
    grille[43] = F4;
    grille[44] = F5;
    grille[45] = F6;
    grille[46] = F7;
    grille[47] = F8;

    grille[48] = G1;
    grille[49] = G2;
    grille[50] = G3;
    grille[51] = G4;
    grille[52] = G5;
    grille[53] = G6;
    grille[54] = G7;
    grille[55] = G8;

    grille[56] = H1;
    grille[57] = H2;
    grille[58] = H3;
    grille[59] = H4;
    grille[60] = H5;
    grille[61] = H6;
    grille[62] = H7;
    grille[63] = H8;

    //grille couleur (couleur de la piece presente sur chaque case)

    string grille_couleur[64];

    grille_couleur[0] = A1_couleur;
    grille_couleur[1] = A2_couleur;
    grille_couleur[2] = A3_couleur;
    grille_couleur[3] = A4_couleur;
    grille_couleur[4] = A5_couleur;
    grille_couleur[5] = A6_couleur;
    grille_couleur[6] = A7_couleur;
    grille_couleur[7] = A8_couleur;

    grille_couleur[8] = B1_couleur;
    grille_couleur[9] = B2_couleur;
    grille_couleur[10] = B3_couleur;
    grille_couleur[11] = B4_couleur;
    grille_couleur[12] = B5_couleur;
    grille_couleur[13] = B6_couleur;
    grille_couleur[14] = B7_couleur;
    grille_couleur[15] = B8_couleur;

    grille_couleur[16] = C1_couleur;
    grille_couleur[17] = C2_couleur;
    grille_couleur[18] = C3_couleur;
    grille_couleur[19] = C4_couleur;
    grille_couleur[20] = C5_couleur;
    grille_couleur[21] = C6_couleur;
    grille_couleur[22] = C7_couleur;
    grille_couleur[23] = C8_couleur;

    grille_couleur[24] = D1_couleur;
    grille_couleur[25] = D2_couleur;
    grille_couleur[26] = D3_couleur;
    grille_couleur[27] = D4_couleur;
    grille_couleur[28] = D5_couleur;
    grille_couleur[29] = D6_couleur;
    grille_couleur[30] = D7_couleur;
    grille_couleur[31] = D8_couleur;

    grille_couleur[32] = E1_couleur;
    grille_couleur[33] = E2_couleur;
    grille_couleur[34] = E3_couleur;
    grille_couleur[35] = E4_couleur;
    grille_couleur[36] = E5_couleur;
    grille_couleur[37] = E6_couleur;
    grille_couleur[38] = E7_couleur;
    grille_couleur[39] = E8_couleur;

    grille_couleur[40] = F1_couleur;
    grille_couleur[41] = F2_couleur;
    grille_couleur[42] = F3_couleur;
    grille_couleur[43] = F4_couleur;
    grille_couleur[44] = F5_couleur;
    grille_couleur[45] = F6_couleur;
    grille_couleur[46] = F7_couleur;
    grille_couleur[47] = F8_couleur;

    grille_couleur[48] = G1_couleur;
    grille_couleur[49] = G2_couleur;
    grille_couleur[50] = G3_couleur;
    grille_couleur[51] = G4_couleur;
    grille_couleur[52] = G5_couleur;
    grille_couleur[53] = G6_couleur;
    grille_couleur[54] = G7_couleur;
    grille_couleur[55] = G8_couleur;

    grille_couleur[56] = H1_couleur;
    grille_couleur[57] = H2_couleur;
    grille_couleur[58] = H3_couleur;
    grille_couleur[59] = H4_couleur;
    grille_couleur[60] = H5_couleur;
    grille_couleur[61] = H6_couleur;
    grille_couleur[62] = H7_couleur;
    grille_couleur[63] = H8_couleur;




    affichageGrille(grille, grille_couleur, renderer, fenetre);

    cout << "Jeu a 2 joueurs : Taper 1" << endl;
    cout << "Jeu a 1 joueur contre IA : Taper 2" << endl;
    int choix_joueur;
    cin >> choix_joueur;
    cout << endl;
    if (choix_joueur != 1 && choix_joueur != 2) { //On verifie que le joueur a bien rentré 1 ou 2
        //probleme dans l'entrée : on relance
        InitialisationGrille(renderer, fenetre);
    }
    else if (choix_joueur == 1) {
        cout << "Quel est le nom du joueur 1" << endl;  //on demande le nom des joueurs
        string NomJoueur1;
        cin >> NomJoueur1;
        cout << endl;

        cout << "Quel est le nom du joueur 2" << endl;
        string NomJoueur2;
        cin >> NomJoueur2;
        cout << endl;

        cout << "Bienvenue a vous : Joueur1 = " << NomJoueur1 << " et Joueur2 = " << NomJoueur2 << endl;
        cout << "qui souhaite commencer ? Taper 1 ou 2" << endl;
        int Qui_joue;
        cin >> Qui_joue;
        cout << endl;

        //pour lancer le tour de celui qui commence
        if ((Qui_joue != 1) && Qui_joue != 2) {  //verif

        }
        else {
            if (Qui_joue == 1) {
                TourJ1(grille, grille_couleur, NomJoueur1, NomJoueur2, renderer, fenetre);
            }
            else {
                TourJ2(grille, grille_couleur, NomJoueur1, NomJoueur2, renderer, fenetre);
            }
        }
    }
    else if (choix_joueur == 2) {
        cout << "Quel est votre nom ?" << endl;
        string NomJoueur1;
        cin >> NomJoueur1;
        cout << endl;
        string NomJoueur2 = "L'IA";

        TourJ1_IA(grille, grille_couleur, NomJoueur1, NomJoueur2, renderer, fenetre);
    }

}

void affichageGrille(string grille[], string grille_couleur[], SDL_Renderer* renderer, SDL_Window* fenetre)
{
    system("cls");    //Pour nettoyer l'ecran
    /*



    PREMIER GRILLE

    cout << endl << endl;
    cout << "                       A         B         C         D         E         F         G         H     " << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "               8  |   " << grille[7] << "   |   " << grille[15] << "   |   " << grille[23] << "   |   " << grille[31] << "   |   " << grille[39] << "   |   " << grille[47] << "   |   " << grille[55] << "   |   " << grille[63] << "   |" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "               7  |   " << grille[6] << "   |   " << grille[14] << "   |   " << grille[22] << "   |   " << grille[30] << "   |   " << grille[38] << "   |   " << grille[46] << "   |   " << grille[54] << "   |   " << grille[62] << "   |" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "               6  |   " << grille[5] << "   |   " << grille[13] << "   |   " << grille[21] << "   |   " << grille[29] << "   |   " << grille[37] << "   |   " << grille[45] << "   |   " << grille[53] << "   |   " << grille[61] << "   |" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "               5  |   " << grille[4] << "   |   " << grille[12] << "   |   " << grille[20] << "   |   " << grille[28] << "   |   " << grille[36] << "   |   " << grille[44] << "   |   " << grille[52] << "   |   " << grille[60] << "   |" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "               4  |   " << grille[3] << "   |   " << grille[11] << "   |   " << grille[19] << "   |   " << grille[27] << "   |   " << grille[35] << "   |   " << grille[43] << "   |   " << grille[51] << "   |   " << grille[59] << "   |" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "               3  |   " << grille[2] << "   |   " << grille[10] << "   |   " << grille[18] << "   |   " << grille[26] << "   |   " << grille[34] << "   |   " << grille[42] << "   |   " << grille[50] << "   |   " << grille[58] << "   |" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "               2  |   " << grille[1] << "   |   " <<  grille[9] << "   |   " << grille[17] << "   |   " << grille[25] << "   |   " << grille[33] << "   |   " << grille[41] << "   |   " << grille[49] << "   |   " << grille[57] << "   |" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "               1  |   " << grille[0] << "   |   " <<  grille[8] << "   |   " << grille[16] << "   |   " << grille[24] << "   |   " << grille[32] << "   |   " << grille[40] << "   |   " << grille[48] << "   |   " << grille[56] << "   |" << endl;
    cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << endl;

    */

    // NOUVELLE GRILLE
    /*
    cout << endl << endl;
    cout << "                       A         B         C         D         E         F         G         H     " << endl;
    for (int i = 7; i > -1; i--) {

        cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
        cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;
        cout << "               " << i + 1 << "  |   " << grille[i] << "   |   " << grille[i + 8] << "   |   " << grille[i + 8 * 2] << "   |   " << grille[i + 8 * 3] << "   |   " << grille[i + 8 * 4] << "   |   " << grille[i + 8 * 5] << "   |   " << grille[i + 8 * 6] << "   |   " << grille[i + 8 * 7] << "   |" << endl;
        cout << "                  |" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << "   " << "   " << "   " << "|" << endl;


    }

    cout << "                  |---------|---------|---------|---------|---------|---------|---------|---------|" << endl;
    cout << endl;
    */

    

      //PREMIERE GRILLE AVEC SDL
    /*
    SDL_Rect cases[32]; // Déclaration du tableau contenant les cases blanches 
    SDL_Point ligne_depart, ligne_arrivee; // Déclaration du point de départ et du point d'arrivée d'une ligne


    

    // On s'occupe tout d'abord des cases de l'échiquier
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 100); //Pour avoir un fond gris sur lequel on pourra afficher des cases blanches
    SDL_RenderClear(renderer);  //pour afficher le fond noir


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Couleur blanche

    // Nous allons maintenant remplir les cases blanches par dessus le fond noir
    // Remplissage du tableau de SDL_Rect que l'on remplira ensuite avec du blanc :

    cases[0].x = cases[0].y = 0;
    cases[0].w = cases[0].h = 100;


    for (int i = 1; i != 32; i++)
    {
        cases[i].x = cases[i - 1].x + 200;
        cases[i].y = cases[i - 1].y;

        if (i % 4 == 0) //retour à la ligne
        {
            cases[i].x = (i % 8 == 0) ? 0 : 100;
            cases[i].y = cases[i - 1].y + 100;
        }
        cases[i].w = cases[i].h = 100; //taille d'une case : 100 x 100
    }

    SDL_RenderFillRects(renderer, cases, 32);
    

    // À présent, occupons nous des lignes
    // On ne peut pas utiliser la fonction SDL_RenderDrawLines
    // car celle-ci ne permet pas de créer des lignes indépendantes comme nous voulons le faire mais des chemins

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 100);//Couleur grise (pour les lignes entre les cases)

    // Lignes horizontales
    ligne_depart.x = 0;
    ligne_arrivee.x = 800;
    ligne_depart.y = 0;
    for (int i = 0; i != 7; i++)
    {
        ligne_depart.y += 100;
        ligne_arrivee.y = ligne_depart.y;
        SDL_RenderDrawLine(renderer, ligne_depart.x, ligne_depart.y, ligne_arrivee.x, ligne_arrivee.y);
    }

    // Lignes verticales
    ligne_depart.x = 0;
    ligne_depart.y = 0;
    ligne_arrivee.y = 800;
    for (int i = 0; i != 7; i++)
    {
        ligne_depart.x += 100;
        ligne_arrivee.x = ligne_depart.x;
        SDL_RenderDrawLine(renderer, ligne_depart.x, ligne_depart.y, ligne_arrivee.x, ligne_arrivee.y);
    }


    SDL_RenderPresent(renderer);    //on affiche le tout
    
    */

    // DEUXIEME GRILLE SDL (affichage du screen de la grille precedente)

    //affichage de la grille
    SDL_Surface* image = IMG_Load("png/grille.png");    //chargement de l'image grille.png
    SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //création de la texture constitué de la grille qui servira de fond 
    SDL_FreeSurface(image); //on libere la mémoire contenu dans la variable image
    SDL_Rect src_grille{ 0, 0, 0, 0 };
    SDL_Rect dst_grille{ 0, 0, 800, 800 };    //0 0 : point d'origine (en haut a gauche de la fenetre) 800, 800 taille de l'image (toute la fenetre)
    SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src_grille.w, &src_grille.h);    //on regroupe les valeurs

   

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   //On reinitialise la grille (pour enlever les pieces du tour precedant)
    SDL_RenderClear(renderer);


    SDL_RenderCopy(renderer, pTextureImage, &src_grille, &dst_grille); //On place la grille sur le rendu
    SDL_DestroyTexture(pTextureImage);
    SDL_RenderPresent(renderer);    //On affiche le rendu



    for (int i = 64; i--; i > 0) {  //affichage des pieces sur la fenetre SDL



        SDL_Rect src{ 0, 0, 0, 0 };
        SDL_Rect dst{ 10, 15, 80, 60 };

        switch (i)  //on doit attribuer les coordonnées dst.x et dst.y à chaque case de l'échiquier
        {
        case 0 :
            dst.x = 10;
            dst.y = 715;
            break;
        case 1:
            dst.x = 10;
            dst.y = 615;
            break;
        case 2:
            dst.x = 10;
            dst.y = 515;
            break;
        case 3:
            dst.x = 10;
            dst.y = 415;
            break;
        case 4:
            dst.x = 10;
            dst.y = 315;
            break;
        case 5:
            dst.x = 10;
            dst.y = 215;
            break;
        case 6:
            dst.x = 10;
            dst.y = 115;
            break;
        case 7:
            dst.x = 10;
            dst.y = 15;
            break;
        case 8:
            dst.x = 110;
            dst.y = 715;
            break;
        case 9:
            dst.x = 110;
            dst.y = 615;
            break;
        case 10:
            dst.x = 110;
            dst.y = 515;
            break;
        case 11:
            dst.x = 110;
            dst.y = 415;
            break;
        case 12:
            dst.x = 110;
            dst.y = 315;
            break;
        case 13:
            dst.x = 110;
            dst.y = 215;
            break;
        case 14:
            dst.x = 110;
            dst.y = 115;
            break;
        case 15:
            dst.x = 110;
            dst.y = 15;
            break;
        case 16:
            dst.x = 210;
            dst.y = 715;
            break;
        case 17:
            dst.x = 210;
            dst.y = 615;
            break;
        case 18:
            dst.x = 210;
            dst.y = 515;
            break;
        case 19:
            dst.x = 210;
            dst.y = 415;
            break;
        case 20:
            dst.x = 210;
            dst.y = 315;
            break;
        case 21:
            dst.x = 210;
            dst.y = 215;
            break;
        case 22:
            dst.x = 210;
            dst.y = 115;
            break;
        case 23:
            dst.x = 210;
            dst.y = 15;
            break;
        case 24:
            dst.x = 310;
            dst.y = 715;
            break;
        case 25:
            dst.x = 310;
            dst.y = 615;
            break;
        case 26:
            dst.x = 310;
            dst.y = 515;
            break;
        case 27:
            dst.x = 310;
            dst.y = 415;
            break;
        case 28:
            dst.x = 310;
            dst.y = 315;
            break;
        case 29:
            dst.x = 310;
            dst.y = 215;
            break;
        case 30:
            dst.x = 310;
            dst.y = 115;
            break;
        case 31:
            dst.x = 310;
            dst.y = 15;
            break;
        case 32:
            dst.x = 410;
            dst.y = 715;
            break;
        case 33:
            dst.x = 410;
            dst.y = 615;
            break;
        case 34:
            dst.x = 410;
            dst.y = 515;
            break;
        case 35:
            dst.x = 410;
            dst.y = 415;
            break;
        case 36:
            dst.x = 410;
            dst.y = 315;
            break;
        case 37:
            dst.x = 410;
            dst.y = 215;
            break;
        case 38:
            dst.x = 410;
            dst.y = 115;
            break;
        case 39:
            dst.x = 410;
            dst.y = 15;
            break;
        case 40:
            dst.x = 510;
            dst.y = 715;
            break;
        case 41:
            dst.x = 510;
            dst.y = 615;
            break;
        case 42:
            dst.x = 510;
            dst.y = 515;
            break;
        case 43:
            dst.x = 510;
            dst.y = 415;
            break;
        case 44:
            dst.x = 510;
            dst.y = 315;
            break;
        case 45:
            dst.x = 510;
            dst.y = 215;
            break;
        case 46:
            dst.x = 510;
            dst.y = 115;
            break;
        case 47:
            dst.x = 510;
            dst.y = 15;
            break;
        case 48:
            dst.x = 610;
            dst.y = 715;
            break;
        case 49:
            dst.x = 610;
            dst.y = 615;
            break;
        case 50:
            dst.x = 610;
            dst.y = 515;
            break;
        case 51:
            dst.x = 610;
            dst.y = 415;
            break;
        case 52:
            dst.x = 610;
            dst.y = 315;
            break;
        case 53:
            dst.x = 610;
            dst.y = 215;
            break;
        case 54:
            dst.x = 610;
            dst.y = 115;
            break;
        case 55:
            dst.x = 610;
            dst.y = 15;
            break;
        case 56:
            dst.x = 710;
            dst.y = 715;
            break;
        case 57:
            dst.x = 710;
            dst.y = 615;
            break;
        case 58:
            dst.x = 710;
            dst.y = 515;
            break;
        case 59:
            dst.x = 710;
            dst.y = 415;
            break;
        case 60:
            dst.x = 710;
            dst.y = 315;
            break;
        case 61:
            dst.x = 710;
            dst.y = 215;
            break;
        case 62:
            dst.x = 710;
            dst.y = 115;
            break;
        case 63:
            dst.x = 710;
            dst.y = 15;
            break;
        default :
            dst.x = 0;
            dst.y = 0;
            break;
        }

        //on va regarder pour chaque case, quelle piece afficher

        if (grille[i] == "P1N" || grille[i] == "P2N" || grille[i] == "P3N" || grille[i] == "P4N" || grille[i] == "P5N" || grille[i] == "P6N" || grille[i] == "P7N" || grille[i] == "P8N") {
            image = IMG_Load("png/pion_noir.png");  //on charge l'image du pion
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "P1B" || grille[i] == "P2B" || grille[i] == "P3B" || grille[i] == "P4B" || grille[i] == "P5B" || grille[i] == "P6B" || grille[i] == "P7B" || grille[i] == "P8B") {
            image = IMG_Load("png/pion_blanc.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "T1B" || grille[i] == "T2B") {
            image = IMG_Load("png/tour_blanc.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "T1N" || grille[i] == "T2N") {
            image = IMG_Load("png/tour_noir.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "C1B" || grille[i] == "C2B") {
            image = IMG_Load("png/cavalier_blanc.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "C1N" || grille[i] == "C2N") {
            image = IMG_Load("png/cavalier_noir.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "F1B" || grille[i] == "F2B") {
            image = IMG_Load("png/fou_blanc.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "F1N" || grille[i] == "F2N") {
            image = IMG_Load("png/fou_noir.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "ReB") {
            image = IMG_Load("png/reine_blanc.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "ReN") {
            image = IMG_Load("png/reine_noir.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "RoB") {
            image = IMG_Load("png/roi_blanc.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }
        else if (grille[i] == "RoN") {
            image = IMG_Load("png/roi_noir.png"); //on charge l'image
            SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(renderer, image); //on remplit la texture avec l'image
            SDL_FreeSurface(image); //on libere la variable image
            SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src.w, &src.h);

            SDL_RenderCopy(renderer, pTextureImage, &src, &dst);   //on place la texture dans le rendu
            SDL_DestroyTexture(pTextureImage);  //on libére la mémoire en détruisant la texture
            SDL_RenderPresent(renderer);    //on affiche le rendu actualisé
        }

        
    }

    cout << endl;   //les coordonnées n'étant pas annotés sur la fenetre SDL, on affiche les coordonnées sur la console
    cout << "8" << endl;
    cout << "7" << endl;
    cout << "6" << endl;
    cout << "5" << endl;
    cout << "4" << endl;
    cout << "3" << endl;
    cout << "2" << endl;
    cout << "1" << endl;
    cout << "   A   B   C   D   E   F   G   H" << endl;
    cout << endl;
    cout << "Pour selectionner les coordonnées de vos cases : " << endl;
    cout << endl;



}

void TourJ1(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre)   //J1 = blanc
{

    cout << "Tour de " << J1 << endl;
    cout << "Choisir la case contenant le pion a bouger" << endl;
    string case_jouee;
    cin >> case_jouee;
    int numero_case = conversion(case_jouee);   //on retrouve le numero dans le tableau
    if (grille_couleur[numero_case] == "blanc") {    //verif couleur de la piece

        cout << "Choisir la case ou se deplacer" << endl;
        string case_deplacement;
        cin >> case_deplacement;
        int numero_case_deplacement = conversion(case_deplacement);
        int coup = verification_J1(grille, grille_couleur, numero_case, numero_case_deplacement);//verif en fonction de la piece (on veut savoir si la case voulu est bien une case possible pour un déplacement avec cette piece), c'est égal à 0 si c'est pas bon
        if (coup != 0)
        {

            deplacement(grille, grille_couleur, numero_case, numero_case_deplacement, coup);  //si le deplacement est correct, on deplace la piece

            affichageGrille(grille, grille_couleur, renderer, fenetre);

            VerifVictoire(grille, grille_couleur, J1, J2, renderer, fenetre);  //on verifie si le joueur a gagné (on doit le mettre avant la mise en echec car sans roi, la mise en echec ne peut se faire correctement

            VerifMiseEnEchec(grille, grille_couleur);

            TourJ2(grille, grille_couleur, J1, J2, renderer, fenetre); //si il n a pas gagné, c'est le tour du joueur 2

        }
        else {
            cout << "probleme dans le deplacement : veuillez reeesayer :" << endl;
            TourJ1(grille, grille_couleur, J1, J2, renderer, fenetre); //on relance le tour de Joueur 1
        }


    }
    else {

        //erreur
        cout << "probleme dans le choix du pion : veuillez reeesayer :" << endl;
        TourJ1(grille, grille_couleur, J1, J2, renderer, fenetre);     //on relance le tour de Joueur 1
    }




}

void TourJ2(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre)   //J2 = noir
{
    cout << "Tour de " << J2 << endl;
    cout << "Choisir la case contenant le pion a bouger" << endl;
    string case_jouee;
    cin >> case_jouee;
    int numero_case = conversion(case_jouee);   //on retrouve le numero dans le tableau
    if (grille_couleur[numero_case] == "noir") {    //verif couleur de la piece

        cout << "Choisir la case ou se deplacer" << endl;
        string case_deplacement;
        cin >> case_deplacement;
        int numero_case_deplacement = conversion(case_deplacement);
        int coup = verification_J2(grille, grille_couleur, numero_case, numero_case_deplacement);
        if (coup != 0)  //verif en fonction de la piece (on veut savoir si la case voulu est bien une case possible pour un déplacement avec cette piece), c'est égal à 1 si c'est bon
        {

            deplacement(grille, grille_couleur, numero_case, numero_case_deplacement, coup);

            affichageGrille(grille, grille_couleur, renderer, fenetre);

            VerifVictoire(grille, grille_couleur, J1, J2, renderer, fenetre);

            VerifMiseEnEchec(grille, grille_couleur);

            TourJ1(grille, grille_couleur, J1, J2, renderer, fenetre);

        }
        else {
            cout << "probleme dans le deplacement : veuillez reeesayer :" << endl;
            TourJ2(grille, grille_couleur, J1, J2, renderer, fenetre);
        }

    }
    else {

        cout << "probleme dans le choix du pion : veuillez reeesayer :" << endl;
        TourJ2(grille, grille_couleur, J1, J2, renderer, fenetre);

    }
}

int conversion(string case_jouee)   //va permettre de passer du format lettre chiffre (A2, B5...) au format chiffres du tableau grille(0, 1, 2... 63)
{
    if (case_jouee == "A1") {
        return 0;
    }
    else if (case_jouee == "A2") {
        return 1;
    }
    else if (case_jouee == "A3") {
        return 2;
    }
    else if (case_jouee == "A4") {
        return 3;
    }
    else if (case_jouee == "A5") {
        return 4;
    }
    else if (case_jouee == "A6") {
        return 5;
    }
    else if (case_jouee == "A7") {
        return 6;
    }
    else if (case_jouee == "A8") {
        return 7;
    }
    else if (case_jouee == "B1") {
        return 8;
    }
    else if (case_jouee == "B2") {
        return 9;
    }
    else if (case_jouee == "B3") {
        return 10;
    }
    else if (case_jouee == "B4") {
        return 11;
    }
    else if (case_jouee == "B5") {
        return 12;
    }
    else if (case_jouee == "B6") {
        return 13;
    }
    else if (case_jouee == "B7") {
        return 14;
    }
    else if (case_jouee == "B8") {
        return 15;
    }
    else if (case_jouee == "C1") {
        return 16;
    }
    else if (case_jouee == "C2") {
        return 17;
    }
    else if (case_jouee == "C3") {
        return 18;
    }
    else if (case_jouee == "C4") {
        return 19;
    }
    else if (case_jouee == "C5") {
        return 20;
    }
    else if (case_jouee == "C6") {
        return 21;
    }
    else if (case_jouee == "C7") {
        return 22;
    }
    else if (case_jouee == "C8") {
        return 23;
    }
    else if (case_jouee == "D1") {
        return 24;
    }
    else if (case_jouee == "D2") {
        return 25;
    }
    else if (case_jouee == "D3") {
        return 26;
    }
    else if (case_jouee == "D4") {
        return 27;
    }
    else if (case_jouee == "D5") {
        return 28;
    }
    else if (case_jouee == "D6") {
        return 29;
    }
    else if (case_jouee == "D7") {
        return 30;
    }
    else if (case_jouee == "D8") {
        return 31;
    }
    else if (case_jouee == "E1") {
        return 32;
    }
    else if (case_jouee == "E2") {
        return 33;
    }
    else if (case_jouee == "E3") {
        return 34;
    }
    else if (case_jouee == "E4") {
        return 35;
    }
    else if (case_jouee == "E5") {
        return 36;
    }
    else if (case_jouee == "E6") {
        return 37;
    }
    else if (case_jouee == "E7") {
        return 38;
    }
    else if (case_jouee == "E8") {
        return 39;
    }
    else if (case_jouee == "F1") {
        return 40;
    }
    else if (case_jouee == "F2") {
        return 41;
    }
    else if (case_jouee == "F3") {
        return 42;
    }
    else if (case_jouee == "F4") {
        return 43;
    }
    else if (case_jouee == "F5") {
        return 44;
    }
    else if (case_jouee == "F6") {
        return 45;
    }
    else if (case_jouee == "F7") {
        return 46;
    }
    else if (case_jouee == "F8") {
        return 47;
    }
    else if (case_jouee == "G1") {
        return 48;
    }
    else if (case_jouee == "G2") {
        return 49;
    }
    else if (case_jouee == "G3") {
        return 50;
    }
    else if (case_jouee == "G4") {
        return 51;
    }
    else if (case_jouee == "G5") {
        return 52;
    }
    else if (case_jouee == "G6") {
        return 53;
    }
    else if (case_jouee == "G7") {
        return 54;
    }
    else if (case_jouee == "G8") {
        return 55;
    }
    else if (case_jouee == "H1") {
        return 56;
    }
    else if (case_jouee == "H2") {
        return 57;
    }
    else if (case_jouee == "H3") {
        return 58;
    }
    else if (case_jouee == "H4") {
        return 59;
    }
    else if (case_jouee == "H5") {
        return 60;
    }
    else if (case_jouee == "H6") {
        return 61;
    }
    else if (case_jouee == "H7") {
        return 62;
    }
    else if (case_jouee == "H8") {
        return 63;
    }
    else {
        //probleme
    }


}

int verification_J1(string grille[], string grille_couleur[], int numero_case, int numero_case_deplacement)
{

    //afin de vérifier les déplacements, on a besoin de connaitre les numéros de ligne horizontale et verticale

    int ligne_horizontale_initiale = numero_case % 8;       //pour avoir le numero de ligne horizontal, il suffit de faire le numero de case modulo 8 et de regarder le numero de ligne entre 0 et 7
    int ligne_horizontale_deplacement = numero_case_deplacement % 8;

    int ligne_verticale_initiale = 0;
    int ligne_verticale_deplacement = 0;

    if (0 <= numero_case && numero_case < 8) {                             //pour avoir le numero de ligne vertical il faut verifier pour chaque colonne si la case y est (entre 1 et 8)
        ligne_verticale_initiale = 1;
    }
    else if (8 <= numero_case && numero_case < 16) {
        ligne_verticale_initiale = 2;
    }
    else if (16 <= numero_case && numero_case < 24) {
        ligne_verticale_initiale = 3;
    }
    else if (24 <= numero_case && numero_case < 32) {
        ligne_verticale_initiale = 4;
    }
    else if (32 <= numero_case && numero_case < 40) {
        ligne_verticale_initiale = 5;
    }
    else if (40 <= numero_case && numero_case < 48) {
        ligne_verticale_initiale = 6;
    }
    else if (48 <= numero_case && numero_case < 56) {
        ligne_verticale_initiale = 7;
    }
    else if (56 <= numero_case && numero_case < 64) {
        ligne_verticale_initiale = 8;
    }



    if (0 <= numero_case_deplacement && numero_case_deplacement < 8) {
        ligne_verticale_deplacement = 1;
    }
    else if (8 <= numero_case_deplacement && numero_case_deplacement < 16) {
        ligne_verticale_deplacement = 2;
    }
    else if (16 <= numero_case_deplacement && numero_case_deplacement < 24) {
        ligne_verticale_deplacement = 3;
    }
    else if (24 <= numero_case_deplacement && numero_case_deplacement < 32) {
        ligne_verticale_deplacement = 4;
    }
    else if (32 <= numero_case_deplacement && numero_case_deplacement < 40) {
        ligne_verticale_deplacement = 5;
    }
    else if (40 <= numero_case_deplacement && numero_case_deplacement < 48) {
        ligne_verticale_deplacement = 6;
    }
    else if (48 <= numero_case_deplacement && numero_case_deplacement < 56) {
        ligne_verticale_deplacement = 7;
    }
    else if (56 <= numero_case_deplacement && numero_case_deplacement < 64) {
        ligne_verticale_deplacement = 8;
    }








    if (grille[numero_case] == "P1B" || grille[numero_case] == "P2B" || grille[numero_case] == "P3B" || grille[numero_case] == "P4B" || grille[numero_case] == "P5B" || grille[numero_case] == "P6B" || grille[numero_case] == "P7B" || grille[numero_case] == "P8B") {
        //cas où la piece choisi est un pion
        //pour pouvoir bouger un pion (tout le long de la partie), il faut soit avancer de une case sur une case vide, soit avancer d'une case en diagonale pour éliminer un pion ennemi

        if (grille_couleur[numero_case_deplacement] == "aucune" && numero_case_deplacement - numero_case == 1 && ligne_horizontale_initiale < ligne_horizontale_deplacement) {    //2 conditions : la case doit etre vide et doit etre la case au dessus de la case precedente

            if (ligne_horizontale_deplacement == 7) {   //lorsqu'un pion arrive en haut de l'echequier, le pion devient une reine
                grille[numero_case] = "ReB";
                return 1;
            }
            else {
                return 1;
            }

        }
        else if (grille_couleur[numero_case_deplacement] == "noir" && numero_case_deplacement - numero_case == 9 && ligne_horizontale_initiale < ligne_horizontale_deplacement) {  //2 conditions : la case est une piece noire et se trouve à une case en diagonale de la precedente

            if (ligne_horizontale_deplacement == 7) {   //lorsqu'un pion arrive en haut de l'echequier, le pion devient une reine
                grille[numero_case] = "ReB";
                return 1;
            }
            else {
                return 1;
            }
        }
        else if (grille_couleur[numero_case_deplacement] == "noir" && numero_case_deplacement - numero_case == -7 && ligne_horizontale_initiale < ligne_horizontale_deplacement) {    //meme chose

            if (ligne_horizontale_deplacement == 7) {   //lorsqu'un pion arrive en haut de l'echequier, le pion devient une reine
                grille[numero_case] = "ReB";
                return 1;
            }
            else {
                return 1;
            }
        }
        else if (grille_couleur[numero_case_deplacement] == "aucune" && numero_case_deplacement - numero_case == 2 && ligne_horizontale_initiale < ligne_horizontale_deplacement) {   //Si le pion n'a pas été bougé, il peut avancer de 2 cases la premiere fois

            if (grille_couleur[numero_case_deplacement - 1] == "aucune" && ligne_horizontale_initiale == 1) {   // la case avant le deplacement doit etre vide et le pion doit etre sur sa case de depart

                return 1;

            }
            else {
                return 0;
            }


        }
        else {

            return 0; //pas valide pour un pion
        }


    }
    else if ((grille[numero_case] == "T1B" || grille[numero_case] == "T2B") && grille_couleur[numero_case_deplacement] != "blanc") {   //cas où la piece choisi est une tour ET que la case de destination n'est pas une piece "amie"

        //pour pouvoir bouger une tour, il faut bouger de 1 à 7 case soit en avant, soit en arriere, que ce soit en horizontale ou en verticale. Il faut faire attention à ce qu'aucune piece ne soit sur le chemin du deplacement (mais elle peut etre sur la case de destination)


        if (ligne_horizontale_initiale < ligne_horizontale_deplacement&& ligne_verticale_initiale == ligne_verticale_deplacement) {    //deplacement vers le haut

            int verif = 0;
            for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement - i] == "aucune") {   //on regarde en bas de la case destination donc on met -i

                    verif++;
                }

            }

            if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale == ligne_verticale_deplacement) {   //deplacement vers le bas

            int verif = 0;
            for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                if (grille_couleur[numero_case_deplacement + i] == "aucune") {   //on regarde en haut de la case destination donc on met +i
                    verif++;
                }

            }

            if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers la droite

            int verif = 0;
            for (int i = (ligne_verticale_deplacement - 1 - ligne_verticale_initiale); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement - 8 * i] == "aucune") {   //on regarde à gauche de la case destination donc on met -8*i
                    verif++;
                }

            }

            if (verif == ligne_verticale_deplacement - 1 - ligne_verticale_initiale) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers la gauche

            int verif = 0;
            for (int i = (ligne_verticale_initiale - 1 - ligne_verticale_deplacement); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement + 8 * i] == "aucune") {  //on regarde à droite de la case destination donc on met +8*i
                    verif++;
                }

            }

            if (verif == ligne_verticale_initiale - 1 - ligne_verticale_deplacement) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else {
            return 0;   //case chosie = case initiale ou tentative de deplacement en diagonale
        }



    }
    else if ((grille[numero_case] == "C1B" || grille[numero_case] == "C2B") && grille_couleur[numero_case_deplacement] != "blanc") {   //cas où la piece choisi est un cavlier et que la case destination n'est pas une case "amie"



        if (ligne_horizontale_initiale == ligne_horizontale_deplacement - 1 && ligne_verticale_initiale == ligne_verticale_deplacement - 2) {    //deplacement vers le haut d'une case et vers la droite de 2 cases

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement - 2 && ligne_verticale_initiale == ligne_verticale_deplacement - 1) {   //deplacement vers le haut de 2 cases et vers la droite d'une case

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement - 2 && ligne_verticale_initiale == ligne_verticale_deplacement + 1) {   //deplacement vers le haut de 2 cases et vers la gauche d'une case

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement - 1 && ligne_verticale_initiale == ligne_verticale_deplacement + 2) {   //deplacement vers le haut d'une case et vers la gauche de 2 cases

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement + 1 && ligne_verticale_initiale == ligne_verticale_deplacement - 2) {   //deplacement vers le bas d'une case et vers la droite de 2 cases

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement + 2 && ligne_verticale_initiale == ligne_verticale_deplacement - 1) {   //deplacement vers le bas de 2 cases et vers la droite d'une case

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement + 1 && ligne_verticale_initiale == ligne_verticale_deplacement + 2) {   //deplacement vers le bas d'une case et vers la gauche de 2 cases

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement + 2 && ligne_verticale_initiale == ligne_verticale_deplacement + 1) {   //deplacement vers le bas de 2 cases et vers la gauche d'une case

            return 1;
        }
        else {

            return 0;   //autre deplacement : erreur
        }


    }
    else if ((grille[numero_case] == "F1B" || grille[numero_case] == "F2B") && grille_couleur[numero_case_deplacement] != "blanc") {   //cas où la piece choisi est un fou et la case de destination n'est pas "amie"


        if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {    //deplacement vers le haut a droite


            if (ligne_horizontale_deplacement - ligne_horizontale_initiale == ligne_verticale_deplacement - ligne_verticale_initiale) {  //si oui, on est sur une diagonale car on avance autant à droite qu'en haut

                int verif = 0;
                for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {



                    if (grille_couleur[numero_case + 9 * i] == "aucune") {
                        verif++;

                    }

                }

                if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                    return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                }
                else {
                    return 0;   //au moins une case n'est pas vide
                }

            }
            else {
                return 0;
            }

        }
        else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le haut à gauche



            if (ligne_horizontale_deplacement - ligne_horizontale_initiale == ligne_verticale_initiale - ligne_verticale_deplacement) {  //si oui, on est sur une diagonale car on avance autant à gauche qu'en haut

                int verif = 0;
                for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {

                    if (grille_couleur[numero_case - 7 * i] == "aucune") {
                        verif++;
                    }

                }

                if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                    return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                }
                else {
                    return 0;   //au moins une case n'est pas vide
                }

            }
            else {
                return 0;
            }
        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers le bas à droite



            if (ligne_horizontale_initiale - ligne_horizontale_deplacement == ligne_verticale_deplacement - ligne_verticale_initiale) {  //si oui, on est sur une diagonale car on avance autant à droite qu'en bas

                int verif = 0;
                for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                    if (grille_couleur[numero_case + 7 * i] == "aucune") {
                        verif++;
                    }

                }

                if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                    return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                }
                else {
                    return 0;   //au moins une case n'est pas vide
                }

            }
            else {
                return 0;
            }


        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le bas à gauche



            if (ligne_horizontale_initiale - ligne_horizontale_deplacement == ligne_verticale_initiale - ligne_verticale_deplacement) {  //si oui, on est sur une diagonale car on avance autant à gauche qu'en bas

                int verif = 0;

                for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {



                    if (grille_couleur[numero_case - 9 * i] == "aucune") {
                        verif++;
                    }

                }

                if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                    return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                }
                else {
                    return 0;   //au moins une case n'est pas vide
                }

            }
            else {
                return 0;
            }

        }
        else {

            return 0;   //case chosie = case initiale ou tentative de deplacement autre que en diagonale
        }



    }
    else if ((grille[numero_case] == "ReB") && grille_couleur[numero_case_deplacement] != "blanc") {   //cas où la piece choisi est une reine


         //la reine peut se deplacer en diagonale ou en ligne droite sur autant de case que souhaite le joueur tant que ces cases sont vides, il s'agit donc des conditions de la tour ET du fou

        if (ligne_horizontale_initiale < ligne_horizontale_deplacement&& ligne_verticale_initiale == ligne_verticale_deplacement) {    //deplacement vers le haut

            int verif = 0;
            for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement - i] == "aucune") {
                    verif++;
                }

            }

            if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale == ligne_verticale_deplacement) {   //deplacement vers le bas

            int verif = 0;
            for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                if (grille_couleur[numero_case_deplacement + i] == "aucune") {
                    verif++;
                }

            }

            if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers la droite

            int verif = 0;
            for (int i = (ligne_verticale_deplacement - 1 - ligne_verticale_initiale); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement - 8 * i] == "aucune") {
                    verif++;
                }

            }

            if (verif == ligne_verticale_deplacement - 1 - ligne_verticale_initiale) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers la gauche

            int verif = 0;
            for (int i = (ligne_verticale_initiale - 1 - ligne_verticale_deplacement); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement + 8 * i] == "aucune") {
                    verif++;
                }

            }

            if (verif == ligne_verticale_initiale - 1 - ligne_verticale_deplacement) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {    //deplacement vers le haut a droite


            if (ligne_horizontale_deplacement - ligne_horizontale_initiale == ligne_verticale_deplacement - ligne_verticale_initiale) {  //si oui, on est sur une diagonale car on avance autant à droite qu'en haut

                int verif = 0;
                for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {

                    if (grille_couleur[numero_case + 9 * i] == "aucune") {
                        verif++;
                    }

                }
                if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                    return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                }
                else {
                    return 0;   //au moins une case n'est pas vide
                }

            }
            else {
                return 0;
            }




        }
        else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le haut à gauche

            if (ligne_horizontale_deplacement - ligne_horizontale_initiale == ligne_verticale_initiale - ligne_verticale_deplacement) {  //si oui, on est sur une diagonale car on avance autant à gauche qu'en haut

                int verif = 0;
                for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {

                    if (grille_couleur[numero_case - 7 * i] == "aucune") {
                        verif++;
                    }

                }
                if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                    return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                }
                else {
                    return 0;   //au moins une case n'est pas vide
                }

            }
            else {
                return 0;
            }
        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers le bas à droite

            if (ligne_horizontale_initiale - ligne_horizontale_deplacement == ligne_verticale_deplacement - ligne_verticale_initiale) {  //si oui, on est sur une diagonale car on avance autant à droite qu'en bas

                int verif = 0;
                for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                    if (grille_couleur[numero_case + 7 * i] == "aucune") {
                        verif++;
                    }

                }
                if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                    return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                }
                else {
                    return 0;   //au moins une case n'est pas vide
                }

            }
            else {
                return 0;
            }


        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le bas à gauche

            if (ligne_horizontale_initiale - ligne_horizontale_deplacement == ligne_verticale_initiale - ligne_verticale_deplacement) {  //si oui, on est sur une diagonale car on avance autant à gauche qu'en bas

                int verif = 0;
                for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                    if (grille_couleur[numero_case - 9 * i] == "aucune") {
                        verif++;
                    }

                }
                if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                    return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                }
                else {
                    return 0;   //au moins une case n'est pas vide
                }

            }
            else {
                return 0;
            }

        }
        else {
            return 0;   //case chosie = case initiale ou tentative de deplacement autre que en diagonale ou en ligne
        }



    }
    else if ((grille[numero_case] == "RoB") && grille_couleur[numero_case_deplacement] != "blanc") {   //cas où la piece choisi est un roi

            //le roi peut se deplacer comme la reine mais uniquement sur une case, nous n'avons donc pas besoin de vérifier que toutes les cases sont vides


        if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale == ligne_verticale_deplacement) {    //deplacement vers le haut

            if (numero_case_deplacement == numero_case + 1) {

                return 1;
            }
            else {

                return 0;
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale == ligne_verticale_deplacement) {   //deplacement vers le bas

            if (numero_case_deplacement == numero_case - 1) {

                return 1;
            }
            else {

                return 0;
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers la droite

            if (numero_case_deplacement == numero_case + 8) {

                return 1;
            }
            else {

                return 0;
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers la gauche

            if (numero_case_deplacement == numero_case - 8) {

                return 1;
            }
            else {

                return 0;
            }

        }
        else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {    //deplacement vers le haut a droite

            if (numero_case_deplacement == numero_case + 9) {

                return 1;
            }
            else {

                return 0;
            }



        }
        else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le haut à gauche

            if (numero_case_deplacement == numero_case - 7) {

                return 1;
            }
            else {

                return 0;
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers le bas à droite

            if (numero_case_deplacement == numero_case + 7) {

                return 1;
            }
            else {

                return 0;
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le bas à gauche

            if (numero_case_deplacement == numero_case - 9) {

                return 1;
            }
            else {

                return 0;
            }
        }
        else {

            return 0;   //erreur
        }


    }
    else if (grille[numero_case] == "RoB" && grille_couleur[numero_case_deplacement] == "blanc" && numero_case == 32) {//cas où la piece choisi est un roi et qu'on veut faire un roque
    //le roi possede 2 coups speciaux : le petit et le grand roque

        if ((grille[numero_case_deplacement] == "T1B" || grille[numero_case_deplacement] == "T2B") && numero_case_deplacement == 56) {  //petit roque


            if (grille_couleur[48] == "aucune" && grille_couleur[40] == "aucune") {
                return 2;   //2 = petit roque (deplacement special car le roi ne va pas prendre la place de la tour)
            }
            else {
                return 0;
            }
        }
        else if ((grille[numero_case_deplacement] == "T1B" || grille[numero_case_deplacement] == "T2B") && numero_case_deplacement == 0) { //grand roque

            if (grille_couleur[8] == "aucune" && grille_couleur[16] == "aucune" && grille_couleur[24] == "aucune") {

                return 3; //3 = grand roque
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    else {

        return 0;
    }
}

int verification_J2(string grille[], string grille_couleur[], int numero_case, int numero_case_deplacement)
{



    //afin de vérifier les déplacements, on a besoin de connaitre les numéros de ligne horizontale et verticale

    int ligne_horizontale_initiale = numero_case % 8;       //pour avoir le numero de ligne horizontal, il suffit de faire le numero de case modulo 8 et de regarder le numero de ligne entre 0 et 7
    int ligne_horizontale_deplacement = numero_case_deplacement % 8;

    int ligne_verticale_initiale = 0;
    int ligne_verticale_deplacement = 0;

    if (0 <= numero_case && numero_case < 8) {                             //pour avoir le numero de ligne vertical il faut verifier pour chaque colonne si la case y est (entre 1 et 8)
        ligne_verticale_initiale = 1;
    }
    else if (8 <= numero_case && numero_case < 16) {
        ligne_verticale_initiale = 2;
    }
    else if (16 <= numero_case && numero_case < 24) {
        ligne_verticale_initiale = 3;
    }
    else if (24 <= numero_case && numero_case < 32) {
        ligne_verticale_initiale = 4;
    }
    else if (32 <= numero_case && numero_case < 40) {
        ligne_verticale_initiale = 5;
    }
    else if (40 <= numero_case && numero_case < 48) {
        ligne_verticale_initiale = 6;
    }
    else if (48 <= numero_case && numero_case < 56) {
        ligne_verticale_initiale = 7;
    }
    else if (56 <= numero_case && numero_case < 64) {
        ligne_verticale_initiale = 8;
    }


    if (0 <= numero_case_deplacement && numero_case_deplacement < 8) {
        ligne_verticale_deplacement = 1;
    }
    else if (8 <= numero_case_deplacement && numero_case_deplacement < 16) {
        ligne_verticale_deplacement = 2;
    }
    else if (16 <= numero_case_deplacement && numero_case_deplacement < 24) {
        ligne_verticale_deplacement = 3;
    }
    else if (24 <= numero_case_deplacement && numero_case_deplacement < 32) {
        ligne_verticale_deplacement = 4;
    }
    else if (32 <= numero_case_deplacement && numero_case_deplacement < 40) {
        ligne_verticale_deplacement = 5;
    }
    else if (40 <= numero_case_deplacement && numero_case_deplacement < 48) {
        ligne_verticale_deplacement = 6;
    }
    else if (48 <= numero_case_deplacement && numero_case_deplacement < 56) {
        ligne_verticale_deplacement = 7;
    }
    else if (56 <= numero_case_deplacement && numero_case_deplacement < 64) {
        ligne_verticale_deplacement = 8;
    }








    if (grille[numero_case] == "P1N" || grille[numero_case] == "P2N" || grille[numero_case] == "P3N" || grille[numero_case] == "P4N" || grille[numero_case] == "P5N" || grille[numero_case] == "P6N" || grille[numero_case] == "P7N" || grille[numero_case] == "P8N") {  //cas où la piece choisi est un pion



        //pour pouvoir bouger un pion, il faut soit avancer de une case sur une case vide, soit avancer d'une case en diagonale pour éliminer un pion ennemi

        if (grille_couleur[numero_case_deplacement] == "aucune" && numero_case_deplacement - numero_case == -1 && ligne_horizontale_initiale > ligne_horizontale_deplacement) {    //2 conditions : la case doit etre vide et doit etre la case en dessous de la case precedente

            if (ligne_horizontale_deplacement == 0) {   //lorsqu'un pion arrive en bas de l'echequier, le pion devient une reine
                grille[numero_case] = "ReN";
                return 1;
            }
            else {
                return 1;
            }
        }
        else if (grille_couleur[numero_case_deplacement] == "blanc" && numero_case_deplacement - numero_case == -9 && ligne_horizontale_initiale > ligne_horizontale_deplacement) {  //2 conditions : la case est une piece noire et se trouve à une case en diagonale de la precedente

            if (ligne_horizontale_deplacement == 0) {
                grille[numero_case] = "ReN";
                return 1;
            }
            else {
                return 1;
            }
        }
        else if (grille_couleur[numero_case_deplacement] == "blanc" && numero_case_deplacement - numero_case == 7 && ligne_horizontale_initiale > ligne_horizontale_deplacement) {    //meme chose

            if (ligne_horizontale_deplacement == 0) {
                grille[numero_case] = "ReN";
                return 1;
            }
            else {
                return 1;
            }
        }
        else if (grille_couleur[numero_case_deplacement] == "aucune" && numero_case - numero_case_deplacement == 2 && ligne_horizontale_initiale > ligne_horizontale_deplacement) {   //Si le pion n'a pas été bougé, il peut avancer de 2 cases la premiere fois

            if (grille_couleur[numero_case - 1] == "aucune" && ligne_horizontale_initiale == 6) {   // la case avant le deplacement doit etre vide et le pion doit etre sur sa case de depart

                return 1;

            }
            else {
                return 0;
            }
        }
        else {

            return 0; //pas valide pour un pion
        }


    }
    else if ((grille[numero_case] == "T1N" || grille[numero_case] == "T2N") && grille_couleur[numero_case_deplacement] != "noir") {   //cas où la piece choisi est une tour ET que la case de destination n'est pas une piece "amie"

         //pour pouvoir bouger une tour, il faut bouger de 1 à 7 case soit en avant, soit en arriere, que ce soit en horizontale ou en verticale. Il faut faire attention à ce qu'aucune piece ne soit sur le chemin du deplacement (mais elle peut etre sur la case de destination)


        if (ligne_horizontale_initiale < ligne_horizontale_deplacement&& ligne_verticale_initiale == ligne_verticale_deplacement) {    //deplacement vers le haut

            int verif = 0;
            for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement - i] == "aucune") {
                    verif++;
                }

            }

            if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale == ligne_verticale_deplacement) {   //deplacement vers le bas

            int verif = 0;
            for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                if (grille_couleur[numero_case_deplacement + i] == "aucune") {
                    verif++;
                }

            }

            if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers la droite

            int verif = 0;
            for (int i = (ligne_verticale_deplacement - 1 - ligne_verticale_initiale); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement - 8 * i] == "aucune") {
                    verif++;
                }

            }

            if (verif == ligne_verticale_deplacement - 1 - ligne_verticale_initiale) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers la gauche

            int verif = 0;
            for (int i = (ligne_verticale_initiale - 1 - ligne_verticale_deplacement); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                if (grille_couleur[numero_case_deplacement + 8 * i] == "aucune") {
                    verif++;
                }

            }

            if (verif == ligne_verticale_initiale - 1 - ligne_verticale_deplacement) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else {
            return 0;   //case chosie = case initiale ou tentative de deplacement en diagonale
        }



    }
    else if ((grille[numero_case] == "C1N" || grille[numero_case] == "C2N") && grille_couleur[numero_case_deplacement] != "noir") {   //cas où la piece choisi est un cavlier et que la case destination n'est pas une case "amie"





        if (ligne_horizontale_initiale == ligne_horizontale_deplacement - 1 && ligne_verticale_initiale == ligne_verticale_deplacement - 2) {    //deplacement vers le haut d'une case et vers la droite de 2 cases

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement - 2 && ligne_verticale_initiale == ligne_verticale_deplacement - 1) {   //deplacement vers le haut de 2 cases et vers la droite d'une case

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement - 2 && ligne_verticale_initiale == ligne_verticale_deplacement + 1) {   //deplacement vers le haut de 2 cases et vers la gauche d'une case

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement - 1 && ligne_verticale_initiale == ligne_verticale_deplacement + 2) {   //deplacement vers le haut d'une case et vers la gauche de 2 cases

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement + 1 && ligne_verticale_initiale == ligne_verticale_deplacement - 2) {   //deplacement vers le bas d'une case et vers la droite de 2 cases

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement + 2 && ligne_verticale_initiale == ligne_verticale_deplacement - 1) {   //deplacement vers le bas de 2 cases et vers la droite d'une case

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement + 1 && ligne_verticale_initiale == ligne_verticale_deplacement + 2) {   //deplacement vers le bas d'une case et vers la gauche de 2 cases

            return 1;
        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement + 2 && ligne_verticale_initiale == ligne_verticale_deplacement + 1) {   //deplacement vers le bas de 2 cases et vers la gauche d'une case

            return 1;
        }
        else {

            return 0;   //autre deplacement : erreur
        }


    }
    else if ((grille[numero_case] == "F1N" || grille[numero_case] == "F2N") && grille_couleur[numero_case_deplacement] != "noir") {   //cas où la piece choisi est un fou et la case de destination n'est pas "amie"


    if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {    //deplacement vers le haut a droite


        if (ligne_horizontale_deplacement - ligne_horizontale_initiale == ligne_verticale_deplacement - ligne_verticale_initiale) {  //si oui, on est sur une diagonale car on avance autant à droite qu'en haut

            int verif = 0;
            for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {

                if (grille_couleur[numero_case + 9 * i] == "aucune") {
                    verif++;
                }

            }
            if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else {
            return 0;
        }




    }
    else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le haut à gauche

        if (ligne_horizontale_deplacement - ligne_horizontale_initiale == ligne_verticale_initiale - ligne_verticale_deplacement) {  //si oui, on est sur une diagonale car on avance autant à gauche qu'en haut

            int verif = 0;
            for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {

                if (grille_couleur[numero_case - 7 * i] == "aucune") {
                    verif++;
                }

            }
            if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else {
            return 0;
        }
    }
    else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers le bas à droite

        if (ligne_horizontale_initiale - ligne_horizontale_deplacement == ligne_verticale_deplacement - ligne_verticale_initiale) {  //si oui, on est sur une diagonale car on avance autant à droite qu'en bas

            int verif = 0;
            for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                if (grille_couleur[numero_case + 7 * i] == "aucune") {
                    verif++;
                }

            }
            if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else {
            return 0;
        }


    }
    else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le bas à gauche

        if (ligne_horizontale_initiale - ligne_horizontale_deplacement == ligne_verticale_initiale - ligne_verticale_deplacement) {  //si oui, on est sur une diagonale car on avance autant à gauche qu'en bas

            int verif = 0;
            for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                if (grille_couleur[numero_case - 9 * i] == "aucune") {
                    verif++;
                }

            }
            if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
            }
            else {
                return 0;   //au moins une case n'est pas vide
            }

        }
        else {
            return 0;
        }

    }
    else {
        return 0;   //case chosie = case initiale ou tentative de deplacement autre que en diagonale
    }



    }
    else if ((grille[numero_case] == "ReN") && grille_couleur[numero_case_deplacement] != "noir") {   //cas où la piece choisi est une reine


         //la reine peut se deplacer en diagonale ou en ligne droite sur autant de case que souhaite le joueur tant que ces cases sont vides, il s'agit donc des conditions de la tour ET du fou

         if (ligne_horizontale_initiale < ligne_horizontale_deplacement&& ligne_verticale_initiale == ligne_verticale_deplacement) {    //deplacement vers le haut

             int verif = 0;
             for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                 if (grille_couleur[numero_case_deplacement - i] == "aucune") {
                     verif++;
                 }

             }

             if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                 return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
             }
             else {
                 return 0;   //au moins une case n'est pas vide
             }

         }
         else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale == ligne_verticale_deplacement) {   //deplacement vers le bas

             int verif = 0;
             for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                 if (grille_couleur[numero_case_deplacement + i] == "aucune") {
                     verif++;
                 }

             }

             if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                 return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
             }
             else {
                 return 0;   //au moins une case n'est pas vide
             }


         }
         else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers la droite

             int verif = 0;
             for (int i = (ligne_verticale_deplacement - 1 - ligne_verticale_initiale); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                 if (grille_couleur[numero_case_deplacement - 8 * i] == "aucune") {
                     verif++;
                 }

             }

             if (verif == ligne_verticale_deplacement - 1 - ligne_verticale_initiale) {
                 return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
             }
             else {
                 return 0;   //au moins une case n'est pas vide
             }


         }
         else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers la gauche

             int verif = 0;
             for (int i = (ligne_verticale_initiale - 1 - ligne_verticale_deplacement); i > 0; i--) {  //on va vérifier pour toutes les cases entre la case initiale et la case de deplacement si elles sont bien vide

                 if (grille_couleur[numero_case_deplacement + 8 * i] == "aucune") {
                     verif++;
                 }

             }

             if (verif == ligne_verticale_initiale - 1 - ligne_verticale_deplacement) {
                 return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
             }
             else {
                 return 0;   //au moins une case n'est pas vide
             }

         }
         else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {    //deplacement vers le haut a droite


             if (ligne_horizontale_deplacement - ligne_horizontale_initiale == ligne_verticale_deplacement - ligne_verticale_initiale) {  //si oui, on est sur une diagonale car on avance autant à droite qu'en haut

                 int verif = 0;
                 for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {

                     if (grille_couleur[numero_case + 9 * i] == "aucune") {
                         verif++;
                     }

                 }
                 if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                     return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                 }
                 else {
                     return 0;   //au moins une case n'est pas vide
                 }

             }
             else {
                 return 0;
             }




         }
         else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le haut à gauche

             if (ligne_horizontale_deplacement - ligne_horizontale_initiale == ligne_verticale_initiale - ligne_verticale_deplacement) {  //si oui, on est sur une diagonale car on avance autant à gauche qu'en haut

                 int verif = 0;
                 for (int i = (ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale); i > 0; i--) {

                     if (grille_couleur[numero_case - 7 * i] == "aucune") {
                         verif++;
                     }

                 }
                 if (verif == ligne_horizontale_deplacement - 1 - ligne_horizontale_initiale) {
                     return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                 }
                 else {
                     return 0;   //au moins une case n'est pas vide
                 }

             }
             else {
                 return 0;
             }
         }
         else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers le bas à droite

             if (ligne_horizontale_initiale - ligne_horizontale_deplacement == ligne_verticale_deplacement - ligne_verticale_initiale) {  //si oui, on est sur une diagonale car on avance autant à droite qu'en bas

                 int verif = 0;
                 for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                     if (grille_couleur[numero_case + 7 * i] == "aucune") {
                         verif++;
                     }

                 }
                 if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                     return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                 }
                 else {
                     return 0;   //au moins une case n'est pas vide
                 }

             }
             else {
                 return 0;
             }


         }
         else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le bas à gauche

             if (ligne_horizontale_initiale - ligne_horizontale_deplacement == ligne_verticale_initiale - ligne_verticale_deplacement) {  //si oui, on est sur une diagonale car on avance autant à gauche qu'en bas

                 int verif = 0;
                 for (int i = (ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement); i > 0; i--) {

                     if (grille_couleur[numero_case - 9 * i] == "aucune") {
                         verif++;
                     }

                 }
                 if (verif == ligne_horizontale_initiale - 1 - ligne_horizontale_deplacement) {
                     return 1;   //toutes les cases entre la case intiale et la case de deplacement sont vides, le deplacement est possible
                 }
                 else {
                     return 0;   //au moins une case n'est pas vide
                 }

             }
             else {
                 return 0;
             }

         }
         else {
             return 0;   //case chosie = case initiale ou tentative de deplacement autre que en diagonale ou en ligne
         }



    }
    else if ((grille[numero_case] == "RoN") && grille_couleur[numero_case_deplacement] != "noir") {   //cas où la piece choisi est un roi

            //le roi peut se deplacer comme la reine mais uniquement sur une case, nous n'avons donc pas besoin de vérifier que toutes les cases sont vides


        if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale == ligne_verticale_deplacement) {    //deplacement vers le haut

            if (numero_case_deplacement == numero_case + 1) {

                return 1;
            } 
            else {

                return 0;
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale == ligne_verticale_deplacement) {   //deplacement vers le bas

            if (numero_case_deplacement == numero_case - 1) {

                return 1;
            }
            else {

                return 0;
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers la droite

            if (numero_case_deplacement == numero_case + 8) {

                return 1;
            }
            else {

                return 0;
            }


        }
        else if (ligne_horizontale_initiale == ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers la gauche

            if (numero_case_deplacement == numero_case - 8) {

                return 1;
            }
            else {

                return 0;
            }

        }
        else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {    //deplacement vers le haut a droite

            if (numero_case_deplacement == numero_case + 9) {

                return 1;
            }
            else {

                return 0;
            }



        }
        else if (ligne_horizontale_initiale < ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le haut à gauche

            if (numero_case_deplacement == numero_case - 7) {

                return 1;
            }
            else {

                return 0;
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale < ligne_verticale_deplacement) {   //deplacement vers le bas à droite

            if (numero_case_deplacement == numero_case + 7) {

                return 1;
            }
            else {

                return 0;
            }

        }
        else if (ligne_horizontale_initiale > ligne_horizontale_deplacement && ligne_verticale_initiale > ligne_verticale_deplacement) {   //deplacement vers le bas à gauche

            if (numero_case_deplacement == numero_case - 9) {

                return 1;
            }
            else {

                return 0;
            }

        }
    }
    else if (grille[numero_case] == "RoN" && grille_couleur[numero_case_deplacement] == "noir" && numero_case == 39) {//cas où la piece choisi est un roi et qu'on veut faire un roque
    //le roi possede 2 coups speciaux : le petit et le grand roque

        if ((grille[numero_case_deplacement] == "T1N" || grille[numero_case_deplacement] == "T2N") && numero_case_deplacement == 63) {  //petit roque

            if (grille_couleur[47] == "aucune" && grille_couleur[55] == "aucune") { //les deux cases entre le roi et la tour
                return 2;   //2 = petit roque (deplacement special car le roi ne va pas prendre la place de la tour)
            }
            else {
                return 0;
            }
        }
        else if ((grille[numero_case_deplacement] == "T1N" || grille[numero_case_deplacement] == "T2N") && numero_case_deplacement == 7) { //grand roque

            if (grille_couleur[15] == "aucune" && grille_couleur[23] == "aucune" && grille_couleur[31] == "aucune") {

                return 3; //3 = grand roque
            }
            else {
                return 0;
            }
        }
        else {

            return 0;   //erreur
        }


    }
    else {

        return 0;
    }




}

void deplacement(string grille[], string grille_couleur[], int numero_case, int numero_case_deplacement, int type_de_coup)
{

    if (type_de_coup == 1) {
        /*
            on est ici si le deplacement est deja validé
            on va tout d'abord remplacer la case de destination par la case initiale puis nous allons "vider" la case initiale
            il n'y a donc aucune difference entre une case de destination vide ou occupée
        */

        grille[numero_case_deplacement] = grille[numero_case];
        grille_couleur[numero_case_deplacement] = grille_couleur[numero_case];

        grille[numero_case] = "   ";
        grille_couleur[numero_case] = "aucune";
    }
    else if (type_de_coup == 2) {   //petit roque

        /*
            on va faire le coup special : petit roque
            on joue le roi et la tour la plus proche que l'on va rapprocher et échanger
            nous avons : roi, case vide, case vide, tour
            et nous voulons : case vide, tour, roi, case vide
        */

        grille[numero_case + 16] = grille[numero_case];     //on place le roi 2 cases à droite
        grille_couleur[numero_case + 16] = grille_couleur[numero_case];

        grille[numero_case_deplacement - 16] = grille[numero_case_deplacement];     //on place la tour 2 cases à gauche
        grille_couleur[numero_case_deplacement - 16] = grille_couleur[numero_case_deplacement];

        grille[numero_case] = "   ";    //on enleve les anciens roi et tour
        grille_couleur[numero_case] = "aucune";

        grille[numero_case_deplacement] = "   ";
        grille_couleur[numero_case_deplacement] = "aucune";

    }
    else if (type_de_coup == 3) {   //grand roque

         /*
            on va faire le coup special : grand roque
            on joue le roi et la tour la plus éloignée que l'on va rapprocher et échanger
            nous avons : tour, case vide, case vide, case vide, roi
            et nous voulons : case vide, case vide, roi, tour, case vide
        */

        grille[numero_case - 16] = grille[numero_case];     //on place le roi 2 cases à gauche
        grille_couleur[numero_case - 16] = grille_couleur[numero_case];

        grille[numero_case_deplacement + 24] = grille[numero_case_deplacement];     //on place la tour 3 cases à droite
        grille_couleur[numero_case_deplacement + 24] = grille_couleur[numero_case_deplacement];

        grille[numero_case] = "   ";    //on enleve les anciens roi et tour
        grille_couleur[numero_case] = "aucune";

        grille[numero_case_deplacement] = "   ";
        grille_couleur[numero_case_deplacement] = "aucune";

    }







}

void VerifVictoire(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre)
{
    int VictoireJ1 = 1;
    int VictoireJ2 = 1;


    for (int i = 64; i--; i > 0) {  //marche uniquement dans ce sens : on parcourt le tableau de 63 à 0

        if (grille[i] == "RoN") {
            VictoireJ1 = 0;
        }
        else if (grille[i] == "RoB") {
            VictoireJ2 = 0;
        }
        else {

        }
    }
    if (VictoireJ1 != 0) {
        //Victoire du J1 (plus de roi noir sur le plateau)



        affichageGrille(grille, grille_couleur, renderer, fenetre);
        cout << "Victoire de " << J1 << endl;
        string rejouer;
        cout << "entrer quelque chose pour rejouer" << endl;
        cin >> rejouer;         //ce cin a pour unique fonction de permettre aux joueurs de regarder la grille avant de recommencer
        InitialisationGrille(renderer, fenetre);

    }
    else if (VictoireJ2 != 0) {
        //Victoire du J2


        affichageGrille(grille, grille_couleur, renderer, fenetre);
        cout << "Victoire de " << J2 << endl;
        string rejouer;
        cout << "entrer quelque chose pour rejouer" << endl;
        cin >> rejouer;
        InitialisationGrille(renderer, fenetre);

    }
    else {
        //pas de victoire
    }

}

void VerifMiseEnEchec(string grille[], string grille_couleur[])
{

    /*
        Il y a une mise en echec si n'importe quelle piece sur la grille a la possibilité de prendre le roi ennemi
        Nous allons donc devoir tester pour toutes les pieces si elles pouvent acceder au roi
        On peut se retrouver en echec si on bouge la mauvaise piece :
        nous devons donc verifier a chaque tour si chaque joueur n'a pas été mis en echec (et pas uniquement pour le joueur qui vient de subir le deplacement)
    */

    //tout d'abord on va regarder où se trouve le roi noir et le roi blanc

    int numero_case_RoN;
    int numero_case_RoB;


    for (int i = 0; i < 64; i++) {
        if (grille[i] == "RoN") {

            numero_case_RoN = i;
        }
        if (grille[i] == "RoB") {

            numero_case_RoB = i;
        }
    }

    //Nous avons donc les numeros de case des 2 rois

    //Il faut maintenant vérifier pour chaque piece si un deplacement sur le roi est possible

    for (int i = 0; i < 64; i++) {

        if (grille_couleur[i] == "blanc") { //on va tester toutes les pieces blanches

            int numero_case = i;    //case de la piece blanche

            int verif = verification_J1(grille, grille_couleur, numero_case, numero_case_RoN);  //verif avec comme case de destination la case du roi ennemi

            if (verif == 1) {   //si le deplacement est possible, il y a une mise en echec  (impossible de tomber sur 2 ou 3 car les roques ne sont pas possibles)
                //Mise en echec sur le roi noir !
                cout << "! Mise en echec sur le roi noir !" << endl;
            }
            else {
                //Pas de mise en echec
            }



        }
        else if (grille_couleur[i] == "noir") { //on va tester toutes les pieces noirs

            int numero_case = i;    //case de la piece noir

            int verif = verification_J2(grille, grille_couleur, numero_case, numero_case_RoB);  //verif avec comme case de destination la case du roi ennemi

            if (verif == 1) {   //si le deplacement est possible, il y a une mise en echec
                //Mise en echec sur le roi blanc !
                cout << "! Mise en echec sur le roi blanc !" << endl;
            }
            else {
                //Pas de mise en echec
            }



        }
        else {
            //Pas de piece sur cette case donc pas de possible mise en echec
        }

    }

}


void TourJ1_IA(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre)
{
    cout << "Tour de " << J1 << endl;
    cout << "Choisir la case contenant le pion a bouger" << endl;
    string case_jouee;
    cin >> case_jouee;
    int numero_case = conversion(case_jouee);   //on retrouve le numero dans le tableau
    if (grille_couleur[numero_case] == "blanc") {    //verif couleur de la piece

        cout << "Choisir la case ou se deplacer" << endl;
        string case_deplacement;
        cin >> case_deplacement;
        int numero_case_deplacement = conversion(case_deplacement);
        int coup = verification_J1(grille, grille_couleur, numero_case, numero_case_deplacement);//verif en fonction de la piece (on veut savoir si la case voulu est bien une case possible pour un déplacement avec cette piece), c'est égal à 0 si c'est pas bon
        if (coup != 0)
        {

            deplacement(grille, grille_couleur, numero_case, numero_case_deplacement, coup);  //si le deplacement est correct, on deplace la piece

            affichageGrille(grille, grille_couleur, renderer, fenetre);

            VerifVictoire(grille, grille_couleur, J1, J2, renderer, fenetre);  //on verifie si le joueur a gagné (on doit le mettre avant la mise en echec car sans roi, la mise en echec ne peut se faire correctement

            VerifMiseEnEchec(grille, grille_couleur);

            Tour_IA(grille, grille_couleur, J1, J2, renderer, fenetre); //si il n a pas gagné, c'est le tour du joueur 2 : ici de l'IA

        }
        else {
            cout << "probleme dans le deplacement : veuillez reeesayer :" << endl;
            TourJ1_IA(grille, grille_couleur, J1, J2, renderer, fenetre); //on relance le tour de Joueur 1
        }


    }
    else {

        //erreur
        cout << "probleme dans le choix du pion : veuillez reeesayer :" << endl;
        TourJ1_IA(grille, grille_couleur, J1, J2, renderer, fenetre);     //on relance le tour de Joueur 1
    }
}

void Tour_IA(string grille[], string grille_couleur[], string J1, string J2, SDL_Renderer* renderer, SDL_Window* fenetre)
{

    //on va utiliser l'alogrithme minmax : cet algorithme va parcourir tous les chemins possibles sur plusieurs tours et enfin donner une note a chaque fin de chemins 
    //Au final, ce sera le meilleur compromis entre potentiel du chemin (valeur de la piece éliminé) et le risque du chemin qui sera choisi pour l'algorithme
    //Ici, la fonction minmax() fera le calcul entre gain et risque

    int numero_case = minmax(grille, grille_couleur, 1);
    int numero_case_deplacement = minmax(grille, grille_couleur, 2);


    deplacement(grille, grille_couleur, numero_case, numero_case_deplacement, 1);  //l'IA ne peut que faire un coup "classique" (1)

    affichageGrille(grille, grille_couleur, renderer, fenetre);

    VerifVictoire(grille, grille_couleur, J1, J2, renderer, fenetre);  //on verifie si le joueur a gagné (on doit le mettre avant la mise en echec car sans roi, la mise en echec ne peut se faire correctement

    VerifMiseEnEchec(grille, grille_couleur);

    TourJ1_IA(grille, grille_couleur, J1, J2, renderer, fenetre); //si il n a pas gagné, c'est le tour du joueur 2 : ici de l'IA
}

int minmax(string grille[], string grille_couleur[], int numero_return)
{
    //La fonction va renvoyer pour chaque piece de l'IA, la valeur du compromis de chaque chemin

    int value[64][64];  //tableau contenant la valeur de chaque chemin

    for (int i = 0; i < 64; i++) {  //On initialise le tableau a 2 dimensions value
        for (int y = 0; y < 64; y++) {
            value[i][y] = 0;
        }
    }

    string grille_simulation[64];
    string grille_simulation_couleur[64];
    string save1[64];       //save1 = sauvegarde pour réinitialiser la grille simulation dans la boucle for des pieces noires
    string save1_couleur[64];
    string save2[64];       //save2 = sauvegarde pour réinitialiser la grille simulation dans la boucle for des pieces blanches
    string save2_couleur[64];

    for (int i = 0; i < 64; i++) {  //on initialise les nouvelles grilles qui serviront a prevoir plusieurs tours
        grille_simulation[i] = grille[i];
        grille_simulation_couleur[i] = grille_couleur[i];
    }

    for (int i = 0; i < 64; i++) {  //on initialise les grilles de sauvegarde qui permettent de comparer si les pieces prisent precedemment sont rentables par rapport a la piece qui a été perdue
        save1[i] = grille_simulation[i];
        save1_couleur[i] = grille_simulation_couleur[i];
    }




    for (int i = 0; i < 64; i++) {  //On commence par MAX (regarder le potentiel des déplacements 

        if (grille_simulation_couleur[i] == "noir") { //on va tester toutes les pieces noirs



            for (int y = 0; y < 64; y++) {  //on va regarder toutes les cases

                for (int i = 0; i < 64; i++) {  //on initialise les nouvelles grilles qui serviront a prevoir plusieurs tours
                    grille_simulation[i] = grille[i];
                    grille_simulation_couleur[i] = grille_couleur[i];
                }




                int verif = verification_J2(save1, save1_couleur, i, y);  //verif avec la piece choisie (i) et la case choisie (y)




                if (verif == 1) {   // le deplacement est possible de la case i à la case y


                    if (grille_simulation[y] == "RoB") {
                        value[i][y] = value[i][y] + 100;    //Pour favoriser les mises en echec ou la victoire
                                                            //+100 = on prend le roi
                    }
                    else if (grille_simulation_couleur[y] == "blanc") {    //Pour favoriser la prise d'une piece
                        value[i][y] = value[i][y] + 50; //+10 = on prend une piece
                    }
                    else if (grille_couleur[y] == "aucune") {
                        value[i][y] = value[i][y] + 5;  //le potentiel n'augmente pas si on ne prend aucune piece ennemie
                                                        //+0 = on ne prend rien
                    }

                    deplacement(grille_simulation, grille_simulation_couleur, i, y, 1);

                    int vicN = VerifVictoire_Simulation(grille_simulation);  //on verifie si l'ia a gagné dans la simulation (si oui alors il faut prendre ce chemin)

                    int meeN = VerifMiseEnEchec_Simulation(grille_simulation, grille_simulation_couleur);   //on vérifie si le roi blanc est mis en echec (si oui il faut prendre ce chemin si l'ia ne gagne pas ailleurs)

                    if (vicN == 1) {
                        value[i][y] = value[i][y] + 5000;   //+5000 = victoire
                    }

                    if (meeN == 1) {
                        value[i][y] = value[i][y] + 3000;   //+3000 = mise en echec
                    }


                    for (int i = 0; i < 64; i++) {  //on initialise les grilles de sauvegarde qui permettent de réinitialiser grille simulation dans la boucle for des pieces blanches
                        save2[i] = grille_simulation[i];
                        save2_couleur[i] = grille_simulation_couleur[i];
                    }


                    for (int w = 0; w < 64; w++) {  //On va maitenant vérifier le risque en faisant le MIN


                        for (int v = 0; v < 64; v++) {  //on va regarder toutes les cases




                            if (grille_simulation_couleur[w] == "blanc") { //on va tester toutes les pieces blanches

                                int verif = verification_J1(save2, save2_couleur, w, v);  //verif avec la piece blanche choisie (w) et la piece noire qui vient de se déplacer (y)

                                if (verif == 1) {   // le deplacement est possible de la case w à la case i

                                    //la piece blanche a la possibilité d'éliminer la piece noire joué precedemment

                                    if (grille_simulation_couleur[v] == "noir") {    //Si la pièce noire avait éliminé une piece blanche au tour precedent, on vérifit que ça vallait le coup de se faire éliminer juste apres

                                        int c = Valeur_Piece(grille_simulation, v) - Valeur_Piece(save1, y);
                                        if (c > 0) {
                                            //si la valeur de la piece noire est plus grande que la valeur de la piece blanche
                                            value[i][y] = value[i][y] - 90; //-90 = on prend une piece mais on perd la notre et on perd l'echange
                                        }
                                        else if (c == 0) {
                                            value[i][y] = value[i][y] - 10; //-5 = on prend une piece mais on perd la notre et on a un echange neutre
                                        }
                                        else {
                                            //la valeur de la piece noire est inférieure à la valeur de la piece blanche éliminée precedemment : c'est donc rentable
                                            value[i][y] = value[i][y] - 5; //-10 = on prend une piece mais on perd la notre et on gagne l'echange
                                        }



                                    }

                                    deplacement(grille_simulation, grille_simulation_couleur, w, v, 1);

                                    int vicB = VerifVictoire_Simulation(grille_simulation);  //on verifie si l'ia a perdu dans la simulation (si oui alors il faut éviter ce chemin)

                                    int meeB = VerifMiseEnEchec_Simulation(grille_simulation, grille_simulation_couleur);   //on vérifie si le roi noir est mis en echec (si oui il faut éviter ce chemin si l'ia ne perd pas ailleurs)

                                    if (vicB == 2) {
                                        value[i][y] = value[i][y] - 4000;   //-4000 = défaite de l'IA
                                    }

                                    if (meeB == 2) {
                                        value[i][y] = value[i][y] - 2000;   //-2000 = mise en echec
                                    }



                                }
                                else {
                                    //La piece noire ne se fait pas éliminée
                                    value[i][y] = value[i][y] - 0;
                                }

                            }// la piece n'est pas blanche : il ne se passe rien

                        }

                    }  //fin boucle for des pieces blanches

                }
                else {
                    //Deplacement impossible
                    value[i][y] = -1000;
                }

            }   //fin boucle for pour les possibilités de mouvement

        }   // la piece n'est pas noir : il ne se passe rien

    }   //fin boucle for des pieces noirs


    int max = -200;
    int valeur_i = 0;
    int valeur_y = 0;

    for (int i = 0; i < 64; i++) {  //on regarde tous les chemins
        for (int y = 0; y < 64; y++) {

            if (value[i][y] > max) {    //Si ce chemin est meilleur que le precedent, on change la valeur de max, de i et de y
                max = value[i][y];
                cout << i << endl << y << endl << max << endl;
                valeur_i = i;
                valeur_y = y;

            }
        }
    }

    if (numero_return == 1) {   //Si on veut numero_case
        return valeur_i;
    }
    else if (numero_return == 2) {    //Si on veut numero_case_deplacement
        return valeur_y;
    }

}

int Valeur_Piece(string grille[], int numero_case)
{
    //Cette fonction sert à aider l'IA à choisir si elle peut sacrifier sa piece pour en capturer une autre avec une valeur plus grande ou de valeur égale



    if (grille[numero_case] == "P1B" || grille[numero_case] == "P2B" || grille[numero_case] == "P3B" || grille[numero_case] == "P4B" || grille[numero_case] == "P5B" || grille[numero_case] == "P6B" || grille[numero_case] == "P7B" || grille[numero_case] == "P8B" || grille[numero_case] == "P1N" || grille[numero_case] == "P2N" || grille[numero_case] == "P3N" || grille[numero_case] == "P4N" || grille[numero_case] == "P5N" || grille[numero_case] == "P6N" || grille[numero_case] == "P7N" || grille[numero_case] == "P8N") {
        //cas où la piece choisi est un pion

        return 1;
    }
    else if (grille[numero_case] == "T1B" || grille[numero_case] == "T2B" || grille[numero_case] == "T1N" || grille[numero_case] == "T2N") {   //cas où la piece choisi est une tour ET que la case de destination n'est pas une piece "amie"

        return 2;
    }
    else if (grille[numero_case] == "C1B" || grille[numero_case] == "C2B" || grille[numero_case] == "C1N" || grille[numero_case] == "C2N") {   //cas où la piece choisi est un cavlier et que la case destination n'est pas une case "amie"

        return 2;
    }
    else if (grille[numero_case] == "F1B" || grille[numero_case] == "F2B" || grille[numero_case] == "F1N" || grille[numero_case] == "F2N") {   //cas où la piece choisi est un fou et la case de destination n'est pas "amie"

        return 2;
    }
    else if (grille[numero_case] == "ReB" || grille[numero_case] == "ReN") {   //cas où la piece choisi est une reine

        return 3;
    }
    else if (grille[numero_case] == "RoB" || grille[numero_case] == "RoN") {   //cas où la piece choisi est un roi

        return 4;
    }
    else {
        return 0;  //Si il n'y avait aucune piece
    }

}

int VerifVictoire_Simulation(string grille[])
{

    int VictoireJ1 = 1;
    int VictoireJ2 = 1;


    for (int i = 0; i < 64; i++) {

        if (grille[i] == "RoN") {
            VictoireJ1 = 0;
        }
        else if (grille[i] == "RoB") {
            VictoireJ2 = 0;
        }
        else {

        }
    }
    if (VictoireJ1 != 0) {
        //Victoire du J1 (plus de roi noir sur le plateau)

        return 2;   //2 = victoire du joueur





    }
    else if (VictoireJ2 != 0) {
        //Victoire du J2


        return 1;   //1 = victoire de l'ia


    }
    else {
        //pas de victoire
    }





}

int VerifMiseEnEchec_Simulation(string grille_simulation[], string grille_couleur_simulation[])
{


    int numero_case_RoN;
    int numero_case_RoB;


    for (int i = 0; i < 64; i++) {
        if (grille_simulation[i] == "RoN") {

            numero_case_RoN = i;
        }
        if (grille_simulation[i] == "RoB") {

            numero_case_RoB = i;
        }
    }

    //Nous avons donc les numeros de case des 2 rois

    //Il faut maintenant vérifier pour chaque piece si un deplacement sur le roi est possible

    for (int i = 0; i < 64; i++) {

        if (grille_couleur_simulation[i] == "blanc") { //on va tester toutes les pieces blanches

            int numero_case = i;    //case de la piece blanche

            int verif = verification_J1(grille_simulation, grille_couleur_simulation, numero_case, numero_case_RoN);  //verif avec comme case de destination la case du roi ennemi

            if (verif == 1) {   //si le deplacement est possible, il y a une mise en echec  (impossible de tomber sur 2 ou 3 car les roques ne sont pas possibles)
                //Mise en echec sur le roi noir !
                return 2;
            }
            else {
                //Pas de mise en echec

            }



        }
        else if (grille_couleur_simulation[i] == "noir") { //on va tester toutes les pieces noirs

            int numero_case = i;    //case de la piece noir

            int verif = verification_J2(grille_simulation, grille_couleur_simulation, numero_case, numero_case_RoB);  //verif avec comme case de destination la case du roi ennemi

            if (verif == 1) {   //si le deplacement est possible, il y a une mise en echec
                //Mise en echec sur le roi blanc !
                return 1;
            }
            else {
                //Pas de mise en echec

            }



        }
        else {
            //Pas de piece sur cette case donc pas de possible mise en echec

        }




    }


    return 0;



}

