// Apolline DURIEU - 12405409

#ifndef POUTREFLEXIONCL_H
#define POUTREFLEXIONCL_H

#include <iostream>
#include "PoutreFlexion.h"

// Definition d'une poutre en flexion aux 2 bords encastrees, charge lineique appliquee : E module d'Young, L longueur, B epaisseur, H hauteur, f fleche, Q charge lineique
class PoutreFlexionCL : public PoutreFlexion
{
    public:
        PoutreFlexionCL();//Constructeur par defaut
        PoutreFlexionCL(double m_E, double m_L, double m_B, double m_H, double m_Q);//Constructeur qui prend des arguments
        ~PoutreFlexionCL();//Destructeur

         //Methodes
    double deforme()const; // Calcul de la fleche
    void affiche()const; // Affichage des attributs
    double eps(double x)const; // Calcul de la deformee

    // Methodes de calcul de l'energie de deformation
    double energie()const; // Calcul de l'energie de deformation
    double energie_RG(int m)const; // methode des rectangles composites a gauche
    double energie_RD(int m)const; // methode des rectangles composites a droite
    double energie_PM(int m)const; // methode des points milieux composites
    double energie_T(int m)const; // methode des trapezes composites
    double energie_S(int m)const; // methode de Simpson

    protected:
        double m_Q; // Charge Lineique
};

#endif // POUTREFLEXIONCL_H
