/**
 * @file puissance_4.c
 * @author FILY Ewen
 * @brief Permet de jouer puissance 4 en 1 contre 1. Peut être compilé uniquement avec le compilateur cc
 * @version 1.4
 * @date 2022-11-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>


const char PION_A ='X'; 
const char PION_B ='O';
const char jaune[13]="\x1b[33m⬤\x1B[0m";
const char rouge[13]="\x1b[31m⬤\x1B[0m";
const char VIDE =' ';
const char INCONNU =' ';

#define  NBLIG 6
#define  NBCOL 7

const int COLONNE_DEBUT = NBCOL/2;
typedef char Grille[NBLIG][NBCOL];


void initGrille(Grille);
void afficher(Grille,char,int);
bool grillePleine(Grille);
void jouer(Grille,char,int*, int*);
int choisirColonne(Grille,char,int);
int trouverLigne(Grille,int);
bool estVainqueur(Grille,int,int);
void finDePartie(char);
int gecth(void);

/**
 * @brief programme principal contenant toutes les fonctions et procedures du programme
 * 
 * @return int 
 */
int main () 
{
    bool partie=true;
    int score_j_a=0;
    int score_j_b=0;
    char input_fin[4];
    while (partie!=false)
    {
        char vainqueur;
        int ligne,colonne;
        Grille g;
        
        initGrille(g);
        vainqueur=INCONNU;
        
        afficher(g,PION_A,COLONNE_DEBUT);
        
        
        while ((vainqueur==INCONNU) && (grillePleine(g)==false))
        {
            jouer(g,PION_A,&ligne,&colonne);
            afficher(g,PION_B,COLONNE_DEBUT);
            
            if (estVainqueur(g,ligne,colonne)==true)
            {
                vainqueur=PION_A;
            }
            else if (grillePleine(g)==false)
            {
                jouer(g,PION_B,&ligne,&colonne);
                afficher(g,PION_A,COLONNE_DEBUT);
                if (estVainqueur(g,ligne,colonne)==true)
                {
                    vainqueur=PION_B;
                }
                
            }
            
        }
        printf("\nPartie terminee : ");
        finDePartie(vainqueur);
        if (vainqueur==PION_A)
        {
            score_j_a=score_j_a+1;
        }
        if (vainqueur==PION_B)
        {
            score_j_b=score_j_b+1;
        }
        printf("\nScore : Joueur %s | %d Victoire(s)\n        Joueur %s | %d Victoire(s)\n",jaune,score_j_a,rouge,score_j_b);
        printf("\nVoulez vous rejouez une partie ? (OUI/NON)\n");
        scanf("%s",input_fin);
        if (input_fin[0]=='N'||input_fin[0]=='n')
        {
            partie=false;
        }
        
    }
     
}
/**
 * @brief permet d'utiliser la fonction gecth (from conio.h) qui n'est pas disponible sur linux
 * 
 * @return int 
 */
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
/**
 * @brief 
 * 
 * @param g 
 */
void initGrille(Grille g)
{
    int i,j;
    for (i = 0; i < NBLIG; i++)
    {
        for (j = 0; j < NBCOL; j++)
        {
            g[i][j]=VIDE;
        }
        
    }
    
}
/**
 * @brief Permet d'afficher la grille complete du puissance 4 ainsi que les jetons en couleur
 * 
 * @param g Grille du puissance 4
 * @param pion pion du joueur qui va jouer 
 * @param colonne permet d'afficher le pion au dessus de la colonne donnée
 */
