// Apolline DURIEU - 12405409

#ifndef POUTRETRACTIONNL_H
#define POUTRETRACTIONNL_H

#include <PoutreTraction.h>

// Definition d'une poutre en traction/compression (loi de comportement non lineaire) : E module d'Young, L longueur, B epaisseur, H hauteur, F force appliquee, L_def longueur deformee
class PoutreTractionNL : public PoutreTraction
{
    public:
        PoutreTractionNL(); // Constructeur par defaut
        PoutreTractionNL(double p_E, double p_L, double p_B, double p_H, double p_F); // Constructeur (avec argument)
        ~PoutreTractionNL(); // Destructeur

    // Methodes :
    double deforme()const; // Calcul de la longueur deformee
    void affiche()const; // Affichage des attributs
    double sigm_0(double eps, double H) const; // Calcul de : loi de Hooke -F/S
    double d_sigm(double eps, double H, double dH) const; // Derivee de la loi de Hooke(eps)
    double h(double eps) const; // Calcul de H(eps,eps_0)
    double dh(double eps) const; // Derivee de H(eps,eps_0)
};
#endif // POUTRETRACTIONNL_H
