// Apolline DURIEU - 12405409

#include <iostream>
#include <math.h>
using namespace std;
#include "PoutreVibTorsion.h"

// Definition d'une poutre en torsion et de ses oscillations : E module d'Young, L longueur, B epaisseur, H hauteur, rho masse volumique, nu coefficient de poisson

PoutreVibTorsion::PoutreVibTorsion(): Poutre(), m_rho(1.0), m_nu(1.0) //Constructeur par defaut
{
}
PoutreVibTorsion::PoutreVibTorsion(double p_E, double p_L, double p_B, double p_H, double p_rho, double p_nu): Poutre(p_E, p_L, p_B, p_H), m_rho(p_rho), m_nu(p_nu) // Constructeur (avec arguments)
{
}

PoutreVibTorsion::~PoutreVibTorsion() //Destructeur
{
}

//Methodes :
    double PoutreVibTorsion::frequence()const // Calcul de la frequence d'oscillation
    {
        // f = 4*L *sqrt(E/(2*rho(nu+1)))
        return (4.0*m_L*sqrt(m_E*1e6/(2.0*m_rho*(m_nu+1.0))));
    }

    void PoutreVibTorsion::affiche()const // Affichage des variables
    {
        cout<<"============================================================"<<endl;
        cout<<"Poutre en torsion"<<endl;
        cout<<"  Module d'Young : "<<m_E<<" Mpa"<<endl;
        cout<<"  Dimensions : "<<m_L<<" x "<<m_B<<" x "<<m_H<<" m"<<endl;
        cout<<"  Frequence d'oscillation : "<<frequence()<<" Hz"<<endl;
        cout<<endl;
    }
