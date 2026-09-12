// Apolline DURIEU - 12405409

#include <iostream>
#include <math.h>
using namespace std;
#include "PoutreTraction.h"

// Definition d'une poutre en traction/compression : E module d'Young, L longueur, B epaisseur, H hauteur, F force appliquee, L_def longueur deformee

PoutreTraction::PoutreTraction(): Poutre(), m_F(1.0), m_L_def(deforme()) // Constructeur par defaut
{
}
PoutreTraction::PoutreTraction(double p_E, double p_L, double p_B, double p_H, double p_F ): Poutre(p_E, p_L, p_B, p_H), m_F(p_F), m_L_def(deforme()) // Constructeur (avec argument)
{
}
PoutreTraction::~PoutreTraction()//Destructeur
{
}

//Methodes :
    void PoutreTraction::affiche()const// affiche les attibuts de la classe
    {
        cout<<"================================================="<<endl;
        cout<<"Poutre en traction, comportement lineaire"<<endl;
        cout<<"  Module d'Young : "<<m_E<<" Mpa"<<endl;
        cout<<"  Dimensions : "<<m_L<<" x "<<m_B<<" x "<<m_H<<" m"<<endl;
        cout<<"  Force : "<<m_F<<" N"<<endl;
        cout<<"  Longueur deformee : "<<m_L_def<<" m"<<endl;
        cout<<endl;
    }

    double PoutreTraction::deforme()const// Calcul de la longueur deformee
    {
        // L_def = L*(1+F/(E*S))
        return m_L*(1 + m_F/(m_E*1e6*section()));
    }

    double PoutreTraction::eps(double x)const
    {
        // eps(x) = F/(SEL)*x
        return m_F/(m_L*m_E*1e6*section())*x;
    }

// Methodes de calcul de l'energie de deformation

    double PoutreTraction::energie()const // Calcul de l'energie de deformation (solution exacte)
    {
        // E_def = F^2*L/(3*S^2*E)
        return pow(m_F,2)*m_L/(3.0*pow(section(),2)*m_E*1e6);
    }

    double PoutreTraction::energie_RG(int m)const // rectangles composites gauches
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

    double PoutreTraction::energie_RD(int m)const // rectangles composites droits
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

    double PoutreTraction::energie_PM(int m)const // points milieux composites
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

    double PoutreTraction::energie_T(int m)const // trapezes composites
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

    double PoutreTraction::energie_S(int m)const // Simpson
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
