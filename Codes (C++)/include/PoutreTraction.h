// Apolline DURIEU - 12405409

#ifndef POUTRETRACTION_H
#define POUTRETRACTION_H
#include <iostream>

#include "Poutre.h"

// Definition d'une poutre en traction/compression : E module d'Young, L longueur, B epaisseur, H hauteur, F force appliquee, L_def longueur deformee
class PoutreTraction : public Poutre
{
    public:
        PoutreTraction(); // Constructeur par defaut
        PoutreTraction(double m_E, double m_L, double m_B, double m_H, double m_F); // Constructeur (avec argument)
        ~PoutreTraction(); // Destructeur

    //Methodes
        void affiche()const; // Affichage des attributs
        double deforme()const; // Calcul de la longueur deformee
        double eps(double x)const; // Calcul de la deformee

        // Methodes de calcul de l'energie de deformation
        double energie()const; // Calcul de l'energie de deformation (solution exacte)
        double energie_RG(int m)const; // methode des rectangles composites a gauche
        double energie_RD(int m)const; // methode des rectangles composites a droite
        double energie_PM(int m)const; // methode des points milieux composites
        double energie_T(int m)const; // methode des trapezes composites
        double energie_S(int m)const; // methode de Simpson

    protected:
        double m_F; // Force appliquee sur la poutre
        double m_L_def; // Longueur deformee
};

#endif // POUTRETRACTION_H