void afficher(Grille g,char pion,int colonne) 
{
    int i,j;
    char jeton[13];
    if (pion==PION_A)
    {
        strcpy(jeton,jaune);
    }
    else
    {
        strcpy(jeton,rouge);
    }
    
    system("clear");
    printf("Joueur au jetons : %s \n",jeton);
    
    switch (colonne)
    {
    case 0:
        printf("    <-%s->\n",jeton);
        break;
    case 1:
        printf("        <-%s->\n",jeton);
        break;
    case 2:
        printf("            <-%s->\n",jeton);
        break;
    case 3:
        printf("                <-%s->\n",jeton);

        break;
    case 4:
        printf("                    <-%s->\n",jeton);
        break;
    case 5:
        printf("                        <-%s->\n",jeton);
        break;
    case 6:
        printf("                            <-%s->\n",jeton);
        break;
    
    default:
        printf("Impossible\n");
        break;
    }
    
    for (i = 0; i < NBLIG; i++)
    {
        printf("    ");
        if (i<NBLIG-1)
        {
            for (j = 0; j < NBCOL; j++)
            {
                if (j<NBCOL-1)
                {
                    if (g[i][j]==VIDE)
                    {
                        printf("| %c ",g[i][j]);
                    }
                    if (g[i][j]==PION_A)
                    {
                        printf("| %s ",jaune);
                    }
                    if (g[i][j]==PION_B)
                    {
                        printf("| %s ",rouge);
                    }
                }
                if (j==NBCOL-1)
                {
                    if (g[i][j]==VIDE)
                    {
                        printf("| %c |",g[i][j]);
                    }
                    if (g[i][j]==PION_A)
                    {
                        printf("| %s ",jaune);
                    }
                    if (g[i][j]==PION_B)
                    {
                        printf("| %s ",rouge);
                    }
                } 
            }   
        }
        if (i==NBLIG-1)
        {
            for (j = 0; j < NBCOL; j++)
            {
                if (j<NBCOL-1)
                {
                    //printf("|_%c_",g[i][j]);
                    if (g[i][j]==VIDE)
                    {
                        printf("|_%c_",g[i][j]);
                    }
                    if (g[i][j]==PION_A)
                    {
                        printf("|_%s_",jaune);
                    }
                    if (g[i][j]==PION_B)
                    {
                        printf("|_%s_",rouge);
                    }
                }
                if (j==NBCOL-1)
                {
                    //printf("|_%c_|",g[i][j]);
                    if (g[i][j]==VIDE)
                    {
                        printf("|_%c_|",g[i][j]);
                    }
                    if (g[i][j]==PION_A)
                    {
                        printf("|_%s_|",jaune);
                    }
                    if (g[i][j]==PION_B)
                    {
                        printf("|_%s_|",rouge);
                    }
                }
            } 
        }
        printf("\n");  
    }
    printf("    |                           |\n  __|__                       __|__\n"); 
}
/**
 * @brief permet de savoir si la grille du puissance 4 est pleine ou non
 * 
 * @param g Grille
 * @return true   
 * @return false 
 */
