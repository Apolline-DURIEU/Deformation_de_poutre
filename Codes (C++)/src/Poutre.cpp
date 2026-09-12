// Apolline DURIEU - 12405409

#include<iostream>
using namespace std;
#include "Poutre.h"

// Definition basique d'une poutre : E module d'Young, L longueur, B epaisseur, H hauteur

Poutre::Poutre():m_E(1.0),m_L(1.0),m_B(1.0),m_H(1.0)// Constructeur par defaut
{
}
Poutre::Poutre(double p_E, double p_L, double p_B, double p_H): m_E(p_E),m_L(p_L),m_B(p_B),m_H(p_H) // Constructeur avec arguments
{
}

Poutre::~Poutre()//Destructeur
{
}

// Methodes :
    double Poutre::section()const // Calcul de la section transverse de la poutre
    {
        double S = m_B*m_H;
        return S;
    }

    double Poutre::getL()const // Accesseur de la longueur
    {
        return m_L;
    }

    void Poutre::affiche()const // Affichage des valeurs
    {
        cout<<"========================================================="<<endl;
        cout<<"Poutre :"<<endl;
        cout<<"  Module d'Young : "<<m_E<<" Mpa"<<endl;
        cout<<"  Dimensions : "<<m_L<<" x "<<m_B<<" x "<<m_H<<" m"<<endl;
        cout<<endl;
    }
