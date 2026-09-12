// Apolline DURIEU - 12405409

#include <iostream>
#include <math.h>
using namespace std;

#include "PoutreTractionNL.h"
double eps_0 = 0.004;
double d_0 = 1e-12; // comparateur a zero

// Definition d'une poutre en traction/compression (loi de comportement non lineaire) : E module d'Young, L longueur, B epaisseur, H hauteur, F force appliquee, L_def longueur deformee

PoutreTractionNL::PoutreTractionNL(): PoutreTraction()
{
}
PoutreTractionNL::PoutreTractionNL(double p_E, double p_L, double p_B, double p_H, double p_F) : PoutreTraction(p_E, p_L, p_B, p_H, p_F)
{
}
PoutreTractionNL::~PoutreTractionNL()//Destructeur
{
}

//Methodes
double PoutreTractionNL::deforme()const// calcule la longueur deformee
{
    // methode de newton
    double eps = 1e-6; // initialisation de eps a un petit nombre
    double H=h(eps);
    double dH = dh(eps);
    while(abs(sigm_0(eps, H)-d_0) > d_0) // teste : (sigma(eps)-F/S) -> 0
    {
        if(abs(eps)>1.0)
        {
            cout<<"erreur : la deformee est superieur a 1"<<endl;
            break;
        }
        else
        {
            //continuer les calculs
            eps = eps - sigm_0(eps,H)/d_sigm(eps, H, dH); // itération : recalcul de eps
            H = h(eps);
            dH = dh(eps);
        }
    }
    return m_L*(1.0+eps); // L_def = L + delta_L    or eps = delta_L/L
}

double PoutreTractionNL::sigm_0(double eps, double H) const // Calcul de : Hooke(eps) -F/S
{
    // sigma(eps) = E*eps*H + (1.0-H)*(E*eps_0+ 1000*sqrt(|eps|/eps_0))
    return m_E*1e6*eps*H+ (1.0-H)*(m_E*1e6*eps_0+1e3*sqrt(abs(eps)/eps_0))-m_F/section();
}
double PoutreTractionNL::d_sigm(double eps, double H, double dH) const// Derivee de la loi de Hooke (selon eps)
{
    // d_sigma(eps) = E*(H+eps*dH) + (1-H)(500/sqrt(|eps|*eps_0)) - dh(E*eps_0+1000*sqrt(eps/eps_0))
    double d_sigma = m_E*1e6*(H+eps*dH)+(1.0-H)*(500.0/sqrt(eps_0*abs(eps)))-dH*(m_E*1e6*eps_0+1000.0*sqrt(eps/eps_0));
    if(abs(d_sigma-d_0)<d_0)
    {
        cout<<"erreur : les conditions ne sont pas respectee"<<endl;
    }
    return d_sigma;
}

double PoutreTractionNL::h(double eps)const // Calcul de H(eps, eps_0)
{
    // H(eps,eps_0) = (1-tanh(5000(eps-eps_0)))/2
    return (1.0-tanh(5000.0*(eps-eps_0)))/2.0;
}
double PoutreTractionNL::dh(double eps)const // fonction derivee de H(eps)
{
    // dH(eps) = -2500*(1-tanh^2(5000(eps-eps_0)))
    return (1.0-pow(tanh(5000.0*(eps-eps_0)),2))*(-2500.0);
}

void PoutreTractionNL::affiche()const// affiche les attibuts de la classe
{
    cout<<"================================================="<<endl;
    cout<<"Poutre en traction. Loi de comportement non lineaire"<<endl;
    cout<<"  Module d'Young : "<<m_E<<" Mpa"<<endl;
    cout<<"  Dimensions : "<<m_L<<" x "<<m_B<<" x "<<m_H<<" m"<<endl;
    cout<<"  Force : "<<m_F<<" N"<<endl;
    cout<<"  Longueur deformee : "<<deforme()<<" m"<<endl;
    cout<<endl;
}



