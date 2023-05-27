#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// les constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define VIDE ' '
#define INCONNU ' '

// les types
typedef int Grille[NB_LIGNES][NB_COLONNES];

// prototypes des fonctions
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void jouer(Grille laGrille, char pion, int * ligne, int * colonne);
int choisirColonne(Grille laGrille, char pion);
int chercherLigne(Grille laGrille, int col);
bool estVainqueur(Grille laGrille, int lig, int col);
void finDePartie(char vainqueur);
int choisirColonneStrategie1(Grille laGrille, char pion);
int choisirColonneStrategie2(Grille laGrille, char pion);
void jouerbot(Grille laGrille, char pion, int * ligne, int * colonne );
int choisirColonneStrategie3(Grille laGrille, char pion);
int choisirColonneStrategie4(Grille laGrille, char pion);

// Programme principal. C'est le pion A qui commence à jouer
int main()
{
    srand(time(NULL));
    
    Grille laGrille;
    int ligne, colonne,compteur1,compteur2,vic1=0,vic2=0,null=0,i=0;
    
    while (i<100)
    {
        char vainqueur=INCONNU;
        compteur1=0;
        compteur2=0;
        initGrille(laGrille);
        afficher(laGrille, PION_A);
        while (vainqueur==INCONNU && !grillePleine(laGrille)){
            jouer(laGrille,PION_A, &ligne, &colonne);
            compteur1++;
            afficher(laGrille, PION_B);
            if (estVainqueur(laGrille, ligne, colonne) ){
                vainqueur = PION_A;
            } else if (!grillePleine(laGrille)){
                jouerbot(laGrille, PION_B, &ligne, &colonne);
                compteur2++;
                afficher(laGrille, PION_A);
                if (estVainqueur(laGrille, ligne, colonne) ){
                    vainqueur = PION_B;
                }
            }
        }
        finDePartie(vainqueur);
        if(vainqueur==PION_B)
        {
            //printf("Nombre de pions jouee %d \n",compteur2);
            vic1++;
        }
        if(vainqueur==PION_A)
        {
            //printf("Nombre de pions jouee %d \n",compteur1);
            vic2++;
        }
        if(vainqueur==INCONNU)
        {
            null++;
        }
        
        i++;  
    }
    printf("%d \n",i);
    printf("Joueur O : %d victoires\n",vic1);
    printf("Joueur X : %d victoires\n",vic2);
    printf("%d parties nulles \n",null);
    system(EXIT_SUCCESS);
}


void initGrille(Grille laGrille){
    int l, c;
    for (l=0 ; l<NB_LIGNES ; l++){
        for (c=0 ; c<NB_COLONNES ; c++){
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion){
    int l, c;
    system("clear");  // changer en "clear" sur Linux
    printf("\t");
    printf("  %c\n", pion);
    printf("\t|");
    for (c=0; c<NB_COLONNES-1 ; c++){
        printf("---|");
    }
    printf("---|\n");
    for (l=0 ; l<NB_LIGNES-1 ; l++){
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("| %c ", laGrille[l][c]);
        }
        printf("|\n");
        printf("\t|");
        for (c=0; c<NB_COLONNES-1 ; c++){
            printf("---|");
        }
        printf("---|\n");
    }
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
        printf("| %c ", laGrille[l][c]);
    }
    printf("|\n");
    printf("\t|");
    for (c=0; c<NB_COLONNES-1 ; c++){
        printf("---|");
    }
    printf("---|\n");
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
        printf("  %d ", c);
    }
    printf("\n\n");
}

bool grillePleine(Grille laGrille){
    bool plein = true;
    int c = 0;
    while (plein && c<NB_COLONNES){
        if (laGrille[0][c] == VIDE){
            plein = false;
        }
        c++;
    }
    return plein;
}

void jouer(Grille laGrille, char pion, int * ligne, int * colonne ){
   *ligne = -1;
    do {
        *colonne = choisirColonneStrategie1(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);
    laGrille[*ligne][*colonne] = pion;
}
void jouerbot(Grille laGrille, char pion, int * ligne, int * colonne ){
   *ligne = -1;
    do {
        *colonne = choisirColonneStrategie4(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);
    laGrille[*ligne][*colonne] = pion;
}

int choisirColonne(Grille laGrille, char pion){
    int col;

    do{
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col<0 ||col>6);
    return col;
}

int chercherLigne(Grille laGrille, int col){
    int ligne = -1;

    while (ligne<NB_LIGNES-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col){
    // consiste à regarder si une ligne de 4 pions s'est formée autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt,i,j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<NB_LIGNES && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions à l'Est et à l'Ouest
    j = col;
    cpt = 0;
    // on regarde à l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde à l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=4 ){
        return true;
    }
    return false;
}
bool estVainqueur2(Grille laGrille, int lig, int col,char pion){
    // consiste à regarder si une ligne de 4 pions s'est formée autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt,i,j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<NB_LIGNES && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    if (cpt>=2){
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions à l'Est et à l'Ouest
    j = col;
    cpt = 0;
    // on regarde à l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde à l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt>=2){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=2 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=2){
        return true;
    }
    return false;
}

void finDePartie(char vainqueur){
    if (vainqueur != INCONNU){
        printf("Joueur %c vainqueur\n", vainqueur);
    } else {
        printf("MATCH NUL");
    }
}


int choisirColonneStrategie1(Grille laGrille, char pion)
{
    int col=0;
    while(laGrille[0][col]!=VIDE)
    {
        col++;
    }
    return col;
}
int choisirColonneStrategie2(Grille laGrille, char pion)
{
    int col=0,i,min=0,tmp,indice;
    printf("%d",chercherLigne(laGrille,col));
    for (i = 0; i < NB_COLONNES; i++)
    {
        tmp=chercherLigne(laGrille,i);
        if(min<=tmp)
        {
            min=tmp;
            indice=i;
        }
        
    }
    col=indice;
    
    return col;
}
int choisirColonneStrategie3(Grille laGrille, char pion)
{
    int col=3;
    if (chercherLigne(laGrille,col)==-1)
    {
        col=2;
        if (chercherLigne(laGrille,col)==-1)
        {
            col=4;
            if(chercherLigne(laGrille,col)==-1)
            {
                col=1;
                if (chercherLigne(laGrille,col)==-1)
                {
                    col=5;
                    if (chercherLigne(laGrille,col)==-1)
                    {
                        col=0;
                        if (chercherLigne(laGrille,col)==-1)
                        {
                            col=6;
                        }
                        
                    }

                    
                }
                
            }
            
        }
        
    }
    return col;

}
int choisirColonneStrategie4(Grille laGrille, char pion)
{
    int col;
    col=(rand() % 8);
    return col;
}
int choisirColonneStrategie5(Grille laGrille, char pion,int lig,int col)
{
    char detec_pion;
    if (pion == PION_B)
    {
        detec_pion= PION_A;
    }
    if (pion == PION_A)
    {
        detec_pion= PION_B;
    }
    estVainqueur2(laGrille,lig,col,detec_pion);
    
}


