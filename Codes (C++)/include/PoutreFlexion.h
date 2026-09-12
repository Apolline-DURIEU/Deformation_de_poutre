// Apolline DURIEU - 12405409

#ifndef POUTREFLEXION_H
#define POUTREFLEXION_H

#include "Poutre.h"

// Definition d'une poutre en flexion aux 2 bords encastrees : E module d'Young, L longueur, B epaisseur, H hauteur, F force appliquee, f fleche

class PoutreFlexion : public Poutre
{
    public:
        PoutreFlexion(); // Constructeur par defaut
        PoutreFlexion(double p_E, double p_L, double p_B, double p_H, double p_F); // Constructeur avec arguments
        ~PoutreFlexion(); // Destructeur

    //Methodes
        void affiche()const; // Affichage des attributs
        double I()const; // Calcul du Moment Quadratique de la section
        double deforme()const; // Calcul de la fleche
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
        double m_f; // Fleche de la poutre
};

#endif // POUTREFLEXION_H
