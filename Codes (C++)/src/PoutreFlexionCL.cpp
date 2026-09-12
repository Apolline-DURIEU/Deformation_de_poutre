// Apolline DURIEU - 12405409

#include <iostream>
#include <math.h>
using namespace std;
#include "PoutreFlexionCL.h"

// Definition d'une poutre en flexion aux 2 bords encastrees, charge lineique appliquee : E module d'Young, L longueur, B epaisseur, H hauteur, f fleche, Q charge lineique

PoutreFlexionCL::PoutreFlexionCL(): PoutreFlexion(1.0, 1.0, 1.0, 1.0, 0.0), m_Q(1.0) // Constructeur par defaut
{
}
PoutreFlexionCL::PoutreFlexionCL(double p_E, double p_L, double p_B, double p_H, double p_Q): PoutreFlexion(p_E, p_L, p_B, p_H, 0.0), m_Q(p_Q) // Constructeur (avec arguments)
{
    m_f = deforme();
}
PoutreFlexionCL::~PoutreFlexionCL()//Destructeur
{
}

//Methodes
double PoutreFlexionCL::deforme()const // Calcul de la fleche
{
    // f = 5*Q*L^4/(384*E*I)
    return 5.0*m_Q*pow(m_L,4)/(384.0*(m_E*1e6)*I());
}

void PoutreFlexionCL::affiche()const// Affichage des attibuts
{
    cout<<"=============================================="<<endl;
    cout<<"Poutre en flexion simple, charge lineique"<<endl;
    cout<<"  Module d'Young : "<<m_E<<" Mpa"<<endl;
    cout<<"  Dimensions : "<<m_L<<" x "<<m_B<<" x "<<m_H<<" m"<<endl;
    cout<<"  Force Lineique : "<<m_Q<<" N/m"<<endl;
    cout<<"  Fleche : "<<m_f<<" m"<<endl;
    cout<<endl;
}

double PoutreFlexionCL::energie()const
{
    // E_def = -389/362880 * (Q/LI)^2 * L^9/E
    return pow((m_Q/(m_L*I())),2) *pow(m_L,9)/(m_E*1e6) * 389.0/362880.0;
}

double PoutreFlexionCL::eps(double x)const // Calcul de la deforme
{
    // eps(x) = (Q/2*L*E*I) * (-x^4/12 +L*x^3/6 -L^3*x/12)
    return m_Q/(2.0*m_L*(m_E*1e6)*I())*(-pow(x,4)/12.0+m_L/6.0*pow(x,3)-pow(m_L,3)/12.0*x);
}

double PoutreFlexionCL::energie_RG(int m)const // rectangles composites gauches
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

    double PoutreFlexionCL::energie_RD(int m)const // rectangles composites droits
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

    double PoutreFlexionCL::energie_PM(int m)const // points milieux composites
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

    double PoutreFlexionCL::energie_T(int m)const // trapezes composites
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

    double PoutreFlexionCL::energie_S(int m)const // Simpson
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

