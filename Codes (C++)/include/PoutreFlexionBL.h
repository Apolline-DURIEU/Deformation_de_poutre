// Apolline DURIEU - 12405409

#ifndef POUTREFLEXIONBL_H
#define POUTREFLEXIONBL_H

#include <iostream>
#include <PoutreFlexion.h>

// Definition d'une poutre en flexion, charge ponctuelle appliquee : E module d'Young, L longueur, B epaisseur, H hauteur f fleche, F force appliquee
// Bord encastree en x=L
// Bord libre en x=0
class PoutreFlexionBL : public PoutreFlexion
{
    public:
        PoutreFlexionBL(); // Constructeur par defaut
        PoutreFlexionBL(double p_E, double p_L, double p_B, double p_H, double p_F); // Constructeur avec arguments
        ~PoutreFlexionBL(); // Destructeur

    //Methodes :
        double deforme()const; // Calcul de la longueur deformee
        void affiche()const; // Affichage des attributs
        double eps(double x)const; // Calcul de la deformee

        // Methodes de calcul de l'energie de deformation
        double energie()const; // Calcul de l'energie de deformation (solution exacte)
        double energie_RG(int m)const; // methode des rectangles composites a gauche
        double energie_RD(int m)const; // methode des rectangles composites a droite
        double energie_PM(int m)const; // methode des points milieux composites
        double energie_T(int m)const; // methode des trapezes composites
        double energie_S(int m)const; // methode de Simpson

};

#endif // POUTREFLEXIONBL_H
