// Apolline DURIEU - 12405409

#include <iostream>
#include <math.h>
using namespace std;
#include "PoutreVibration.h"
double pi(3.14159265359);

// Definition des vibrations d'une poutre en flexion aux 2 bords encastrees : E module d'Young, L longueur, B epaisseur, H hauteur, F force appliquee, f fleche, rho masse volumique

PoutreVibration::PoutreVibration() : PoutreFlexion(), m_rho(1.0)
{
}
PoutreVibration::PoutreVibration(double p_E, double p_L, double p_B, double p_H, double p_F, double p_rho): PoutreFlexion(p_E, p_L, p_B, p_H, p_F), m_rho(p_rho)
{
}

PoutreVibration::~PoutreVibration()//Destructeur
{
}

//Methodes:
double PoutreVibration::frequence()const // Calcul de la frequence de vibration
{
    return pow(nbOnde(),2)*sqrt(m_E*1e6*I()/(m_rho*section()))*(1.0/(2.0*pi));
}

double PoutreVibration::nbOnde()const
{
    return 27.0*pi/2.0; // a=5 -> k=27*pi/2 (on aurait pu le definir en tant que constante en haut de la page)
}

double PoutreVibration::vitesse()const // Calcul de c_p, la vitesse de propagation de l'onde
{
    return 2*pi*frequence()/nbOnde(); //c_p = omega/k
}

double PoutreVibration::deforme()const // Calcul de la fleche
{
    double kL = nbOnde()*m_L;
    return sin(kL/2.0)/sinh(kL);
}

void PoutreVibration::affiche()const // Affichage des donnees
{
    cout<<"======================================================"<<endl;
    cout<<"Poutre en flexion vibrante"<<endl;
    cout<<"  Module d'Young : "<<m_E<<" Mpa"<<endl;
    cout<<"  Dimensions : "<<m_L<<" x "<<m_B<<" x "<<m_H<<" m"<<endl;
    cout<<"  Force : "<<m_F<<" N"<<endl;
    cout<<"  Fleche : "<<m_f<<" m"<<endl;
    cout<<endl;
}

// Methodes de calcul de l'energie de deformation :

    double PoutreVibration::energie()const // Calcul de l'energie de deformation
    {
        double k = nbOnde();
        // E_def  = E/(2*sinh^2(kL)) * (L+sin(2KL)/(2k))
        return m_E*1e6/(2.0*pow(sinh(k*m_L),2))*(m_L+sin(2.0*k*m_L)/(2.0*k));
    }

    double PoutreVibration::energie_RG(int m)const // rectangles composites gauches
    {
        // m la quantite de rectangles utilises
        double h = m_L/(double)m; // longueur des rectangles (selon l'axe des abscisses)
        double I=0.0; // l'integrale
        double x = 0.0;
        for(int k=0; k<m; k++)
        {
            I = I + pow(eps(x),2);
            x = x+h;
        }
        I = I*h*m_E*1e6;
        return I;
    }

    double PoutreVibration::energie_RD(int m)const // rectangles composites droits
    {
        // m la quantite de rectangles utilises
        double h = m_L/(double)m; // longueur des rectangles (selon l'axe des abscisses)
        double I=0.0; // l'integrale
        double x = h;
        for(int k=0; k<m; k++)
        {
            I = I + pow(eps(x),2);
            x = x+h;
        }
        I = I*h*m_E*1e6;
        return I;
    }

    double PoutreVibration::energie_PM(int m)const // points milieux composites
    {
        // m la quantite de rectangles utilises
        double h = m_L/(double)m; // longueur des rectangles (selon l'axe des abscisses)
        double I=0.0; // l'integrale
        double x = h/2.0;
        for(int k=0; k<m; k++)
        {
            I = I + pow(eps(x),2);
            x = x+h;
        }
        I = I*h*m_E*1e6;
        return I;
    }

    double PoutreVibration::energie_T(int m)const // trapezes composites
    {
        // m la quantite de trapezes utilises
        double h = m_L/(double)m; // longueur des trapezes (selon l'axe des abscisses)
        double I=0.0; // l'integrale
        double x = 0.0;
        for(int k=0; k<m; k++)
        {
            I = I + pow(eps(x),2) + pow(eps(x+h),2);
            x = x+h;
        }
        I = I*h*m_E*1e6/2.0;
        return I;
    }

    double PoutreVibration::energie_S(int m)const // Simpson
    {
        // m la quantite de rectangles utilises
        double h = m_L/(double)m; // longueur des rectangles (selon l'axe des abscisses)
        double I=0.0; // l'integrale
        double x = 0.0;
        for(int k=0; k<m; k++)
        {
            I = I + pow(eps(x),2) + 4.0*pow(eps(x+h/2.0),2) + pow(eps(x+h),2);
            x = x+h;
        }
        I = I*h*m_E*1e6/6.0;
        return I;
    }
