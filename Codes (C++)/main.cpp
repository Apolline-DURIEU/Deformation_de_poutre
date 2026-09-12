#include <iostream>
#include <math.h>
#include <Poutre.h>
#include <PoutreFlexion.h>
#include <PoutreFlexionBL.h>
#include <PoutreFlexionCL.h>
#include <PoutreTraction.h>
#include <PoutreTractionNL.h>
#include <PoutreVibration.h>
#include <PoutreVibTorsion.h>

using namespace std;

int main()
{
    double E = 69000.0; // Module d'Young de l'acier (Mpa)

    PoutreFlexionCL Haut(E,1.5,2.5e-2, 2.5e-2, 200.0);

    double force = -(1.5*200.0)/2.0; // force supporte par les poutres du bas (masse des poutres negligee)
    PoutreTraction Bas(E, 1.8, 5.0e-3, 5.0e-3, force);

    PoutreVibTorsion Vib(E,1.5,2.5e-2, 2.5e-2, 7850.0, 0.27);

    /*int m = 3;

    // Calcul des erreurs
    double Eh = Haut.energie();
    double Eb = Bas.energie();

    double Eh_pm = Haut.energie_PM(m);
    double Eh_rg = Haut.energie_RG(m);
    double Eh_rd = Haut.energie_RD(m);
    double Eh_t = Haut.energie_T(m);
    double Eh_s = Haut.energie_S(m);

    double Eb_pm = Bas.energie_PM(m);
    double Eb_rg = Bas.energie_RG(m);
    double Eb_rd = Bas.energie_RD(m);
    double Eb_t = Bas.energie_T(m);
    double Eb_s = Bas.energie_S(m);*/


    cout<<"Assemblage dolmen : "<<endl;
    cout<<endl;
    cout<<"Poutre superieure :"<<endl;
    Vib.affiche();
    cout<<endl;
    cout<<"Poutre inferieure (x2) :"<<endl;
    Bas.affiche();

    /*cout<<endl;
    cout<<"Energies de deformation (poutre en flexion): "<<endl;
    cout<<"==============================="<<endl;
    cout<<"Solution exacte : "<<Eh<<" J"<<endl;
    cout<<endl;
    cout<<"erreurs d'exactitudes :"<<endl;
    cout<<"Rectangle composite a gauche : "<<(Eh-Eh_rg)/Eh<<endl;
    cout<<"Rectangle composite a droite : "<<(Eh-Eh_rd)/Eh<<endl;
    cout<<"Point milieu composite : "<<(Eh-Eh_pm)/Eh<<endl;
    cout<<"Trapeze composite : "<<(Eh-Eh_t)/Eh<<endl;
    cout<<"Simpson composite : "<<(Eh-Eh_s)/Eh<<endl;

    cout<<endl;
    cout<<endl;
    cout<<"Energies de deformation (poutre en traction): "<<endl;
    cout<<"==============================="<<endl;
    cout<<"Solution exacte : "<<Eb<< "J"<<endl;
    cout<<endl;
    cout<<"erreurs d'exactitudes : "<<endl;
    cout<<"Rectangle composite a gauche : "<<(Eb-Eb_rg)/Eb<<endl;
    cout<<"Rectangle composite a droite : "<<(Eb-Eb_rd)/Eb<<endl;
    cout<<"Point milieu composite : "<<(Eb-Eb_pm)/Eb<<endl;
    cout<<"Trapeze composite : "<<(Eb-Eb_t)/Eb<<endl;
    cout<<"Simpson composite : "<<(Eb-Eb_s)/Eb<<endl;*/

    return 0;
}
