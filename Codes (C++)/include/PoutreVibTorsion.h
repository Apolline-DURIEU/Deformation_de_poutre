// Apolline DURIEU - 12405409

#ifndef POUTREVIBTORSION_H
#define POUTREVIBTORSION_H
#include <iostream>

#include <Poutre.h>

// Definition des vibrations d'une poutre en torsion : E module d'Young, L longueur, B epaisseur, H hauteur, F force appliquee, L_def longueur deformee
class PoutreVibTorsion : public Poutre
{
    public:
        PoutreVibTorsion(); // Constructeur par defaut
        PoutreVibTorsion(double p_E, double p_L, double p_B, double p_H, double p_rho, double p_nu); // Constructeur (avec arguments)
        ~PoutreVibTorsion(); //Destructeur

    //Methode :
    double frequence()const;
    void affiche()const;

    private:
        double m_rho; // Masse Volumique
        double m_nu; // Coefficient de poisson
};

#endif // POUTREVIBTORSION_H