bool grillePleine(Grille g)
{
    int i,grille_v=0;
    for (i = 0; i < NBLIG; i++)
    {
        if(g[0][i]==VIDE)
        {
            grille_v=grille_v+1;
        } 
    }
    if (grille_v>=1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
/**
 * @brief permet au joueur via les touches z , q et espace de pouvoir choisir la colonne ou le pion va se placer
 * 
 * @param g Grille
 * @param pion 
 * @param colonne 
 * @return int 
 */
int choisirColonne(Grille g,char pion,int colonne)
{
    char kb_code;
    
    kb_code='a';
    afficher(g,pion,colonne);
    while (kb_code!=' ')
    {
        kb_code = getch();
        if ((kb_code=='d')&&(colonne<6))
        {
            colonne=colonne+1;
            afficher(g,pion,colonne);
            
        }
        if ((kb_code=='q')&&(colonne>0))
        {
            colonne=colonne-1;
            afficher(g,pion,colonne); 
        }
        
    
    }
    return colonne;  
}
/**
 * @brief permet au programme de savoir a quel ligne le pion va être placé si la colonne est pleine on retourne -1 
 * 
 * @param g Grille
 * @param colonne 
 * @return int 
 */
int trouverLigne(Grille g,int colonne)
{
    int i,cases_v=0;
    for (i = 0; i < NBCOL; i++)
    {
        
        if(g[i][colonne]==' ')
        {
            cases_v=cases_v+1;
        }
    }
    if (cases_v==0)
    {
        return -1;
    }
    else
    {
        return cases_v-1;
    }   
}
/**
 * @brief permet de joueur de jouer tout en s'assurant que la colonne et la ligne soit la bonne 
 * 
 * @param g Grille
 * @param pion 
 * @param ligne 
 * @param colonne 
 */
void jouer(Grille g,char pion,int *ligne, int *colonne)
{
    int ligne_tmp,colonne_tmp;
    colonne_tmp=choisirColonne(g,pion,COLONNE_DEBUT);

    ligne_tmp=trouverLigne(g,colonne_tmp);

    while (ligne_tmp==-1)//On boucle tant que le joueur choisit une case pleine
        {
            if (ligne_tmp==-1)
            {
                
                colonne_tmp=choisirColonne(g,pion,COLONNE_DEBUT); 
                ligne_tmp=trouverLigne(g,colonne_tmp);
            } 
            printf("Colonne pleine veuillez choisir une autre .\n "); 
        }
    *ligne=ligne_tmp;
    *colonne=colonne_tmp;
    g[ligne_tmp][colonne_tmp]=pion;
}
/**
 * @brief Détecte alignement de quatre pions du même joueur à l'horizontal à la verticale et à la diagonale ,si un puissance quatre est detecté la fonction return true
 * 
 * @param g Grille
 * @param ligne 
 * @param colonne 
 * @return true 
 * @return false 
 */
bool estVainqueur(Grille g,int ligne,int colonne)
{
    int i,j,k,puiss_v=0,puiss_h=0,puiss_d1=0,puiss_d2=0,puiss_d3=0,puiss_d4=0;
     
    for (j = 0;j<NBCOL; j++)//détection à l'horizontal
    {
        if (g[ligne][j]==g[ligne][colonne])
        {
            
            puiss_h=puiss_h+1;
            
        }
        if (g[ligne][j]!=g[ligne][colonne])
            {
                
                puiss_h=0;
            }
        else if (puiss_h>3)
        {
            return true;
        }    
    }
    
    
    for (i = 0;i<NBLIG; i++)//détection à la vertical
        {
            if (g[i][colonne]==g[ligne][colonne])
            {
                
                puiss_v=puiss_v+1;
            }
            if (g[i][colonne]!=g[ligne][colonne])
            {
                
                puiss_v=0;
            }
            else if (puiss_v>3)
            {
                return true;
                break;
            }
            
            
        }   
    
    for (k = 1;k < 5; k++)// détection à la diagonale
    {
        if (g[ligne][colonne]==g[ligne-k][colonne-k])
        {
            
            puiss_d1=puiss_d1+1;
        }
        
        if (g[ligne][colonne]==g[ligne+k][colonne+k])
        {
            
            puiss_d2=puiss_d2+1;
        }
        
        if (g[ligne][colonne]==g[ligne+k][colonne-k])
        {
    
            puiss_d3=puiss_d3+1;
        }
        
        if (g[ligne][colonne]==g[ligne-k][colonne+k])
        {
            
            puiss_d4=puiss_d4+1;
        }
        else if((puiss_d1>2)||(puiss_d2>2)||(puiss_d3>2)||(puiss_d4>2))
        {
            return true;
            break;
        }
        
    }     
    {
        return false;
    }
}
/**
 * @brief Afficher qui est le vainqueur de la partie ou égalité si la grille est pleine
 * 
 * @param pion 
 */
void finDePartie(char pion)
{
    if (pion==PION_A) 
    {
        printf("Victoire du joueur %s\n",jaune);
    }
    if (pion==PION_B)
    {
        printf("Victoire du joueur %s\n",rouge);
    }
    
    if (pion==INCONNU)
    {
        printf("Egalite\n"); 
    }
        
    
    
}