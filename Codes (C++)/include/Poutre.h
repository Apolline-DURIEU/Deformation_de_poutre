// Apolline DURIEU - 12405409

#ifndef POUTRE_H
#define POUTRE_H

class Poutre // Definition basique d'une poutre : E module d'Young, L longueur, B epaisseur, H hauteur
{
    public:
        Poutre(); // Constructeur par defaut
        Poutre(double m_E, double m_L, double m_B, double m_H); // Constructeur avec arguments
        ~Poutre();// Destructeur

        //Méthodes
        double section()const; // Calcule de la section S = m_B*m_H
        void affiche()const; // Affichage des attributs
        double getL()const; // Accesseur de la longueur

    protected:
        double m_E; // Module d'Young
        double m_L; // Longueur initiale de la poutre
        double m_B; // Epaisseur de la poutre
        double m_H; // Hauteur de la poutre
};
#endif // POUTRE_H
