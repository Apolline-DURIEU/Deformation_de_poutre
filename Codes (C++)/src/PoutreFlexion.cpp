// Apolline DURIEU - 12405409

#include <iostream>
#include <math.h>
using namespace std;
#include "PoutreFlexion.h"

// Definition d'une poutre en flexion aux 2 bords encastrees : E module d'Young, L longueur, B epaisseur, H hauteur f fleche, F force appliquee

PoutreFlexion::PoutreFlexion(): Poutre(), m_F(0.0), m_f(deforme()) // Constructeur par defaut
{
}
PoutreFlexion::PoutreFlexion(double p_E, double p_L, double p_B, double p_H, double p_F ): Poutre(p_E, p_L, p_B, p_H), m_F(p_F), m_f(deforme()) // Constructeur avec arguments
{
}
PoutreFlexion::~PoutreFlexion()// Destructeur
{
}

//Methodes :
    void PoutreFlexion::affiche()const// Affichage les attibuts de la classe
    {
        cout<<"=============================================="<<endl;
        cout<<"Poutre en flexion simple"<<endl;
        cout<<"  Module d'Young : "<<m_E<<" Mpa"<<endl;
        cout<<"  Dimensions : "<<m_L<<" x "<<m_B<<" x "<<m_H<<" m"<<endl;
        cout<<"  Force ponctuelle : "<<m_F<<" N"<<endl;
        cout<<"  Fleche : "<<m_f<<" m"<<endl;
        cout<<endl;
    }

    double PoutreFlexion::I()const// Calcul du moment quadratique de la section
    {
        // I = B*H^3/12
        return m_B*pow(m_H,3)/12.0;
    }

    double PoutreFlexion::deforme()const// Calcul de la fleche
    {
        // fleche f = F*L^3/(48*E*I)
        return m_F*pow(m_L,3)/(48.0*(m_E*1e6)*I());
    }

    double PoutreFlexion::eps(double x)const // Calcul de la deformee
    {
        return m_F/(2.0*m_E*1e6*m_L*I())*(pow(x,3)/6.0-m_L*m_L*x/8.0);

    }

// Methodes de calcul de l'energie de deformation :

    double PoutreFlexion::energie()const // Calcul de l'energie de deformation
    {
        // E_def = 17*F^2*L^5/(80640*E*I^2)
        return pow(m_F,2)*pow(m_L,5)/((m_E*1e6)*pow(I(),2)) * 17.0/80640.0;
    }

    double PoutreFlexion::energie_RG(int m)const // rectangles composites gauches
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

    double PoutreFlexion::energie_RD(int m)const // rectangles composites droits
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

    double PoutreFlexion::energie_PM(int m)const // points milieux composites
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

    double PoutreFlexion::energie_T(int m)const // trapezes composites
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

    double PoutreFlexion::energie_S(int m)const // Simpson
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
