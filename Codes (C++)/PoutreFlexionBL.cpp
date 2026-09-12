#include <iostream>
#include <math.h>
using namespace std;

#include "PoutreFlexionBL.h"

// Definition d'une poutre en flexion, charge ponctuelle appliquee : E module d'Young, L longueur, B epaisseur, H hauteur f fleche, F force appliquee
// Bord encastree en x=L
// Bord libre en x=0

PoutreFlexionBL::PoutreFlexionBL():PoutreFlexion() // Constructeur par defaut
{
}
PoutreFlexionBL::PoutreFlexionBL(double p_E, double p_L, double p_B, double p_H, double p_F): PoutreFlexion(p_E, p_L, p_B, p_H, p_F) // Constructeur avec arguments
{
    m_f = deforme();
}

PoutreFlexionBL::~PoutreFlexionBL() // Destructeur
{
}

double PoutreFlexionBL::deforme()const // Calcul de la fleche
{
    // f = F*L^3/(3*E*I)
    return m_F*pow(m_L,3)/(3.0*m_E*1e6*I());
}

void PoutreFlexionBL::affiche()const // Affichage des constantes
{
    cout<<"=============================================="<<endl;
    cout<<"Poutre en flexion avec un bord libre, force ponctuelle"<<endl;
    cout<<"  Module d'Young : "<<m_E<<" Mpa"<<endl;
    cout<<"  Dimensions : "<<m_L<<" x "<<m_B<<" x "<<m_H<<" m"<<endl;
    cout<<"  Force Ponctuelle : "<<m_F<<" N"<<endl;
    cout<<"  Fleche : "<<m_f<<" m"<<endl;
    cout<<endl;
}

double PoutreFlexionBL::eps(double x)const // Calcul de la deformee
{
    // eps(x) = F/(L*E*I) * (-x^3/6 +L^2*x/2 -L^3/3)
    return m_F/(m_L*m_E*1e6*I())*(-pow(x,3)/6.0+pow(m_L,2)/2.0*x-pow(m_L,3)/3.0);
}

// Methodes de calcul de l'energie de deformation :

    double PoutreFlexionBL::energie()const // Calcul de l'enrgie de deformation (solution exacte)
    {
        // E_def = (F/I)^2 *L^6/E *2/63
        return (2.0/63.0)*pow((m_F/I()),2)*pow(m_L,6)/(m_E*1e6);
    }

    double PoutreFlexionBL::energie_RG(int m)const // rectangles composites gauches
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

    double PoutreFlexionBL::energie_RD(int m)const // rectangles composites droits
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
        cout<<"flexion I : "<<I<<endl;
        return I;
    }

    double PoutreFlexionBL::energie_PM(int m)const // points milieux composites
    {
        // m la quantite de rectangles utilises
        double h = m_L/(double)m; // longueur des rectangles (selon l'axe des abscisses)
        double I=0.0; // l'integrale
        double x = h/2.0;
        for(int k=0; k<m; k++)
        {
            I = I + pow(eps(x),2);
            cout<<"eps(x) = "<<eps(x)<<endl;
            x = x+h;
        }
        I = I*h*m_E*1e6;
        cout<<"pm I : "<<I<<endl;
        return I;
    }

    double PoutreFlexionBL::energie_T(int m)const // trapezes composites
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

    double PoutreFlexionBL::energie_S(int m)const // Simpson
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
