// Apolline DURIEU - 12405409

#ifndef POUTREVIBRATION_H
#define POUTREVIBRATION_H
#include <iostream>

#include <PoutreFlexion.h>

// Definition des vibrations longitudinales d'une poutre en flexion aux 2 bords encastrees
class PoutreVibration : public PoutreFlexion
{
    public:
        PoutreVibration(); //Constructeur par defaut
        PoutreVibration(double p_E, double p_L, double p_B, double p_H, double p_F, double p_rho); // Constructeur (avec argument)
        ~PoutreVibration(); //Destructeur

    // Methode :
    double frequence()const; // Calcul de la frequence de vibration
    double nbOnde()const; // Calcul du nombre d'onde (note k)
    double vitesse()const; // Calcul de la vitesse de propagation de l'onde
    double deforme()const; //Calcul de la fleche
    void affiche()const; // Affichage des donnees

    // Methodes de calcul de l'energie de deformation
        double energie()const; // Calcul de l'energie de deformation (solution exacte)
        double energie_RG(int m)const; // methode des rectangles composites a gauche
        double energie_RD(int m)const; // methode des rectangles composites a droite
        double energie_PM(int m)const; // methode des points milieux composites
        double energie_T(int m)const; // methode des trapezes composites
        double energie_S(int m)const; // methode de Simpson


    private:
        double m_rho; //masse volumique
};

#endif // POUTREVIBRATION_H
